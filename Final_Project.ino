#include <dht.h>
#include <LiquidCrystal.h>

#define DHT11_PIN 7  // Define the pin to which the DHT sensor is connected
#define ENABLE 5
#define DIRA 3
#define DIRB 4
#define TEMP_THRESHOLD 22  // Define the temperature threshold
#define WATER_LEVEL_PIN A0  // Pin connected to the water level sensor
#define WATER_LEVEL_THRESHOLD 500  // Define the water level threshold

dht DHT;

LiquidCrystal lcd(12,11,9,8,6,2); // RS, EN, D4, D5, D6, D7

void setup() {
  Serial.begin(9600); // Start serial communication
  
  pinMode(ENABLE,OUTPUT);
  pinMode(DIRA,OUTPUT);
  pinMode(DIRB,OUTPUT);

  digitalWrite(DIRA,HIGH); //one way
  digitalWrite(DIRB,LOW);
  digitalWrite(ENABLE,LOW); // enable off
  
  lcd.begin(16, 2); // Initialize the LCD with 16 columns and 2 rows
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

  delay(2000); // Wait for 2 seconds for the sensor to stabilize
}
