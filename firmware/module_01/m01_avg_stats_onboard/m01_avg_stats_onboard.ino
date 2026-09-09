/*
  m01_avg_stats_onboard.ino
  Module 1 -- Part 3C helper
  Compute mean and sample standard deviation of 100 single readings on the Arduino itself.

  Team:      TEC 8
  Board:     Arduino Uno, USB powered.  TEC POWER SUPPLY OFF for all of Module 1.
  Wiring:    100 kOhm pot held FIXED: outer terminals to 5V and GND, wiper to A0.
  Baud:      9600
  Output:    Mean_V:<v>  s:<v>   -- two labeled fields on one line; use Serial Monitor, not Plotter.
             Cross-check against analysis/module_01/averaging_stats.py.
  Produces:  data/module_01/m01_onboard_stats_YYYYMMDD.txt

  Was:       S2/3c.ino
  Version:   v1 (2026-09-09) -- restructured from the flat S2/ folder; logic unchanged
             except where marked "repo cleanup".
*/

const char* VERSION = "m01_avg_stats_onboard v1";

#include <math.h>

void setup() {
  Serial.begin(9600);
  Serial.println(VERSION);   // repo cleanup: proves which build is on the board
}

void loop() {
  float voltages[100];
  float sum = 0.0;

  // Collect 100 voltage samples from A0
  for (int i = 0; i < 100; i++) {
    int raw = analogRead(A0);
    float voltage = raw * (5.00 / 1024.0);
    voltages[i] = voltage;
    sum += voltage;
    delay(100);  // spread the 100 samples across about 10 seconds
  }

  // Mean voltage for this 100-point block
  float meanVoltage = sum / 100.0;

  // Sample standard deviation s
  float sumSquares = 0.0;
  for (int i = 0; i < 100; i++) {
    float diff = voltages[i] - meanVoltage;
    sumSquares += diff * diff;
  }
  float s = sqrt(sumSquares / 99.0);

  Serial.print("Mean_V:");
  Serial.print(meanVoltage, 2);
  Serial.print("  s:");
  Serial.println(s, 4);
}