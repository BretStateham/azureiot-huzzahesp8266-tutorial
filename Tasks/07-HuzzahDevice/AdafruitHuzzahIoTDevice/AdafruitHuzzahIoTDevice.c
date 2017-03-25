///////////////////////////////////////////////////////////////////////////////////////////////////
// Copyright (c) Microsoft. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <stdlib.h>

#include <stdio.h>
#include <stdint.h>
#include <pgmspace.h>
#include <Arduino.h>
#include <time.h>

#include "dht22.h"
#include "AdafruitHuzzahIoTDevice.h"

/* This sample uses the _LL APIs of iothub_client for example purposes.
That does not mean that HTTP or MQTT only works with the _LL APIs.
Simply changing the using the convenience layer (functions not having _LL)
and removing calls to _DoWork will yield the same results. */

#include "AzureIoTHub.h"
#include "sdk/schemaserializer.h"

/* CODEFIRST_OK is the new name for IOT_AGENT_OK. The follow #ifndef helps during the name migration. Remove it when the migration ends. */
#ifndef  IOT_AGENT_OK
#define  IOT_AGENT_OK CODEFIRST_OK
#endif // ! IOT_AGENT_OK

// The Azure IoT Hub DeviceID and Connection String
//static const char DeviceId[] = "[DeviceId]";
//static const char connectionString[] = "[AzureIoTHubDevicePrimaryConnectionString";
static const char DeviceId[] = "huzzah01";
static const char connectionString[] = "HostName=creativedayiothub.azure-devices.net;DeviceId=huzzah01;SharedAccessKey=xsqBRQ3/hjPSDDDZWaEWbiNHdNRM2ZwSAiDEiowb/fA=";

// How frequently the Azure IoT Hub library should poll to receive messages (if any) as well as how often the simple_run_http() method should send messages.
unsigned int receiveFrequencySecs = 9;   //When using the HTTP protocol, this controls the minimum frequency in seconds the device polls for Cloud to Device messages.
unsigned int sendFrequencyMillis = 30000; //How frequently, in milliseconds, should it send messages

//IOTHUB_CLIENT_TRANSPORT_PROVIDER protocol = MQTT_Protocol;
IOTHUB_CLIENT_TRANSPORT_PROVIDER protocol = HTTP_Protocol;

//The pins that the red and green LEDs are connected to, and their iniial state (LOW=OFF, HIGH=ON if they are wired correctly)
static int redLedPin = 12;
static int redLedState = LOW;
static int greenLedPin = 13;
static int greenLedState = LOW;

// Define the Namespace and Model for the MyIoTDeviceModel.  This is used by the Azure IoT Hub SDK to serialize and deserialize messages from and to the device. 
// The "WITH_DATA" declarations define the data values in the messages the device sends
// The "WITH_ACTION" declarations define the actions that can be triggered on the device from the cloud
BEGIN_NAMESPACE(MyIoTDeviceNamespace);

DECLARE_MODEL(MyIoTDeviceModel,
WITH_DATA(ascii_char_ptr, DeviceId),
WITH_DATA(int, EventTime),
WITH_DATA(int, Temperature),
WITH_DATA(int, Humidity),
WITH_ACTION(ToggleGreenLed),
WITH_ACTION(ToggleRedLed)
);

END_NAMESPACE(MyIoTDeviceNamespace);

EXECUTE_COMMAND_RESULT ToggleRedLed(MyIoTDeviceModel* device)
{
    (void)device;

    LogInfo("Toggling red LED.\r\n");
    if (redLedState != LOW)
    {
        redLedState = LOW;
    }
    else
    {
        redLedState = HIGH;
    }
    digitalWrite(redLedPin, redLedState);

    return EXECUTE_COMMAND_SUCCESS;
}

EXECUTE_COMMAND_RESULT ToggleGreenLed(MyIoTDeviceModel* device)
{
    (void)device;

    LogInfo("Toggling green LED.\r\n");
    if (greenLedState != LOW)
    {
        greenLedState = LOW;
    }
    else
    {
        greenLedState = HIGH;
    }
    digitalWrite(greenLedPin, greenLedState);

    return EXECUTE_COMMAND_SUCCESS;
}

void sendCallback(IOTHUB_CLIENT_CONFIRMATION_RESULT result, void* userContextCallback)
{
    int messageTrackingId = (intptr_t)userContextCallback;

    LogInfo("Message Id: %d Received.\r\n", messageTrackingId);

    LogInfo("Result Call Back Called! Result is: %s \r\n", ENUM_TO_STRING(IOTHUB_CLIENT_CONFIRMATION_RESULT, result));
}

static void sendMessage(IOTHUB_CLIENT_LL_HANDLE iotHubClientHandle, const unsigned char* buffer, size_t size)
{
    static unsigned int messageTrackingId;
    IOTHUB_MESSAGE_HANDLE messageHandle = IoTHubMessage_CreateFromByteArray(buffer, size);
    if (messageHandle == NULL)
    {
        LogInfo("unable to create a new IoTHubMessage\r\n");
    }
    else
    {
        if (IoTHubClient_LL_SendEventAsync(iotHubClientHandle, messageHandle, sendCallback, (void*)(uintptr_t)messageTrackingId) != IOTHUB_CLIENT_OK)
        {
            LogInfo("failed to hand over the message to IoTHubClient");
        }
        else
        {
            LogInfo("IoTHubClient accepted the message for delivery\r\n");
        }
        IoTHubMessage_Destroy(messageHandle);
    }
    free((void*)buffer);
    messageTrackingId++;
}

/*this function "links" IoTHub to the serialization library*/
static IOTHUBMESSAGE_DISPOSITION_RESULT IoTHubMessage(IOTHUB_MESSAGE_HANDLE message, void* userContextCallback)
{
    LogInfo("Command Received\r\n");
    IOTHUBMESSAGE_DISPOSITION_RESULT result;
    const unsigned char* buffer;
    size_t size;
    if (IoTHubMessage_GetByteArray(message, &buffer, &size) != IOTHUB_MESSAGE_OK)
    {
        LogInfo("unable to IoTHubMessage_GetByteArray\r\n");
        result = EXECUTE_COMMAND_ERROR;
    }
    else
    {
        /*buffer is not zero terminated*/
        char* temp = malloc(size + 1);
        if (temp == NULL)
        {
            LogInfo("failed to malloc\r\n");
            result = EXECUTE_COMMAND_ERROR;
        }
        else
        {
            memcpy(temp, buffer, size);
            temp[size] = '\0';
            
            EXECUTE_COMMAND_RESULT executeCommandResult = EXECUTE_COMMAND(userContextCallback, temp);
            result =
                (executeCommandResult == EXECUTE_COMMAND_ERROR) ? IOTHUBMESSAGE_ABANDONED :
                (executeCommandResult == EXECUTE_COMMAND_SUCCESS) ? IOTHUBMESSAGE_ACCEPTED :
                IOTHUBMESSAGE_REJECTED;
            free(temp);
        }
    }
    return result;
}

void iot_device_run(void)
{
    initDht();

    digitalWrite(redLedPin, redLedState);
    pinMode(redLedPin, OUTPUT);
    
    digitalWrite(greenLedPin, greenLedState);
    pinMode(greenLedPin, OUTPUT);

    if (serializer_init(NULL) != SERIALIZER_OK)
    {
        LogInfo("Failed on serializer_init\r\n");
    }
    else
    {
        //IOTHUB_CLIENT_LL_HANDLE iotHubClientHandle = IoTHubClient_LL_CreateFromConnectionString(connectionString, protocol);
        IOTHUB_CLIENT_LL_HANDLE iotHubClientHandle = IoTHubClient_LL_CreateFromConnectionString(connectionString, protocol);
        srand((unsigned int)time(NULL));
        int avgWindSpeed = 10.0;

        if (iotHubClientHandle == NULL)
        {
            LogInfo("Failed on IoTHubClient_LL_Create\r\n");
        }
        else
        {
            //Set up the polling frequency for Cloud-to-Device messages.  
            //Set receiveFrequencySecs above to set the frequency
            //This is used only on the HTTP protocol
            //And determines how long it may take before a message from the cloud is received by the device.
            unsigned int minimumPollingTime = receiveFrequencySecs; 
            if (IoTHubClient_LL_SetOption(iotHubClientHandle, "MinimumPollingTime", &minimumPollingTime) != IOTHUB_CLIENT_OK)
            {
                LogInfo("failure to set option \"MinimumPollingTime\"\r\n");
            }

#ifdef MBED_BUILD_TIMESTAMP
            // For mbed add the certificate information
            if (IoTHubClient_LL_SetOption(iotHubClientHandle, "TrustedCerts", certificates) != IOTHUB_CLIENT_OK)
            {
                LogInfo("failure to set option \"TrustedCerts\"\r\n");
            }
#endif // MBED_BUILD_TIMESTAMP

            MyIoTDeviceModel* myDevice = CREATE_MODEL_INSTANCE(MyIoTDeviceNamespace, MyIoTDeviceModel);
            if (myDevice == NULL)
            {
                LogInfo("Failed on CREATE_MODEL_INSTANCE\r\n");
            }
            else
            {
                if (IoTHubClient_LL_SetMessageCallback(iotHubClientHandle, IoTHubMessage, myDevice) != IOTHUB_CLIENT_OK)
                {
                    LogInfo("unable to IoTHubClient_SetMessageCallback\r\n");
                }
                else
                {
                    
                    /* wait for commands */
                    long Prev_time_ms = millis();
                    char buff[11];
                    int timeNow = 0;

                    while (1)
                    {
                        long Curr_time_ms = millis();
                        if (Curr_time_ms >= Prev_time_ms + sendFrequencyMillis)
                        {
                            Prev_time_ms = Curr_time_ms;
                            
                            timeNow = (int)time(NULL);
    
                            //Get the temp and humidity readings from the dht22 sensor
                            float Temp_c__f, Humi_pct__f;
                            getNextSample(&Temp_c__f, &Humi_pct__f);

                            // Populate the model instance with the device id, 
                            // current time, temp and humidity values.
                            myDevice->DeviceId = DeviceId;
                            myDevice->EventTime = timeNow;
                            myDevice->Temperature = (int)Temp_c__f;
                            myDevice->Humidity = (int)Humi_pct__f;

                            // Log the info out to the console for monitoring / debugging purposes
                            LogInfo("Result: %s | %d | %d | %d \r\n", myDevice->DeviceId, myDevice->EventTime, myDevice->Temperature, myDevice->Humidity);
                        
                            unsigned char* messageBytes;
                            size_t messageSize;
                            
                            if (SERIALIZE(&messageBytes, &messageSize, myDevice->DeviceId, myDevice->EventTime, myDevice->Temperature, myDevice->Humidity) != IOT_AGENT_OK)
                            {
                                LogInfo("Failed to serialize\r\n");
                            }
                            else
                            {
                                IOTHUB_MESSAGE_HANDLE messageHandle = IoTHubMessage_CreateFromByteArray(messageBytes, messageSize);
                                if (messageHandle == NULL)
                                {
                                    LogInfo("unable to create a new IoTHubMessage\r\n");
                                }
                                else
                                {
                                    if (IoTHubClient_LL_SendEventAsync(iotHubClientHandle, messageHandle, sendCallback, (void*)1) != IOTHUB_CLIENT_OK)
                                    {
                                        LogInfo("failed to hand over the message to IoTHubClient\r\n");
                                    }
                                    else
                                    {
                                        LogInfo("IoTHubClient accepted the message for delivery\r\n");
                                    }
    
                                    IoTHubMessage_Destroy(messageHandle);
                                }
                                free(messageBytes);
                            }
                            
                        }
                        
                        IoTHubClient_LL_DoWork(iotHubClientHandle);
                        ThreadAPI_Sleep(100);
                    }
                }

                DESTROY_MODEL_INSTANCE(myDevice);
            }
            IoTHubClient_LL_Destroy(iotHubClientHandle);
        }
        serializer_deinit();
    }
}


