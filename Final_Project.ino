#include <dht.h>

#define DHT11_PIN 7  // Define the pin to which the DHT sensor is connected
#define ENABLE 5
#define DIRA 3
#define DIRB 4
#define TEMP_THRESHOLD 22  // Define the temperature threshold

dht DHT;

void setup() {
  Serial.begin(9600); // Start serial communication
  
  pinMode(ENABLE,OUTPUT);
  pinMode(DIRA,OUTPUT);
  pinMode(DIRB,OUTPUT);

  digitalWrite(DIRA,HIGH); //one way
  digitalWrite(DIRB,LOW);
  digitalWrite(ENABLE,LOW); // enable off
}

void loop() {
  delay(2000); // Wait for 2 seconds for the sensor to stabilize

  int chk = DHT.read11(DHT11_PIN);

  Serial.print("Temperature = ");
  Serial.println(DHT.temperature);

  Serial.print("Humidity = ");
  Serial.println(DHT.humidity);

  // Check if temperature is above the threshold
  if (DHT.temperature > TEMP_THRESHOLD) {
    digitalWrite(ENABLE, HIGH); // Turn on the ENABLE pin
  } else {
    digitalWrite(ENABLE, LOW); // Keep the ENABLE pin off
  }
}
