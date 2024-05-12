#include <dht.h>
#include <LiquidCrystal.h>
#include <Stepper.h>

#define DHT11_PIN 7  // Define the pin to which the DHT sensor is connected
#define ENABLE 5
#define DIRA 3
#define DIRB 4
#define TEMP_THRESHOLD 22  // Define the temperature threshold
#define WATER_LEVEL_PIN A0  // Pin connected to the water level sensor
#define WATER_LEVEL_THRESHOLD 500  // Define the water level threshold

#define STEPPER_STEPS 200  // Number of steps per revolution
#define STEPPER_PIN_STEP 22  // Step pin
#define STEPPER_PIN_DIR 23   // Direction pin
#define STEPPER_PIN_EN 24    // Enable pin

#define PUSH_BUTTON_PIN 21 // Push button pin (change to the appropriate pin)

const int stepsPerRevolution = 200;  // change this to fit the number of steps per revolution
const int rolePerMinute = 17;         // Adjustable range of 28BYJ-48 stepper is 0~17 rpm

dht DHT;
LiquidCrystal lcd(12, 11, 9, 8, 6, 2); // RS, EN, D4, D5, D6, D7
Stepper myStepper(stepsPerRevolution, 23, 25, 27, 29);
bool systemOn = false;

void setup() {
  Serial.begin(9600); // Start serial communication
  
  pinMode(ENABLE, OUTPUT);
  pinMode(DIRA, OUTPUT);
  pinMode(DIRB, OUTPUT);
  pinMode(STEPPER_PIN_EN, OUTPUT);
  pinMode(PUSH_BUTTON_PIN, INPUT_PULLUP); // Set push button pin as input with internal pull-up resistor
  
  digitalWrite(DIRA, HIGH); //one way
  digitalWrite(DIRB, LOW);
  digitalWrite(ENABLE, LOW); // enable off
  digitalWrite(STEPPER_PIN_EN, LOW); // Disable stepper motor
  
  lcd.begin(16, 2); // Initialize the LCD with 16 columns and 2 rows

  myStepper.setSpeed(rolePerMinute);

  // Attach interrupt to push button pin
  attachInterrupt(digitalPinToInterrupt(PUSH_BUTTON_PIN), toggleSystem, FALLING);
}

void loop() {
  if (systemOn) {
    // Clear the LCD screen
    lcd.clear();
    
    // Set cursor to first row, first column
    lcd.setCursor(0, 0);
    
    // Read temperature and humidity
    int chk = DHT.read11(DHT11_PIN);
  
    // Print temperature and unit on LCD
    lcd.print("Temp: ");
    lcd.print(DHT.temperature);
    lcd.print(" C");
  
    // Set cursor to second row, first column
    lcd.setCursor(0, 1);
    
    // Print humidity and unit on LCD
    lcd.print("Humidity: ");
    lcd.print(DHT.humidity);
    lcd.print("%");
    
    // Print temperature and humidity to Serial Monitor
    Serial.print("Temperature: ");
    Serial.print(DHT.temperature);
    Serial.println(" C");
  
    Serial.print("Humidity: ");
    Serial.print(DHT.humidity);
    Serial.println("%");
  
    // Read water level
    int waterLevel = analogRead(WATER_LEVEL_PIN);
  
    // Print water level to LCD
    lcd.setCursor(0, 2);
    lcd.print("Water Level: ");
    lcd.print(waterLevel);
  
    // Print water level to Serial Monitor
    Serial.print("Water Level: ");
    Serial.println(waterLevel);
  
    // Check if temperature is above the threshold
    if (DHT.temperature > TEMP_THRESHOLD) {
      digitalWrite(ENABLE, HIGH); // Turn on the ENABLE pin
      Serial.println("High temperature - turn on fan");
    } else {
      digitalWrite(ENABLE, LOW); // Keep the ENABLE pin off
      Serial.println("Normal temperature - turn off fan");
    }
  
    // Check for serial input to control the stepper motor
    if (Serial.available() > 0) {
      char inputVariable = Serial.read();
      if (inputVariable == 'o') {
        openMotor();
      } else if (inputVariable == 'c') {
        closeMotor();
      }
    }
  } else {
    // Turn off all systems
    digitalWrite(ENABLE, LOW); // Disable fan
    digitalWrite(STEPPER_PIN_EN, LOW); // Disable stepper motor
  }

  delay(2000); // Wait for 2 seconds for the sensor to stabilize
}

void openMotor() {
  Serial.println("Opening..");
  myStepper.step(stepsPerRevolution);
  delay(500);
  Serial.println("Open.");
}

void closeMotor() {
  Serial.println("Closing..");
  myStepper.step(-stepsPerRevolution);
  delay(500);
  Serial.println("Closed.");
}

void toggleSystem() {
  // Interrupt service routine for toggling the system
  systemOn = !systemOn;
  delay(500); // Debounce delay
}
