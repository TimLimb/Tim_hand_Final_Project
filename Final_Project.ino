#include <dht.h>
#include <LiquidCrystal.h>
#include <Stepper.h>
#include <Wire.h>     // Include Wire library for I2C communication
#include <RTClib.h>   // Include RTC library for DS1307

#define DHT11_PIN 7  // Define the pin to which the DHT sensor is connected
#define ENABLE 5
#define DIRA 3
#define DIRB 4
#define TEMP_THRESHOLD 26  // Define the temperature threshold
#define WATER_LEVEL_PIN A0  // Pin connected to the water level sensor
#define WATER_LEVEL_THRESHOLD 500  // Define the water level threshold

#define STEPPER_STEPS 200  // Number of steps per revolution
#define STEPPER_PIN_STEP 22  // Step pin
#define STEPPER_PIN_DIR 23   // Direction pin
#define STEPPER_PIN_EN 24    // Enable pin

const int stepsPerRevolution = 200;  // change this to fit the number of steps per revolution
const int rolePerMinute = 17;         // Adjustable range of 28BYJ-48 stepper is 0~17 rpm

dht DHT;
LiquidCrystal lcd(12, 11, 9, 8, 6, 2); // RS, EN, D4, D5, D6, D7
Stepper myStepper(stepsPerRevolution, 23, 25, 27, 29);

RTC_DS1307 rtc;

void setup() {
  Serial.begin(9600); // Start serial communication

  if (!rtc.begin()) {
    Serial.println("Couldn't find RTC");
    while (1);
  }

  if (!rtc.isrunning()) {
    Serial.println("RTC is not running, setting time...");
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__))); // Set the initial time and date to compile time
  }
  
  pinMode(ENABLE, OUTPUT);
  pinMode(DIRA, OUTPUT);
  pinMode(DIRB, OUTPUT);
  pinMode(STEPPER_PIN_EN, OUTPUT);
  
  digitalWrite(DIRA, HIGH); //one way
  digitalWrite(DIRB, LOW);
  digitalWrite(ENABLE, LOW); // enable off
  digitalWrite(STEPPER_PIN_EN, LOW); // Disable stepper motor
  
  lcd.begin(16, 2); // Initialize the LCD with 16 columns and 2 rows

  myStepper.setSpeed(rolePerMinute);
}

void loop() {
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
 
  
  // Read water level
  int waterLevel = analogRead(WATER_LEVEL_PIN);
  
  
  // Print water level to Serial Monitor
  if (waterLevel < 100) {
     Serial.print("Water Level: ");
     Serial.println(waterLevel);
  
  }
 
  // Check if temperature is above the threshold
  if (DHT.temperature > TEMP_THRESHOLD) {
    digitalWrite(ENABLE, HIGH); // Turn on the ENABLE pin
    //Serial.println("High temperature - turn on fan");
  } else {
    digitalWrite(ENABLE, LOW); // Keep the ENABLE pin off
    //Serial.println("Normal temperature - turn off fan");
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

  delay(2000); // Wait for 2 seconds for the sensor to stabilize
}

void openMotor() {
  Serial.println("Opening..");
  recordTime(); // Record time when motor opens
  myStepper.step(stepsPerRevolution);
  delay(500);
  Serial.println("Open.");
}

void closeMotor() {
  Serial.println("Closing..");
  recordTime(); // Record time when motor closes
  myStepper.step(-stepsPerRevolution);
  delay(500);
  Serial.println("Closed.");
}

void recordTime() {
  // Get the current time from RTC
  DateTime now = rtc.now();
  
  // Print the current date and time
  Serial.print("Time: ");
  Serial.print(now.hour());
  printDigits(now.minute());
  printDigits(now.second());
  Serial.print(" ");
  Serial.print(now.day());
  Serial.print("/");
  Serial.print(now.month());
  Serial.print("/");
  Serial.println(now.year());
}

void printDigits(int digits) {
  // Utility function to print leading 0
  if (digits < 10) {
    Serial.print('0');
  }
  Serial.print(digits);
}
