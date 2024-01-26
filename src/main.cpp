// *****************************************************************************
// Description: ESP32 ADC example, read voltage using voltage divider method.
// Author: Thomas Paganelli - University of studies of Bergamo - Engineering department
// Date: 26/01/2024
//
// Important: esp32 and the generator under test grounds must be connected together.
// *****************************************************************************

#include <Arduino.h>
#define input_pin 25

// voltage divider values, change them according to the voltage you want to measure.
#define R1 3250 // voltage divider resistor 1
#define R2 993 // voltage divider resistor 2

void setup() {
  // put your setup code here, to run once:
  pinMode(input_pin, INPUT);
  Serial.begin(115200);

  analogSetPinAttenuation(input_pin, ADC_11db); // 0-3.3V
  analogReadResolution(12); // 0-4095
}

void loop() {

  long int a = 0;
  for (size_t i = 0; i < 100; i++){  // 100 samples

    a = a + analogReadMilliVolts(input_pin); // read input pin, analogReadMilliVolts() returns mV and is more accurate than analogRead() in mV readings.
    // no matter the function, esp32 readigs are not accurate, so we need to take a lot of samples and then divide by the number of samples to get the average.
    // the readings still encreased by 25-40 mV.
  }
  
  int mV_R2 = a/100;  
  float mV_E = mV_R2*(R1+R2)/R2;  // reverse formula of voltage divider, R1 = 3250, R2 = 993 (input pin reads voltage between R2 and GND).
  float V_E = mV_E/1000;

  Serial.println(V_E);
  delay(250);
}

