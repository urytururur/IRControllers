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
//#include <LightStripController.h>
#include <FanController.h>

const uint16_t tvControllerSendingPin = 4;  // ESP8266 GPIO pin to use. Recommended: 4 (D2).
IRsend irsend(tvControllerSendingPin);

// WiFi Credentials
const char* ssid = "TN-SN7677";
const char* password = "oshakati";

//IR signal protocols
enum IRSignalProtocol
{
  IRSignalProtocol_Nikai,
  IRSignalProtocol_Nec
};

//IR code enums
enum TVLightsCodes
{
  TVLightsCodes_ON = 0xF7C03F,
  TVLightsCodes_OFF = 0xF740BF,
  TVLightsCodes_BRIGHTNESS_UP = 0xF700FF,
  TVLightsCodes_BRIGHTNESS_DOWN = 0xF7807F,
  TVLightsCodes_RED0 = 0xF720DF,
  TVLightsCodes_GREEN0 = 0xF7A05F,
  TVLightsCodes_BLUE0 = 0xF7609F,
  TVLightsCodes_RED1 = 0xF710EF,
  TVLightsCodes_GREEN1 = 0xF7906F,
  TVLightsCodes_BLUE1 = 0xF750AF,
  TVLightsCodes_RED2 = 0xF730CF,
  TVLightsCodes_GREEN2 = 0xF7B04F,
  TVLightsCodes_BLUE2 = 0xF7708F,
  TVLightsCodes_WHITE = 0xF7E01F,
  TVLightsCodes_FLASH = 0xF7D02F,
  TVLightsCodes_STROBE = 0xF7F00F,
  TVLightsCodes_FADE = 0xF7C837,
  TVLightsCodes_SMOOTH = 0xF7E817
};

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
//TODO: tvLightsController tvLightsController{irsend};
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
  value = espalexa.toPercent(value);

  tvController.sendSignalBasedOnUpdateValue(value);
}

void IRControlUnitReceivedTVLightsUpdateSignal(uint8_t value)
{
  value = espalexa.toPercent(value);
  
  switch(value)
  {
    //Light strip remote commands
    case 1:
      irsend.sendNEC(TVLightsCodes_ON);
      Serial.println("Emitted IR signal based on the value of 'TVLightsCodes_ON'.");
      break;
    case 2:
      irsend.sendNEC(TVLightsCodes_OFF);
      Serial.println("Emitted IR signal based on the value of 'TVLightsCodes_OFF'.");
      break;
    case 3:
      irsend.sendNEC(TVLightsCodes_BRIGHTNESS_UP);
      Serial.println("Emitted IR signal based on the value of 'TVLightsCodes_BRIGHTNESS_UP'.");
      break;
    case 4:
      irsend.sendNEC(TVLightsCodes_BRIGHTNESS_DOWN);
      Serial.println("Emitted IR signal based on the value of 'TVLightsCodes_BRIGHTNESS_DOWN'.");
      break;
    case 5:
      irsend.sendNEC(TVLightsCodes_RED0);
      Serial.println("Emitted IR signal based on the value of 'TVLightsCodes_RED0'.");
      break;
    case 6:
      irsend.sendNEC(TVLightsCodes_GREEN0);
      Serial.println("Emitted IR signal based on the value of 'TVLightsCodes_GREEN0'.");
      break;
    case 7:
      irsend.sendNEC(TVLightsCodes_BLUE0);
      Serial.println("Emitted IR signal based on the value of 'TVLightsCodes_BLUE0'.");
      break;
    case 8:
      irsend.sendNEC(TVLightsCodes_WHITE);
      Serial.println("Emitted IR signal based on the value of 'TVLightsCodes_WHITE'.");
      break;
    case 9:
      irsend.sendNEC(TVLightsCodes_FLASH);
      Serial.println("Emitted IR signal based on the value of 'TVLightsCodes_FLASH'.");
      break;
    case 10:
      irsend.sendNEC(TVLightsCodes_STROBE);
      Serial.println("Emitted IR signal based on the value of 'TVLightsCodes_STROBE'.");
      break;
    case 11:
      irsend.sendNEC(TVLightsCodes_FADE);
      Serial.println("Emitted IR signal based on the value of 'TVLightsCodes_FADE'.");
      break;
    case 12:
      irsend.sendNEC(TVLightsCodes_SMOOTH);
      Serial.println("Emitted IR signal based on the value of 'TVLightsCodes_SMOOTH'."); 
      break;
    case 13:
      irsend.sendNEC(TVLightsCodes_RED1);
      Serial.println("Emitted IR signal based on the value of 'TVLightsCodes_RED1'.");
      break;
    case 14:
      irsend.sendNEC(TVLightsCodes_GREEN1);
      Serial.println("Emitted IR signal based on the value of 'TVLightsCodes_GREEN1'.");
      break;
    case 15:
      irsend.sendNEC(TVLightsCodes_BLUE1);
      Serial.println("Emitted IR signal based on the value of 'TVLightsCodes_BLUE1'.");
      break;
    case 16:
      irsend.sendNEC(TVLightsCodes_RED2);
      Serial.println("Emitted IR signal based on the value of 'TVLightsCodes_RED2'.");
      break;
    case 17:
      irsend.sendNEC(TVLightsCodes_GREEN2);
      Serial.println("Emitted IR signal based on the value of 'TVLightsCodes_GREEN2'.");
      break;
    case 18:
      irsend.sendNEC(TVLightsCodes_BLUE2);
      Serial.println("Emitted IR signal based on the value of 'TVLightsCodes_BLUE2'.");
      break;
      
    default:
      Serial.println("Event registered on 'TV lights' but no action defined for the incoming callback method argument.");
  }
}

void IRControlUnitReceivedFanUpdateSignal(uint8_t value)
{
  value = espalexa.toPercent(value);
  
  fanController.sendSignalBasedOnUpdateValue(value);
}