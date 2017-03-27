# Configure the Event Hub
---

<a name="overview"></a>

## Overview

In this task you will configure the "**Azure Event Hub**" that will be used to forward "**alert**" messages for further processing.  In this tutorial, the "Stream Analytics" job, sends messages to this event hub if the Temperature reading is above 25 (25° Celsius). The "further processing" that is done with those alerts is nothing more than displaying them under the "Alerts" heading in the web app, but it could be an Azure Function, or some other back-end code that deals with the alerts.

"**Azure Event Hubs**" provide a powerful message queue that supports massive volume and multiple parallel readers at a low cost.  They are a great mechanism for forwarding data between layers of an application.

"**Azure Event Hubs**" are part of the "**Azure Service Bus**" family.  In fact, to create an Event Hub, you actually first create an "**Azure Service Bus Namespace**", and then within that namespace, you create one or more Event Hubs. It isn't obvious in the portal that this is what you are actually doing it, but knowing that up front may help you better what you are doing.

Follow these steps:

1. [Create the Event Hub](#step1)
1. 

--- 

<a name="step1"></a>

## Step 1



--- 

<a name="step2"></a>

## Step 2



--- 

<a name="step3"></a>

## Step 3



--- 

<a name="step4"></a>

## Step 4



---

<a name="sumnmary"></a>

## Summary and Next Step

In this task, you chose how you were going to name the resources you create in this lab by decided on a "**_`<name>`_**" prefix, you chose a the Location where all the resources would be created.  Then, in the Azure Portal, you created a new Dashboard to store all the tiles for the resources you create in a convenient place, and finally created an Azure Resource Group in which you will create all the resources.  

Next Step: [05-StreamAnalyticsJob](../05-StreamAnalyticsJob/README.md)