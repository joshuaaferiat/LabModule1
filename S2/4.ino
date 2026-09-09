const int potPin = A0;
const int ledPin = 9;
const int numSamples = 10;

void setup() {
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  // 1. Sample and average the ADC reading
  long sum = 0;
  for (int i = 0; i < numSamples; i++) {
    sum += analogRead(potPin);
    delay(1); // small settling delay between samples
  }
  int avgADC = sum / numSamples; // 0–1023

  // 2. Convert averaged ADC number to voltaxge
  float voltage = avgADC * (5.0 / 1023.0);

  // 3. Map to PWM range (0–255)
  int pwmValue = map(avgADC, 0, 1023, 0, 255);

  // 4. Write PWM to LED pin
  analogWrite(ledPin, pwmValue);

  // Debug output
  Serial.print("ADC: "); Serial.print(avgADC);
  Serial.print("  Voltage: "); Serial.print(voltage, 2);
  Serial.print("V  PWM: "); Serial.println(pwmValue);

  delay(20);
}