/* IRremoteESP8266: IRsendDemo - demonstrates sending IR codes with IRsend.
 *
 * Version 1.1 January, 2019
 * Based on Ken Shirriff's IrsendDemo Version 0.1 July, 2009,
 * Copyright 2009 Ken Shirriff, http://arcfn.com
 *
 * An IR LED circuit *MUST* be connected to the ESP8266 on a pin
 * as specified by kIrLed below.
 *
 * TL;DR: The IR LED needs to be driven by a transistor for a good result.
 *
 * Suggested circuit:
 *     https://github.com/crankyoldgit/IRremoteESP8266/wiki#ir-sending
 *
 * Common mistakes & tips:
 *   * Don't just connect the IR LED directly to the pin, it won't
 *     have enough current to drive the IR LED effectively.
 *   * Make sure you have the IR LED polarity correct.
 *     See: https://learn.sparkfun.com/tutorials/polarity/diode-and-led-polarity
 *   * Typical digital camera/phones can be used to see if the IR LED is flashed.
 *     Replace the IR LED with a normal LED if you don't have a digital camera
 *     when debugging.
 *   * Avoid using the following pins unless you really know what you are doing:
 *     * Pin 0/D3: Can interfere with the boot/program mode & support circuits.
 *     * Pin 1/TX/TXD0: Any serial transmissions from the ESP8266 will interfere.
 *     * Pin 3/RX/RXD0: Any serial transmissions to the ESP8266 will interfere.
 *   * ESP-01 modules are tricky. We suggest you use a module with more GPIOs
 *     for your first time. e.g. ESP-12 etc.
 */

/**********************************************************************************
 *  TITLE: Alexa control 5 channel Relay Module using NodeMCU or ESP32
 *  Click on the following links to learn more. 
 *  YouTube Video: https://youtu.be/tIFEtHVLexw
 *  Related Blog : https://easyelectronicsproject.com/esp32-projects/
 *  by Subhajit (Tech StudyCell)
 *  
 *  Download the libraries:
 *  https://github.com/Aircoookie/Espalexa
 *  
 *  Preferences--> Aditional boards Manager URLs : 
 *  https://dl.espressif.com/dl/package_esp32_index.json, http://arduino.esp8266.com/stable/package_esp8266com_index.json
 *  
 *  Download Board:
 *  For ESP8266 NodeMCU (2.5.1): https://github.com/esp8266/Arduino
 *  For ESP32                  : https://github.com/espressif/arduino-esp32
 **********************************************************************************/

#include <Arduino.h>
#include <IRremoteESP8266.h>
#include <IRsend.h>

#ifdef ARDUINO_ARCH_ESP32
#include <WiFi.h>
#else
#include <ESP8266WiFi.h>
#endif
#include <Espalexa.h>

#include <TVController.h>
#include <LightStripController.h>
#include <FanController.h>

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
void IRControlUnitReceivedTVUpdateSignal(uint8_t value);
void IRControlUnitReceivedTVLightsUpdateSignal(uint8_t value);
void IRControlUnitReceivedFanUpdateSignal(uint8_t value);

//helper function declarations
boolean connectWifi();

boolean wifiConnected = false;
Espalexa espalexa;

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

//IR controllers
TVController tvController{irsend};
LightStripController lightStripController{irsend};
FanController fanController{irsend};

void loop()
{
  tvController.sendIRSignalsBasedOnState();
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
//NOTE! The argument passed as the parameter "value" for each callback function below is actually a value for brightness of a light. However, since the Alexa library used doesn't seem to support any Alexa smart device types except for lights, I'm instead mapping the brightness value to a specific commnand and setting routines in the Alexa app to make the phrases for setting different brightnesses more intuitive (Example: Routine("TV on" -> Alexa sets brighness to 1%) -> The callback function receives "value = 1" and will then excecute the code that is set up to run when the value argument is equal to 1).
void IRControlUnitReceivedTVUpdateSignal(uint8_t value)
{
  uint8_t controllerCommandId{espalexa.toPercent(value)};
  tvController.sendSignalBasedOnCommandId(controllerCommandId);
}

void IRControlUnitReceivedTVLightsUpdateSignal(uint8_t value)
{
  uint8_t controllerCommandId{espalexa.toPercent(value)};
  lightStripController.sendSignalBasedOnCommandId(controllerCommandId);
}

void IRControlUnitReceivedFanUpdateSignal(uint8_t value)
{
  uint8_t controllerCommandId{espalexa.toPercent(value)};
  fanController.sendSignalBasedOnCommandId(controllerCommandId);
}