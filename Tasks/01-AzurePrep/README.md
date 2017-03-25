# Azure Prep

**_This is part of the <a target="_blank" href="http://aka.ms/aziot-huzesp-tut">"Azure IoT Adafruit Feather Huzzah ESP8266 Starter Kit Getting Started Tutorial"</a>. If you are coming into this task from somewhere else, you should <a target="_blank" href="http://aka.ms/aziot-huzesp-tut">start at the beginning</a>!_**

---

<a name="overview"></a>

## Overview

Throughout this tutorial, you will be creating a number of resources in Azure.  To help you manage the multiple resources, as well as to make it easy to clean up and delete those resources when you are done you should follow these steps:

1. Choose a Good Name for your Resources(#goodname)
1. Choose and Use a Single "Location"
1. Create a Portal Dashboard for your Resources
1. Create and Use a Single Resource Group

---
<a name="goodname"></a>

## Choose a Good Name for your Resources

The solution that you develop throughout this tutorial looks like this:

![Solution Architecture](../../Images/SolutionArchitecture.png)

If you look at the diagram above, you will see a number of resources that have names that match the "**_`<name>xxxx`_**" pattern.  These names are made up of a "**_`<name>`_**" prefix, and some resource type "**_`xxxx`_**" .  For example, "**_`<name>group`_**", "**_`<name>iothub`_**", "**_`<name>asajob`_**", "**_`<name>storage`_**" , etc.  It is **_strongly recommended that you conform to this naming convention as you work through this tutorial_**.  It will help you to understand what resources are being referred to in the documentation as well as help you to identify what each resource is when you see it in the portal, etc.

To use this naming convention though, you need to come up with a good "**_`<name>`_**" prefix for your resource names.  The "**_`<name>`_**" prefix you choose:

- Must be all lower case - some of the services, like Azure Storage Accounts, require their names to be all lower case.  To conform you should just user lower case in all instances.
- Must be alpha-numeric only, and start with a letter (no special characters, spaces, underlines, dashes, etc). These names are often used to make DNS Fully Qualified Domain Names (FQDN)s.  And as such your name should conform to DNS naming rules.


Following are some possible suggestions of how to come up with your own "**_`<name>`_**" prefix:

- A lower case single word version of your team name at a hackathon  For example if your team name was "iSaveWater", you might use "**_`isavewater`_**" as your "**_`<name>`_**".  Then your resource names would look something like  "**_`isavewatergroup`_**", "**_`isavewateriothub`_**", "**_`isavewaterasajob`_**", etc.
- Your first, middle and last initials along with your birth month and day in MMDD format.  For example, if your name were Jane Q. Doe and you were born of February 17th, you might use "**_`jqd0217`_**" as your "**_`<name>`_**" and have resource names like "**_`jqd0217group`_**", "**_`jqd0217iothub`_**", "**_`jqd0217asajob`_**", etc.

1. Use the information above to come up with a good name prefix




