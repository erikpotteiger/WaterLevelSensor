// Adafruit IO Temperature & Humidity Example
// Tutorial Link: https://learn.adafruit.com/adafruit-io-basics-temperature-and-humidity
//
// Adafruit invests time and resources providing this open source code.
// Please support Adafruit and open source hardware by purchasing
// products from Adafruit!
//
// Written by Todd Treece for Adafruit Industries
// Copyright (c) 2016-2017 Adafruit Industries
// Licensed under the MIT license.
//
// All text above must be included in any redistribution.

/************************** Configuration ***********************************/

// edit the config.h tab and enter your Adafruit IO credentials
// and any additional configuration needed for WiFi, cellular,
// or ethernet clients.
#include "config.h"

/************************ Example Starts Here *******************************/

// pin connected to Water Float Sensor data line
#define DATA_PIN 14

// Define WaterLevel Variable
int FloatSensor = 0;


// set up the 'WaterLevel' feeds
AdafruitIO_Feed *WaterLevel = io.feed("WaterLevel");

void setup() {

  // start the serial connection
  Serial.begin(115200);

  // wait for serial monitor to open
  while(! Serial);

  //Init WaterLevel Pin
  pinMode(DATA_PIN, INPUT_PULLUP);

  // connect to io.adafruit.com
  Serial.print("Connecting to Adafruit IO");
  io.connect();

  // wait for a connection
  while(io.status() < AIO_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  // we are connected
  Serial.println();
  Serial.println(io.statusText());

}

void loop() {

  // io.run(); is required for all sketches.
  // it should always be present at the top of your loop
  // function. it keeps the client connected to
  // io.adafruit.com, and processes any incoming data.
  io.run();


  // save FloatSensor Adafruit IO
  FloatSensor = digitalRead(DATA_PIN);
  if (FloatSensor == HIGH)
  {
    Serial.println("The line went high");
    WaterLevel->save(FloatSensor);
  }

  if (FloatSensor == LOW)
  {
    Serial.println("The line is low");
    WaterLevel->save(FloatSensor);
  }
  // temperature->save(fahrenheit);

  // deep sleep 10 minutes
  ESP.deepSleep(600e6);

}
