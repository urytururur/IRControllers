#ifdef ARDUINO_ARCH_ESP32
#include <WiFi.h>
#else
#include <ESP8266WiFi.h>
#endif
#include <Espalexa.h>

#include <Arduino.h>
#include <IRremoteESP8266.h>
#include <IRsend.h>
#include <TVControllerHandler.h>
#include <LightStripControllerHandler.h>
#include <FanControllerHandler.h>

const uint16_t tvControllerSendingPin = 4;  // ESP8266 GPIO pin to use. Recommended: 4 (D2).
IRsend irsend(tvControllerSendingPin);

// WiFi Credentials
const char* ssid = "TN-SN7677";
const char* password = "oshakati";

//device names
String device_TV = "TV";
String device_tv_lights = "TV lights";
String device_fan = "Fan";

//callback function declarations
void IRControlUnitReceivedTVUpdateSignal(uint8_t brightness);
void IRControlUnitReceivedTVLightsUpdateSignal(uint8_t brightness);
void IRControlUnitReceivedFanUpdateSignal(uint8_t brightness);

//helper function declarations
boolean connectWifi();

boolean wifiConnected = false;
Espalexa espalexa;

TVControllerHandler tvControllerHandler{irsend};
LightStripControllerHandler lightStripControllerHandler{irsend};
FanControllerHandler fanControllerHandler{irsend};

void setup() {
  Serial.begin(115200);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  irsend.begin();

  // Initialise wifi connection
  wifiConnected = connectWifi();  

  if (wifiConnected)
  {
    // Define your devices here.
    espalexa.addDevice(device_TV, IRControlUnitReceivedTVUpdateSignal); //simplest definition, default state off
    espalexa.addDevice(device_tv_lights, IRControlUnitReceivedTVLightsUpdateSignal);
    espalexa.addDevice(device_fan, IRControlUnitReceivedFanUpdateSignal);

    espalexa.begin();
  }
  else
  {
    while (1)
    {
      Serial.println("Cannot connect to WiFi. Please check data and reset the ESP.");
      delay(2500);
    }
  }
}

void loop()
{
  tvControllerHandler.handleState();
  delay(100); //TODO: find a nicer way (than having delay-method calls all over the code) to make sure IR signals don't interfer with each other, maybe by altering the code in IRsend.(h/cpp) somehow?

  espalexa.loop();
  delay(100); //TODO: find a nicer way (than having delay-method calls all over the code) to make sure IR signals don't interfer with each other, maybe by altering the code in IRsend.(h/cpp) somehow?
}

//helper function implementations
boolean connectWifi()
{
  boolean state = true;
  int i = 0;

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("");
  Serial.println("Connecting to WiFi");

  // Wait for connection
  Serial.print("Connecting...");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    if (i > 20) {
      state = false; break;
    }
    i++;
  }
  Serial.println("");
  if (state) {
    Serial.print("Connected to ");
    Serial.println(ssid);
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
  }
  else {
    Serial.println("Connection failed.");
  }
  return state;
}

//callback function implementations
//NOTE! The argument passed as the parameter "brightness" for each callback function below is actually a value for brightness of a light. However, since the Alexa library used doesn't seem to support any Alexa smart device types except for lights, I'm instead mapping the brightness value to a specific commnand and setting routines in the Alexa app to make the phrases for setting different brightnesses more intuitive (Example: Routine("TV on" -> Alexa sets brighness to 1%) -> The callback function receives "value = 1" and will then excecute the code that is set up to run when the value argument is equal to 1).
void IRControlUnitReceivedTVUpdateSignal(uint8_t brightness)
{
  uint8_t commandId{espalexa.toPercent(brightness)};
  tvControllerHandler.sendSignalBasedOnCommandId(commandId);
}

void IRControlUnitReceivedTVLightsUpdateSignal(uint8_t brightness)
{
  uint8_t commandId{espalexa.toPercent(brightness)};
  lightStripControllerHandler.sendSignalBasedOnCommandId(commandId);
}

void IRControlUnitReceivedFanUpdateSignal(uint8_t brightness)
{
  
  uint8_t commandId{espalexa.toPercent(brightness)};
  fanControllerHandler.sendSignalBasedOnCommandId(commandId);
}