#include <math.h>

void setup() {
  Serial.begin(9600);
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