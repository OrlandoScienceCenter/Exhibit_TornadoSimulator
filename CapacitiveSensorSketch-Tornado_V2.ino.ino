#include <CapacitiveSensor.h>

/*
 * CapitiveSense Library Demo Sketch
 * Paul Badger 2008
 * Uses a high value resistor e.g. 10M between send pin and receive pin
 * Resistor effects sensitivity, experiment with values, 50K - 50M. Larger resistor values yield larger sensor values.
 * Receive pin is the sensor pin - try different amounts of foil/metal on this pin
 */

int Relay = 11;                        // Relay Pin
int CapSensePin1 = 3;                  // for cs_x_y, CapSensePin1 = x, Pin that goes to sensor/button
int CapSensePin2 = 8;                  // for cs_x_y, CapSensePin2 = y

//int ResetButton = 8;                   // Front Plate Button Pin for resetting program
//int ResetPin = 0;                      // Pin to send low to reset Arduino program when ResetButton goes high

int ArduinoPowerLED = 12;               // Arduino Power Indicator
int RelayLED = 13;                      // Diagnostic LED for Relay LED. Goes high when Relay is high.

int debounce = 200;
int mininumthreshold = 500;            // Minimum threshold for readings
int TimeRelayOn = 27;                  // 1/2 the time the Relay must stay on >>  For TimeRelayOn>30 the Arduino keeps the pin powered, so Delay(TimeRelayOn) in code below is split into two segments.


// 620kM resistor between pins CapSensePin1 & CapSensePin2, CapSensePin1 is sensor pin
CapacitiveSensor   cs_CapSensePin2_CapSensePin1 = CapacitiveSensor(CapSensePin2, CapSensePin1);


void setup()
{
  cs_CapSensePin2_CapSensePin1.set_CS_AutocaL_Millis(0xFFFFFFFF);     // turn off autocalibrate on channel 1 - just as an example
  Serial.begin(9600);
 
  pinMode(Relay, OUTPUT);
  pinMode(RelayLED, OUTPUT);
  TimeRelayOn *= 1000;
  pinMode(ArduinoPowerLED, OUTPUT);
  digitalWrite(ArduinoPowerLED, HIGH);

}

void loop()
{
  long total1 =  cs_CapSensePin2_CapSensePin1.capacitiveSensor(30);

  Serial.println(total1);                  // print sensor output 1
  Serial.println("\t");


  
  if (total1 > mininumthreshold) {
    digitalWrite(RelayLED, HIGH);
    digitalWrite(Relay, HIGH);

    delay(TimeRelayOn);
    delay(TimeRelayOn);

    digitalWrite(RelayLED, LOW);
    digitalWrite(Relay, LOW);
  }
  else
   digitalWrite(RelayLED, LOW);
   digitalWrite(Relay, LOW);


}
