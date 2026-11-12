#include <LiquidCrystal.h>

// LCD pin configuration: RS, E, D4, D5, D6, D7
LiquidCrystal lcd(12, 11, 10, 9, 8, 7);

// Analog sensor pins
const int voltagePin = A0;
const int currentPin = A1;

// Voltage divider resistors
const float R1 = 4000.0;
const float R2 = 1000.0;

// ACS712 5A sensitivity
const float sensitivity = 0.185; // V/A

// Nominal ACS712 zero-current output
const float zeroCurrentVoltage = 2.5;

// Arduino ADC reference voltage
const float referenceVoltage = 5.0;

void setup() {
  lcd.begin(20, 4);

  // Welcome screen 1
  lcd.setCursor(5, 0);
  lcd.print("WELCOME TO");
  lcd.setCursor(6, 1);
  lcd.print("FEC CSE");
  lcd.setCursor(0, 2);
  lcd.print("MICROCONTROLLER LAB");
  lcd.setCursor(4, 3);
  lcd.print("SOLAR PROJECT");
  delay(4000);
  lcd.clear();

  // Welcome screen 2
  lcd.setCursor(1, 1);
  lcd.print("Solar Monitoring");
  lcd.setCursor(3, 2);
  lcd.print("System Starting");
  delay(2000);
  lcd.clear();
}

void loop() {
  // 1. Read and average panel-voltage samples
  long voltageTotal = 0;
  for (int i = 0; i < 100; i++) {
    voltageTotal += analogRead(voltagePin);
    delay(2);
  }
  float voltageReading = voltageTotal / 100.0;
  float sensorVoltage = voltageReading * referenceVoltage / 1023.0;

  // Convert divider output to panel voltage
  float solarVoltage = sensorVoltage * (R1 + R2) / R2;

  // 2. Read and average ACS712 samples
  long currentTotal = 0;
  for (int i = 0; i < 100; i++) {
    currentTotal += analogRead(currentPin);
    delay(2);
  }
  float currentReading = currentTotal / 100.0;
  float currentSensorVoltage = currentReading * referenceVoltage / 1023.0;

  // Convert ACS712 output voltage to current
  float solarCurrent = (currentSensorVoltage - zeroCurrentVoltage) / sensitivity;

  // Display magnitude only; direction is not shown
  solarCurrent = abs(solarCurrent);

  // 3. Calculate electrical power
  float solarPower = solarVoltage * solarCurrent;

  // 4. Display values on the 20x4 LCD
  lcd.setCursor(0, 0);
  lcd.print("FEC CSE SOLAR SYSTEM");

  lcd.setCursor(0, 1);
  lcd.print("Voltage : ");
  lcd.print(solarVoltage, 2);
  lcd.print(" V  ");

  lcd.setCursor(0, 2);
  lcd.print("Current : ");
  lcd.print(solarCurrent, 2);
  lcd.print(" A  ");

  lcd.setCursor(0, 3);
  lcd.print("Power : ");
  lcd.print(solarPower, 2);
  lcd.print(" W  ");

  delay(1000);
}
