#include <Arduino.h>
#include <SoftwareSerial.h>
#include "MHZ19.h"
#include <ArduinoJson.h>

#define RX_PIN 3                                          // Rx pin which the MHZ19 Tx pin is attached to
#define TX_PIN 2                                          // Tx pin which the MHZ19 Rx pin is attached to
#define BAUDRATE 9600                                      // Device to MH-Z19 Serial baudrate (should not be changed)

MHZ19 myMHZ19;                                             // Constructor for library
SoftwareSerial mySerial(RX_PIN, TX_PIN);                   // Create software serial object

unsigned long getDataTimer = 0;

void setup()
{

    Serial.begin(9600);
    mySerial.begin(BAUDRATE);                               // Start the software serial at the correct baud rate

    myMHZ19.begin(mySerial);                                // Pass the software serial to the MHZ19 library

    myMHZ19.autoCalibration();                              // Turn auto calibration ON (OFF autoCalibration(false))

    pinMode(LED_BUILTIN, OUTPUT);                           // Initialize the LED pin as an output

    digitalWrite(LED_BUILTIN, HIGH);                        // turn the LED on
    delay(2000);                                            // wait
    digitalWrite(LED_BUILTIN, LOW);                         // turn the LED off
    delay(2000);                                            // wait
}

void loop()
{
  if (millis() - getDataTimer >= 2000)
  {
    getDataTimer = millis();

    int CO2 = myMHZ19.getCO2();                           // Request CO2 (as ppm)
    int8_t temperature = myMHZ19.getTemperature();        // Request Temperature (as Celsius)
    bool isABCEnabled = myMHZ19.getABC();                 // Check if ABC is enabled
    int range = myMHZ19.getRange();                       // Get sensor range
    int backgroundCO2 = myMHZ19.getBackgroundCO2();       // Get background CO2 level

    // Create a JSON object
    StaticJsonDocument<200> doc;
    // Variables - expectation from stable to volatile length
    doc["millis"] = getDataTimer;
    doc["ABCEnabled"] = isABCEnabled;
    doc["Range"] = range;
    doc["BackgroundCO2"] = backgroundCO2;
    doc["Temperature"] = temperature;
    doc["CO2"] = CO2;

    // Serialize the JSON object to a string
    String jsonString;
    serializeJson(doc, jsonString);

    // Print the JSON string
    Serial.println(jsonString);

  }
}
