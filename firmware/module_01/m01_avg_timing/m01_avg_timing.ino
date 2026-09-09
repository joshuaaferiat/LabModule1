/*
  m01_avg_timing.ino
  Module 1 -- Part 3D
  Time 1000 analogRead() conversions with micros() and report the conversion rate.

  Team:      TEC 8
  Board:     Arduino Uno, USB powered.  TEC POWER SUPPLY OFF for all of Module 1.
  Wiring:    100 kOhm pot: outer terminals to 5V and GND, wiper to A0.
  Baud:      9600
  Output:    Elapsed_us:<n> and Conversions_per_second:<n>, once per second.
  Produces:  data/module_01/m01_timing_YYYYMMDD.txt

  Was:       S2/tryagain3D.ino
  Version:   v1 (2026-09-09) -- restructured from the flat S2/ folder; logic unchanged
             except where marked "repo cleanup".
*/

const char* VERSION = "m01_avg_timing v1";

/*
  Part 3D: Measure the time cost of 1000 analogRead() conversions.
*/

const int inputPin = A0;
const int averageCount = 1000;
const float referenceVoltage = 5.00;

void setup() {
  Serial.begin(9600);
  Serial.println(VERSION);   // repo cleanup: proves which build is on the board
}

void loop() {
  long total = 0;

  // Start immediately before the acquisition loop and stop immediately after it.
  unsigned long startTime = micros();
  for (int reading = 0; reading < averageCount; reading++) {
    total += analogRead(inputPin);
  }
  unsigned long elapsedMicroseconds = micros() - startTime;

  float averageAdc = total / (float)averageCount;
  // repo cleanup: divisor was /1023.0; standardised on 1024 to match the other sketches
  float averageVoltage = referenceVoltage * averageAdc / 1024.0;
  float elapsedSeconds = elapsedMicroseconds / 1000000.0;
  float conversionsPerSecond = averageCount / elapsedSeconds;

  Serial.print("Average_ADC:");
  Serial.println(averageAdc, 2);
  Serial.print("Average_Voltage:");
  Serial.println(averageVoltage, 4);
  Serial.print("Elapsed_us:");
  Serial.println(elapsedMicroseconds);
  Serial.print("Conversions_per_second:");
  Serial.println(conversionsPerSecond, 1);
  Serial.println();

  delay(1000);
}