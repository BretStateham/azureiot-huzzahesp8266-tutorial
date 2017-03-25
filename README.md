# Azure IoT Adafruit Feather Huzzah ESP8266 Starter Kit Getting Started Tutorial

***THIS IS NOT THE OFFICIAL GETTING STARTED WALK THROUGH!  For the official tutorial see <a target="_blank" href="https://github.com/Azure-Samples/iot-hub-c-huzzah-getstartedkit">https://github.com/Azure-Samples/iot-hub-c-huzzah-getstartedkit</a>***

This is my variation on the Adafruit Huzzah ESP8266 Azure IoT Starter Kit getting started walkthrough.  I created this version to help clarify the code from the official tutorial and make it easier to understand what you would need to modify it for your own use.

I also wanted to be able to look at alternative flows for the message data in Azure including the use of IoT Hub Routes, Azure Functions, logic apps and more.

## Prerequisites

- **"Adafruit Feather HUZZAH ESP8266 Kit" Azure IoT Starter Kit** -This lab is based on the kit from Adafruit.  You can buy one from  <a target="_blank" href="https://www.adafruit.com/products/3032">"https://www.adafruit.com/products/3032</a>**.  If you don't have the complete kit, you can still work through this lab with the following items:
    - An Arduino IDE compatible ESP8266 module (you will need to follow your modules instructions for configuring it and deploying code to it)
    - A DHT22 Temperature and Humidity sensor and 10Kohm pullup resistor
    - A Red LED and 330ohm current limiting resistor
    - A Green LED and 330ohm current limiting resistor
    - Various jumpers
    - Breadboard
    - Additional components as needed

- **A personal computer running Windows, OS X, or Linux**. There are one or two tools that only work on Windows, but they are not critical to the overall lab.

- **The Arduino IDE v1.6.8 or later**.  You cand download it for free from <a target="_blank" href="https://www.arduino.cc/en/Main/Software">https://www.arduino.cc/en/Main/Software</a>

- **An active Azure subscription**.  If you don't have one currently, you can create a free one at <a target="_blank" href="http://azure.com/free">http://azure.com/free</a>.  If you have signed and used the free trial in the past, you can create a new one by:

    - Opening an "icognito" or "private" browser session (`Ctrl-Shift-N` in Chrome, `Ctrl-Shift-P` in Edge).
    - Sign up for a ***new*** outlook.com email address at <a target="_blank" href="http://outlook.com">http://outlook.com</a>
    - Staying in your private browser sessions, use that new outlook.com account to sign up for the Azure Free trial at <a target="_blank" href="">http://azure.com/free</a>
    - You will be asked for a credit card during sign up, but it is used only for identification purposes and you will not be billed anything unless you convert your free trial to a pay-as-you-go subscription.

- **Visual Studio Code**.  You can download it for free from <a target="_blank" href="http://code.visualstudio.com">http://code.visualstudio.com</a>

- **Node.js 4.x or higher**.  You can download Node.js for free from <a target="_blank" href="https://nodejs.org/en/">https://nodejs.org/en/</a>

- **Azure CLI 1.0 based on Node.js** (NOT THE Azure CLI 2.0 Based on Python).  Read how to Install the Azure CLI 1.0 here: <a target="_blank" href="https://docs.microsoft.com/en-us/azure/cli-install-nodejs">https://docs.microsoft.com/en-us/azure/cli-install-nodejs</a>.  However, if you already have Node.js 4.x or later installed, from a command prompt you can run:

    ```bash
    npm install -g azure-cli
    ```

- **iothub-explorer CLI**. Learn more about it and how to install it here: <a target="_blank" href="https://github.com/Azure/iothub-explorer/blob/master/readme.md">https://github.com/Azure/iothub-explorer/blob/master/readme.md</a>.  Basically though once you have Node.js 4.x or higher installed, you can simply install the iothub-explorer from the command line:

    ```bash
    npm install -g iothub-explorer
    ```
- **Git**.  You can download git for free from <a target="_blank" href="https://git-scm.com/">https://git-scm.com/</a>
    
    - Make sure you have configured your git user name and email address:

    ```bash
    git config --global user.name "<your name>"
    git config --global user.email "<your email addr>"
    ```

- **Additional debugging and monitoring tools**:

    - **Microsoft Azure Storage Explorer**.  A great cross-platform tool for working with your Azure Storage Accounts.  Get it for free from <a target="_blank" href="http://storageexplorer.com/">http://storageexplorer.com/</a>

    - **Service Bus Explorer** (WINDOWS ONLY).  An excellent tool for monitoring all Azure Service Bus technologies.  For this tutorial, it's helpful for monitoring Azure Event Hubs and Azure IoT Hub Events endpoints.  Download it for free from <a target="_blank" href="https://code.msdn.microsoft.com/windowsapps/Service-Bus-Explorer-f2abca5a">https://code.msdn.microsoft.com/windowsapps/Service-Bus-Explorer-f2abca5a</a> . The downloaded .zip file includes a Visual Studio 2013 C# project.  ***You DON'T NEED to open it in Visual Studio to run it***, you can just extract the .zip file, then under the folder where you extracted it go to the "`\C#\bin\Debug\`" folder and from there run "`ServiceBusExplorer.exe`".

    - **Device Explorer** (WINDOWS ONLY) - The **iothub-explorer CLI** is a great tool for working with your Azure IoT Hubs and devices from the command line, but it if you prefer a graphical interface, then you may like "Device Explorer".  Learn how to install it and use it here: <a target="_blank" href="https://github.com/Azure/azure-iot-sdk-csharp/blob/master/tools/DeviceExplorer/readme.md">https://github.com/Azure/azure-iot-sdk-csharp/blob/master/tools/DeviceExplorer/readme.md</a>





