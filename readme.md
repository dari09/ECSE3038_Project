#Project Description
This code is part of a class project to build an IoT platform that controls simple appliances typically controlled by a switch. The project focuses on controlling lighting appliances (e.g., lamps, in-wall lighting fixtures) and cooling/heating appliances (e.g., fans, air conditioning units).

The code performs the following tasks:

It includes necessary libraries such as Arduino.h, WiFi.h, HTTPClient.h, and ArduinoJson.h to enable communication and data handling.
It defines variables for API endpoints and pin numbers for connecting the appliances.
The setup() function initializes the serial communication and sets up the pin modes and connects to the Wi-Fi network.
The switchLightAndFan() function controls the state of the light and fan appliances based on the provided Boolean values.
The sendPutRequest() function performs a PUT request to update the temperature data on the IoT platform.
The handleGetResponse() function parses the JSON response received from the GET request and controls the state of the appliances accordingly.
The sendGetRequest() function performs a GET request to retrieve the current state of the appliances from the IoT platform.
The loop() function continuously executes the main logic of the code, including sending a PUT request with a random temperature, retrieving the state of the appliances through a GET request, and controlling the appliances based on the received state.
Overall, the code combines the functionalities of sending temperature data to the IoT platform using a PUT request and retrieving the current state of the appliances from the platform using a GET request. It demonstrates the control of simple appliances through the platform based on the received state information.




