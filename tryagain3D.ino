/*
  Part 3D: Measure the time cost of 1000 analogRead() conversions.
*/

const int inputPin = A0;
const int averageCount = 1000;
const float referenceVoltage = 5.00;

void setup() {
  Serial.begin(9600);
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
  float averageVoltage = referenceVoltage * averageAdc / 1023.0;
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