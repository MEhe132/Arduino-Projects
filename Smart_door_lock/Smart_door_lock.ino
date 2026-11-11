#include <Keypad.h>
#include <LiquidCrystal.h>
#include <Servo.h>
// 1. KEYPAD CONFIGURATION
const byte ROWS = 4;
const byte COLS = 3;
char keys[ROWS][COLS] = {
  { '1', '2', '3' },
  { '4', '5', '6' },
  { '7', '8', '9' },
  { '*', '0', '#' }
};
byte rowPins[ROWS] = { 9, 8, 7, 6 };
byte colPins[COLS] = { 5, 4, 3 };
Keypad keypad = Keypad(
  makeKeymap(keys),
  rowPins,
  colPins,
  ROWS,
  COLS);
// 2. LCD CONFIGURATION
LiquidCrystal lcd(12, 11, 10, A0, A1, A2);
// 3. SERVO CONFIGURATION
Servo lockServo;
const int servoPin = A3;
const int LOCK_POSITION = 0;
const int UNLOCK_POSITION = 90;
// 4. PASSWORD CONFIGURATION
String password = "1234";
String input = "";
// 5. DISPLAY PASSWORD PROMPT
void passwordScreen() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Enter Password:");
  lcd.setCursor(0, 1);
  lcd.print("Pass: ");
}
// 6. DISPLAY WELCOME MESSAGE
void welcomeScreen() {
  lcd.clear();
  lcd.setCursor(1, 0);
  lcd.print("Welcome To");
  lcd.setCursor(0, 1);
  lcd.print("Smart Door Lock");
  delay(2000);
  passwordScreen();
}
// 7. INITIALIZATION
void setup() {
  lcd.begin(16, 2);
  lockServo.attach(servoPin);
  lockServo.write(LOCK_POSITION);
  welcomeScreen();
}
// 8. MAIN PROGRAM
void loop() {
  char key = keypad.getKey();
  if (key) {
    // SUBMIT PASSWORD
    if (key == '#') {
      if (input == password) {
        // Correct password
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Access Granted");
        lcd.setCursor(0, 1);
        lcd.print("Door Unlocked");
        lockServo.write(UNLOCK_POSITION);
        delay(5000);
        lockServo.write(LOCK_POSITION);
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Door Locked");
        delay(1500);
      } else {
        // Incorrect password
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Wrong Password!");

        lcd.setCursor(0, 1);
        lcd.print("Access Denied");
        delay(2000);
      }
      input = "";
      passwordScreen();
    }
    // CLEAR INPUT
    else if (key == '*') {
      input = "";
      lcd.setCursor(0, 1);
      lcd.print(" ");
      lcd.setCursor(0, 1);
      lcd.print("Pass: ");
    }
    // ADD A PASSWORD DIGIT
    else {
      if (input.length() < 8) {
        input += key;
        lcd.setCursor(6 + input.length() - 1, 1);
        lcd.print("*");
      }
    }
  }
}