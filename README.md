# Tim_hand_Final_Project
# Evaporation Cooling System

## Overview:
The Evaporation Cooling System project aims to create an energy-efficient cooling system based on evaporation principles. It utilizes components such as a DHT11 sensor for temperature and humidity monitoring, an LCD for displaying real-time data, a stepper motor for controlling the vent angle, and a DS1307 RTC module for timekeeping. The system is designed to:
- Monitor water levels and provide alerts when levels are low
- Display current temperature and humidity on an LCD screen
- Control a fan motor based on temperature thresholds
- Adjust the vent angle using a control
- Enable or disable the system with an on/off button
- Record the date and time each time the motor is turned on or off and transmit this information to a host computer over USB.

## Hardware Requirements:
1. Arduino Uno or compatible microcontroller board
2. DHT11 Temperature and Humidity Sensor
3. Liquid Crystal Display (LCD)
4. Stepper Motor
5. DS1307 RTC Module
6. Push Button (for on/off control)
7. Resistor, Capacitors, Wires, Breadboard, etc.

## Software Requirements:
1. Arduino IDE installed on your computer
2. Necessary libraries installed in the Arduino IDE:
   - dht (for DHT11 sensor)
   - LiquidCrystal (for LCD)
   - Stepper (for stepper motor)
   - Wire (for I2C communication)
   - RTClib (for DS1307 RTC module)

## Installation and Setup:
1. Connect the components as per the provided schematic.
2. Upload the Arduino code to the Arduino board using the Arduino IDE.
3. Ensure all connections are secure and power on the system.
4. Monitor the LCD screen for real-time temperature, humidity, and system status.
5. Use the provided on/off button to control the system's operation.
6. Connect the Arduino to a host computer via USB to record time and date data.

## Additional Notes:
- Ensure that the Arduino IDE is properly configured and set up with the correct board and port settings.
- Make sure to install the required libraries in the Arduino IDE before uploading the code.
- Check the serial monitor for debugging messages and system status updates.
- Adjust any thresholds or parameters in the code according to your specific requirements and environmental conditions.

By meeting these requirements and following the installation and setup instructions, you should be able to run the code properly and operate the evaporation cooling system effectively.
