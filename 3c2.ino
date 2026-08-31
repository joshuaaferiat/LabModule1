/*
  Part 3C-a: Compare One Reading With A 1000-Reading Average
  Prints 100 averaged readings, then 100 single readings.
  Format: Ave1000_Point_1 Voltage_V:2.4561
          Ave1_Point_1 Voltage_V:2.4570
*/

void setup() {
  Serial.begin(9600);
}

// --- Reads a single ADC conversion and returns voltage ---
float readVoltageSingle() {
  int sensorValue = analogRead(A0);
  // 10-bit ADC: 1024 levels, resolution = 5.00V / 1024 = 4.88mV
  return sensorValue * (5.00 / 1024.0);
}

// --- Averages 'numReadings' ADC conversions and returns voltage ---
float readVoltageAveraged(int numReadings) {
  long sum = 0;  // long prevents overflow (1000 * 1023 = 1,023,000)
  for (int i = 0; i < numReadings; i++) {
    sum += analogRead(A0);
  }
  float avgADC = sum / (float)numReadings;
  return avgADC * (5.00 / 1024.0);
}

void loop() {

  // ---- BLOCK 1: 100 readings, each averaging 1000 conversions ----
  for (int i = 1; i <= 100; i++) {
    float voltage = readVoltageAveraged(1000);
    Serial.print("Ave1000_Point_");
    Serial.print(i);
    Serial.print(" Voltage_V:");
    Serial.println(voltage, 4);
    delay(200);  // Slows down the plotter so you can see the transition
  }

  // ---- BLOCK 2: 100 readings, each from a single conversion ----
  for (int i = 1; i <= 100; i++) {
    float voltage = readVoltageSingle();
    Serial.print("Ave1_Point_");
    Serial.print(i);
    Serial.print(" Voltage_V:");
    Serial.println(voltage, 4);
    delay(200);  // Slows down the plotter
  }

  // Loop repeats forever: Averaged block → Single block → Averaged → Single → ...
}
