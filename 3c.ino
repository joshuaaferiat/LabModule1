void setup() {
  Serial.begin(9600);
}

void loop() {
  // ---------- BLOCK 1: 100 single readings ----------
  for (int i = 1; i <= 100; i++) {
    int raw = analogRead(A0);                       // Read once
    float voltage = raw * (5.00 / 1024.0);          // Convert to voltage
    Serial.print("Ave1_Point_");
    Serial.print(i);
    Serial.print(" Voltage_V:");
    Serial.println(voltage, 4);                     // Print with 4 decimals
    delay(2);                                       // Small delay for readability
  }

  // ---------- BLOCK 2: 100 averaged readings (each averages 1000 raw reads) ----------
  for (int i = 1; i <= 100; i++) {
    long sum = 0;                                   // Use long to avoid overflow
    for (int j = 0; j < 1000; j++) {
      sum += analogRead(A0);                        // Accumulate 1000 readings
    }
    float avgRaw = sum / 1000.0;                    // Average the raw ADC values
    float voltage = avgRaw * (5.00 / 1024.0);       // Convert average to voltage
    Serial.print("Ave1000_Point_");
    Serial.print(i);
    Serial.print(" Voltage_V:");
    Serial.println(voltage, 4);
    delay(2);
  }
}