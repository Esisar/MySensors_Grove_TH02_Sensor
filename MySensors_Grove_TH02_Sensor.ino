/**
 * MySensors_Grove_TH02_Sensor
 *
 *******************************
 *
 * REVISION HISTORY
 * Version 1.0: GUILLOTON Laurent
 * Version 1.1 - 2017-07-03: Création du sketch initial
 *
 * DESCRIPTION
 *
 * Sketch gérant l'envoi des datas d'un capteur de température et d'humidité (Grove) avec un lien NRF24L01 Mysensors v2.0
 *
 * For more information, please visit:
 * http://wiki.seeed.cc/Grove-TemptureAndHumidity_Sensor-High-Accuracy_AndMini-v1.0/
 *
 */



// Enable debug prints
#define MY_DEBUG

// Enable and select radio type attached
#define MY_RADIO_NRF24

// ID du noeud
#define MY_NODE_ID 108

#include "Arduino.h"
#include <Wire.h>
#include <SPI.h>
#include <MySensors.h>
#include <TH02_dev.h>


// Sleep time between sensor updates (in milliseconds)
static const uint64_t UPDATE_INTERVAL = 120000;

#define CHILD_ID_HUM 0
#define CHILD_ID_TEMP 1

MyMessage msgHum(CHILD_ID_HUM, V_HUM);
MyMessage msgTemp(CHILD_ID_TEMP, V_TEMP);


void presentation()
{
  // Send the sketch version information to the gateway
  sendSketchInfo("MySensors_Grove_TH02_Sensor", "1.2");

  // Register all sensors to gw (they will be created as child devices)
  present(CHILD_ID_HUM, S_HUM);
  present(CHILD_ID_TEMP, S_TEMP);
}


void setup()
{
  TH02.begin();
 }


void loop()
{
  float Temperature = TH02.ReadTemperature();
  float Humidity = TH02.ReadHumidity();

    send(msgTemp.set(Temperature, 1));
    send(msgHum.set(Humidity, 1));

  // Sleep for a while to save energy
  sleep(UPDATE_INTERVAL);
}
