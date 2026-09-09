/*
  m01_adc_raw.ino
  Module 1 -- Part 2 / 3A
  Read A0 and print the raw 10-bit ADC integer for Serial Monitor and Serial Plotter.

  Team:      TEC 8
  Board:     Arduino Uno, USB powered.  TEC POWER SUPPLY OFF for all of Module 1.
  Wiring:    100 kOhm pot: outer terminals to 5V and GND, wiper to A0.
  Baud:      9600
  Output:    ADC:<0-1023>, one per line, every 80 ms.
  Produces:  data/module_01/m01_adc_range_YYYYMMDD.txt  (pot swept end to end, gives min/max)
             data/module_01/m01_adc_fixed_mid_YYYYMMDD.txt (pot held at midrange)

  Was:       S2/analog.ino
  Version:   v1 (2026-09-09) -- restructured from the flat S2/ folder; logic unchanged
             except where marked "repo cleanup".
*/

const char* VERSION = "m01_adc_raw v1";

/*
  AnalogReadSerial

  Reads an analog input on pin 0, prints the result to the Serial Monitor.
  Graphical representation is available using Serial Plotter (Tools > Serial Plotter menu).
  Attach the center pin of a potentiometer to pin A0, and the outside pins to +5V and ground.

  This example code is in the public domain.

  https://docs.arduino.cc/built-in-examples/basics/AnalogReadSerial/
*/

// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  Serial.println(VERSION);   // repo cleanup: proves which build is on the board
}

// the loop routine runs over and over again forever:
void loop() {
  // read the input on analog pin 0:
  int sensorValue = analogRead(A0);

  // print a single labeled value so Serial Plotter can graph it
  Serial.print("ADC:");
  Serial.println(sensorValue);

  delay(80);  // delay in between reads for stability
}
