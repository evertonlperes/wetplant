// const int moistureSensorPin = A0;
// const int redPin = 9;
// const int yellowPin = 10;
// const int greenPin = 8;

// const int dryThreshold = 45;    // Adjust based on calibration
// const int moistThreshold = 35;  // Adjust based on calibration
// const int veryMoistThreshold = 20;

// void setup() {
//   pinMode(moistureSensorPin, INPUT);
//   pinMode(redPin, OUTPUT);
//   pinMode(yellowPin, OUTPUT);
//   pinMode(greenPin, OUTPUT);

//   Serial.begin(9600);  // Initialize serial communication
// }

// void loop() {
//   // int moistureLevel = analogRead(moistureSensorPin);
//   int moistureLevel = map(analogRead(moistureSensorPin), 0, 1023, 0, 100);

//   // Print the moisture level to the Serial Monitor
//   Serial.print("Moisture Level: ");
//   Serial.println(moistureLevel);

//   if (moistureLevel < veryMoistThreshold) {
//     // Very Moist
//     digitalWrite(redPin, LOW);
//     digitalWrite(yellowPin, HIGH);
//     digitalWrite(greenPin, LOW);
//     Serial.println("Moisture Level: Very Moist");
//   } else if (moistureLevel < moistThreshold) {
//     // Moist
//     digitalWrite(redPin, LOW);
//     digitalWrite(yellowPin, LOW);
//     digitalWrite(greenPin, HIGH);
//     Serial.println("Moisture Level: Moist");
//   } else if (moistureLevel < dryThreshold) {
//     // Dry
//     digitalWrite(redPin, HIGH);
//     digitalWrite(yellowPin, LOW);
//     digitalWrite(greenPin, LOW);
//     Serial.println("Moisture Level: Dry");
//   } else {
//     digitalWrite(redPin, LOW);
//     digitalWrite(yellowPin, LOW);
//     digitalWrite(greenPin, LOW);
//     Serial.println("Something went wrong.. measuring again... :/ ");
//   }

//   delay(1000);  // Adjust delay time as needed for your application
// }



#include <LiquidCrystal.h>

const int moistureSensorPin = A0;
const int redPin = 9;
const int yellowPin = 10;
const int greenPin = 11;

const int dryThreshold = 45;    // Adjust based on calibration
const int moistThreshold = 35;  // Adjust based on calibration
const int veryMoistThreshold = 20;

LiquidCrystal lcd(12, 11, 5, 4, 3, 2); // Initialize the LCD library with the numbers of the interface pins

void setup() {
  pinMode(moistureSensorPin, INPUT);
  pinMode(redPin, OUTPUT);
  pinMode(yellowPin, OUTPUT);
  pinMode(greenPin, OUTPUT);

  lcd.begin(16, 2); // Initialize the LCD with 16 columns and 2 rows
  lcd.clear(); // Clear the LCD screen

  Serial.begin(9600);  // Initialize serial communication
}

void loop() {
  int moistureLevel = map(analogRead(moistureSensorPin), 0, 1023, 0, 100);

  // Print the moisture level to the Serial Monitor
  Serial.print("Moisture Level: ");
  Serial.println(moistureLevel);

  // Display moisture level on the LCD
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Moisture Level:");
  lcd.setCursor(0, 1);
  lcd.print(moistureLevel);
  lcd.print("%");

  if (moistureLevel < veryMoistThreshold) {
    // Very Moist
    digitalWrite(redPin, LOW);
    digitalWrite(yellowPin, HIGH);
    digitalWrite(greenPin, LOW);
    Serial.println("Moisture Level: Very Moist");
  } else if (moistureLevel < moistThreshold) {
    // Moist
    digitalWrite(redPin, LOW);
    digitalWrite(yellowPin, LOW);
    digitalWrite(greenPin, HIGH);
    Serial.println("Moisture Level: Moist");
  } else if (moistureLevel <= dryThreshold) {
    // Dry
    digitalWrite(redPin, HIGH);
    digitalWrite(yellowPin, LOW);
    digitalWrite(greenPin, LOW);
    Serial.println("Moisture Level: Dry");
  } else {
    digitalWrite(redPin, LOW);
    digitalWrite(yellowPin, LOW);
    digitalWrite(greenPin, LOW);
    Serial.println("Something went wrong.. measuring again... :/ ");
  }

  delay(1000);  // Adjust delay time as needed for your application
}
