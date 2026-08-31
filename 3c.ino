void setup() {
  Serial.begin(9600);
}

void loop() {
  // Immediate measurement from A0
  int raw = analogRead(A0);
  float voltage = raw * (5.00 / 1024.0);
  Serial.print("Immediate_V:");
  Serial.println(voltage, 2);

  // Average of 100 readings from A0
  long sum = 0;
  for (int i = 0; i < 100; i++) {
    sum += analogRead(A0);
  }
  float avgRaw = sum / 100.0;
  float avgVoltage = avgRaw * (5.00 / 1024.0);
  Serial.print("Average_100_V:");
  Serial.println(avgVoltage, 2);

  delay(100);
}