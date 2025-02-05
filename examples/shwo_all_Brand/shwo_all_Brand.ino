#include <WiFi.h> // Include WiFi library for ESP32 (use <ESP8266WiFi.h> for ESP8266)  
#include "IR_Data.h" // Include the custom IR_Data library for API interaction  

// Wi-Fi network credentials  
const char* ssid = "YOUR_SSID";  // Replace YOUR_SSID with your Wi-Fi network name  
const char* password = "YOUR_PASSWORD";  // Replace YOUR_PASSWORD with your Wi-Fi password  

Brand* brands;  // Pointer to an array to hold the retrieved brands  

void setup() {
    Serial.begin(115200); // Start the serial communication at 115200 baud rate  
    WiFi.begin(ssid, password); // Connect to the Wi-Fi network  

    // Wait until the ESP is connected to the Wi-Fi network  
    while (WiFi.status() != WL_CONNECTED) {
        delay(1000); // Wait for 1 second before trying again  
        Serial.println("Connecting to WiFi..."); // Print connection status  
    }
    Serial.println("Connected to WiFi"); // Print a message when connected  

    // Retrieve all brands using the Brand class  
    Brand brandObj; // Create an instance of the Brand class  
    brands = brandObj.getAll(); // Call the getAll method to fetch all brands  

    // Display the retrieved brands on the serial monitor  
    for (int i = 0; brands[i].ID != 0; i++) { // Loop through the brands until a brand with ID = 0 is found  
        Serial.print("Brand ID: "); // Print the label for the brand ID  
        Serial.print(brands[i].ID); // Print the brand ID  
        Serial.print(" - Brand Name: "); // Print the label for the brand name  
        Serial.println(brands[i].BrandName); // Print the brand name  
    }
}

void loop() {
    // The loop can be used for additional functionalities. Currently, it's empty.  
}
