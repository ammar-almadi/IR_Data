#include <WiFi.h> // Include WiFi library for ESP32 or <ESP8266WiFi.h> for ESP8266  
#include "IR_Data.h" // Include the custom IR_Data library for API interaction  

// Wi-Fi network credentials  
const char* ssid = "YOUR_SSID";  // Replace YOUR_SSID with your Wi-Fi network name  
const char* password = "YOUR_PASSWORD"; // Replace YOUR_PASSWORD with your Wi-Fi password  

void setup() {
    Serial.begin(115200); // Start the serial communication at 115200 baud rate  
    WiFi.begin(ssid, password); // Connect to the Wi-Fi network  

    // Wait until the ESP is connected to the Wi-Fi network  
    while (WiFi.status() != WL_CONNECTED) {
        delay(1000); // Wait for 1 second before trying again  
        Serial.println("Connecting to WiFi..."); // Print connection status  
    }
    Serial.println("Connected to WiFi"); // Print a message when connected  
}

void loop() {
    // Prompt the user for input  
    Serial.println("Enter DataIr ID:"); // Ask for ID input  
    while (Serial.available() == 0) { // Wait for user input  
        // Do nothing, just wait  
    }

    int dataIrId = Serial.parseInt(); // Read the integer input from Serial  
    if (dataIrId > 0) { // Ensure that the entered ID is valid (greater than 0)  
        DataIr dataIrObj;
        DataIr result = dataIrObj.Data_ById(dataIrId); // Fetch DataIr by ID  

        // Print the result  
        Serial.print("Data ID: ");
        Serial.println(result.Id); // Print the ID of the retrieved DataIr  
        Serial.print("Device ID: ");
        Serial.println(result.IdDevice); // Print the associated Device ID  
        Serial.print("Name Key: ");
        Serial.println(result.NameKey); // Print the Name Key  
        Serial.print("Data: ");
        Serial.println(result.Data); // Print the Data  
    }
    else {
        Serial.println("Invalid ID entered. Please try again."); // Show error for invalid ID  
    }

    // Wait before prompting for the next ID  
    Serial.println("Press a key to enter another ID or reset the device to exit.");

    // Wait for the user to press a key before continuing  
    while (Serial.available() == 0) {
        // Do nothing, just wait for user to reset  
    }
}
