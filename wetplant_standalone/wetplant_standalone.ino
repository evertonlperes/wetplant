const int moistureSensorPin = A0;
const int redPin = 9;
const int yellowPin = 10;
const int greenPin = 11;
const int bluePin = 12;  // Water pump LED indicator.
const int relayPin = 8;  // Assuming the relay is connected to pin 8

const int dryThreshold = 45;    // Adjust based on calibration
const int moistThreshold = 35;  // Adjust based on calibration
const int veryMoistThreshold = 20;

bool pumpOn = false;  // Track if the pump is already on

void setup() {
  pinMode(moistureSensorPin, INPUT);
  pinMode(redPin, OUTPUT);
  pinMode(yellowPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  pinMode(relayPin, OUTPUT);

  Serial.begin(9600);  // Initialize serial communication
}

void loop() {
  int moistureLevel = map(analogRead(moistureSensorPin), 0, 1023, 0, 100);

  // Print the moisture level to the Serial Monitor
  Serial.print("Moisture Level: ");
  Serial.println(moistureLevel);

  // Display moisture level on the LCD (if LCD is connected)

  if (moistureLevel <= veryMoistThreshold) {
    // Very Moist
    digitalWrite(redPin, LOW);
    digitalWrite(yellowPin, LOW);
    digitalWrite(greenPin, HIGH);
    Serial.println("Moisture Level: Very Moist");
  } else if (moistureLevel <= moistThreshold) {
    // Moist
    digitalWrite(redPin, LOW);
    digitalWrite(yellowPin, HIGH);
    digitalWrite(greenPin, LOW);
    Serial.println("Moisture Level: Moist");
  } else {
    // Dry
    digitalWrite(greenPin, LOW);
    digitalWrite(yellowPin, LOW);
    digitalWrite(redPin, HIGH);  // Red LED stays on
    if (moistureLevel <= dryThreshold) {
      if (!pumpOn) {
        Serial.println("Moisture Level: Dry - Watering plant");
        // Turn on the pump if it's too dry and it's not already on
        digitalWrite(relayPin, LOW);  // Assuming LOW turns on the relay
        digitalWrite(bluePin, HIGH);   // Turn ON LED
        
        pumpOn = true;                 // Pump is now on
        delay(10000);                // Keep pump running for 10 seconds
        digitalWrite(bluePin, LOW);  // Turn off the blue LED after watering
        pumpOn = false;
        Serial.println("Stopped watering plant");
      }
    } else {
      if (pumpOn) {
        // Turn off the pump if it's no longer too dry and the pump is on
        digitalWrite(relayPin, HIGH); // Assumming HIGH turns off the relay
        digitalWrite(bluePin, LOW);
        pumpOn = false;  // Pump is now off
        Serial.println("Stopped watering plant");
      }
    }
  }

  delay(1000);  // Adjust delay time as needed for your application
}
