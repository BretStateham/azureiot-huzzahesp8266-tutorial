// Copyright (c) Microsoft. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

// This example only works with Arduino IDE 1.6.8 or later.

#include "AdafruitHuzzahIoTDevice.h"

///////////////////////////////////////////////////////////////////////////////////////////////////
// ESP8266 Related Includes and Declarations
// ------------------------------------------------------------------------------------------------
#include <ESP8266WiFi.h>
#include <time.h>
#ifdef ARDUINO_ARCH_ESP8266
static WiFiClientSecure sslClient; // for ESP8266
#elif ARDUINO_SAMD_FEATHER_M0
static Adafruit_WINC1500SSLClient sslClient; // for Adafruit WINC1500
#else
static WiFiSSLClient sslClient;
#endif

///////////////////////////////////////////////////////////////////////////////////////////////////
// Azure IoT Hubs related includes and Declarations
// ------------------------------------------------------------------------------------------------
#include <AzureIoTHub.h>
#include <AzureIoTProtocol_MQTT.h>
#include <AzureIoTProtocol_HTTP.h>

static AzureIoTHubClient iotHubClient;

///////////////////////////////////////////////////////////////////////////////////////////////////
// WiFi SSID and Password
// ------------------------------------------------------------------------------------------------
//const char ssid[] = "[SSID]"; //  your WiFi SSID (name)
//const char pass[] = "[PASSWORD}";    // your WiFi password (use for WPA, or use as key for WEP)
const char ssid[] = "PhotonWiFi2"; //  your WiFi SSID (name)
const char pass[] = "12345678";    // your WiFi password (use for WPA, or use as key for WEP)

int status = WL_IDLE_STATUS;

///////////////////////////////////////////////////////////////////////////////////////////////////
void setup() {
    initSerial();
    initWifi();
    initTime();

}

///////////////////////////////////////////////////////////////////////////////////////////////////
void loop() {
    // This function doesn't exit.
    iot_device_run();
}

///////////////////////////////////////////////////////////////////////////////////////////////////
void initSerial() {
    // Start serial and initialize stdout
    Serial.begin(115200);
    Serial.setDebugOutput(true);
}

///////////////////////////////////////////////////////////////////////////////////////////////////
void initWifi() {
    // Attempt to connect to Wifi network:
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(ssid);

    // Connect to WPA/WPA2 network. Change this line if using open or WEP network:
    // Ensure at the ssid and pass variables were initialized with appropriate values above.
    status = WiFi.begin(ssid, pass);

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }

    Serial.println("Connected to wifi");
}

///////////////////////////////////////////////////////////////////////////////////////////////////
void initTime() {
    //We need to have a valid time to be able to send messages to the Azure IoT Hub. 
    time_t epochTime;

    //Configure the ESP8266 time library to use specific time servers
    configTime(0, 0, "pool.ntp.org", "time.nist.gov");

    while (true) {
        //attempt to retrieve the current time from the configured time servers
        epochTime = time(NULL);

        if (epochTime == 0) {
            //If we didn't get a valid time from the servers, wait two seconds and try again.
            Serial.println("Fetching NTP epoch time failed! Waiting 2 seconds to retry.");
            delay(2000);
        } else {
            //Otherwise, if we got a valid time, exit the loop.
            Serial.print("Fetched NTP epoch time is: ");
            Serial.println(epochTime);
            break;
        }
    }
}

