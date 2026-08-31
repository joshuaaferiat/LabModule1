void setup() {
  Serial.begin(9600);
}

void loop() {
  // ---------- BLOCK 1: 100 sequential single readings ----------
  for (int i = 1; i <= 100; i++) {
    int raw = analogRead(A0);                  // One reading from A0
    float voltage = raw * (5.00 / 1024.0);     // Convert to voltage
    Serial.print("Single_Point_");
    Serial.print(i);
    Serial.print(" Voltage_V:");
    Serial.println(voltage, 4);
    delay(100);  // ~100 ms per reading => 100 readings in about 10 s
  }

  // ---------- BLOCK 2: 100 sequential averaged readings ----------
  for (int i = 1; i <= 100; i++) {
    long sum = 0;                             // Accumulate 1000 reads safely
    for (int j = 0; j < 1000; j++) {
      sum += analogRead(A0);                  // Average 1000 readings
    }
    float avgRaw = sum / 1000.0;              // Raw average value
    float voltage = avgRaw * (5.00 / 1024.0); // Convert average to voltage
    Serial.print("Avg1000_Point_");
    Serial.print(i);
    Serial.print(" Voltage_V:");
    Serial.println(voltage, 4);
    delay(100);  // keep each 100-point block spread across about 10 s
  }

  // The Arduino loop() function repeats automatically, so the sequence starts again.
}