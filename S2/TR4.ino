/*
  Part 4: LED Brightness From Averaged Analog Input
  
  Signal chain:
  Pot voltage -> Averaged ADC -> Map to PWM -> analogWrite -> LED
  
  Prints averaged voltage and PWM value to Serial Monitor.
  Outputs PWM on pin 9 to control LED brightness.
  
  Wiring:
  - Potentiometer left pin  -> 5V
  - Potentiometer right pin -> GND
  - Potentiometer wiper     -> A0
  - Pin 9 -> Resistor (220Ω-1kΩ) -> LED Anode (long leg)
  - LED Cathode (short leg) -> GND
*/

// --- Pin Definitions ---
const int POT_PIN = A0;      // Potentiometer on analog pin 0
const int LED_PIN = 9;       // PWM output on pin 9 (~490 Hz on Uno)

// --- Averaging Settings ---
const int NUM_READINGS = 1000;  // Number of readings to average

// --- Helper function: Read and average analog input ---
float readAveragedVoltage(int pin, int numReadings) {
  long sum = 0;
  for (int i = 0; i < numReadings; i++) {
    sum += analogRead(pin);
  }
  float avgADC = sum / (float)numReadings;
  // 10-bit ADC: 1024 levels, resolution = 5.00V / 1024 = 4.88mV
  return avgADC * (5.00 / 1024.0);
}

void setup() {
  Serial.begin(9600);
  pinMode(LED_PIN, OUTPUT);
  
  Serial.println("=== Part 4: LED Brightness from Averaged Analog Input ===");
  Serial.println("Turn the potentiometer to change LED brightness.");
  Serial.println();
  Serial.println("Ave_Voltage(V)\tPWM_Value\tDuty_Cycle(%)");
}

void loop() {
  
  // --- 1. Read and average the potentiometer voltage ---
  float voltage = readAveragedVoltage(POT_PIN, NUM_READINGS);
  
  // --- 2. Convert voltage to ADC value (0-1023) for mapping ---
  // voltage = ADC * (5.0 / 1024.0)  =>  ADC = voltage * (1024.0 / 5.0)
  float adcValue = voltage * (1024.0 / 5.00);
  
  // --- 3. Map the averaged ADC value to a PWM value (0-255) ---
  int pwmValue = map((int)adcValue, 0, 1023, 0, 255);
  
  // --- 4. Constrain to ensure it stays within 0-255 ---
  pwmValue = constrain(pwmValue, 0, 255);
  
  // --- 5. Calculate duty cycle percentage ---
  float dutyCycle = (pwmValue / 255.0) * 100.0;
  
  // --- 6. Output the PWM value to the LED ---
  analogWrite(LED_PIN, pwmValue);
  
  // --- 7. Print to Serial Monitor ---
  Serial.print(voltage, 3);       // Voltage with 3 decimal places
  Serial.print("\t\t");
  Serial.print(pwmValue);         // PWM value (0-255)
  Serial.print("\t\t");
  Serial.print(dutyCycle, 1);     // Duty cycle percentage with 1 decimal
  Serial.println("%");
  
  delay(100);  // Update 10 times per second (smooth enough)
}
