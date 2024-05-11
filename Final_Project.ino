#include <dht.h>

#define DHT11_PIN 7  // Define the pin to which the DHT sensor is connected


dht DHT;

void setup() {
  Serial.begin(9600); // Start serial communication

}

void loop() {
  delay(2000); // Wait for 2 seconds for the sensor to stabilize

 int chk = DHT.read11(DHT11_PIN);

 Serial.print("Temperature = ");
 Serial.println(DHT.temperature);

 Serial.print("Humidity =");
 Serial.println(DHT.humidity);

}
