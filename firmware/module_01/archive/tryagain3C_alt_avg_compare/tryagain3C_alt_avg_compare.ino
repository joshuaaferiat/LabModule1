/*
	Part 3C: Compare one reading with a 1000-reading average.
	Each cycle prints 100 single readings followed by 100 averaged readings.
*/

const int inputPin = A0;
const int pointsPerBlock = 100;
const int averageCount = 1000;
const float referenceVoltage = 5.00;

float adcToVoltage(float adcValue) {
	return referenceVoltage * adcValue / 1023.0;
}

float readAverageVoltage(int numberOfReadings) {
	long total = 0;

	for (int reading = 0; reading < numberOfReadings; reading++) {
		total += analogRead(inputPin);
	}

	return adcToVoltage(total / (float)numberOfReadings);
}

void printVoltagePoint(const char *label, int pointNumber, float voltage) {
	Serial.print(label);
	Serial.print(pointNumber);
	Serial.print(" Voltage_V:");
	Serial.println(voltage, 4);
}

void setup() {
	Serial.begin(9600);
}

void loop() {
	// Block 1: one ADC conversion per reported voltage.
	for (int point = 1; point <= pointsPerBlock; point++) {
		float voltage = readAverageVoltage(1);
		printVoltagePoint("Ave1_Point_", point, voltage);
		delay(200);
	}

	// Block 2: average 1000 ADC conversions for each reported voltage.
	for (int point = 1; point <= pointsPerBlock; point++) {
		float voltage = readAverageVoltage(averageCount);
		printVoltagePoint("Ave1000_Point_", point, voltage);
		delay(200);
	}
}
