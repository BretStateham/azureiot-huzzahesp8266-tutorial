-- Forward all valid messages
-- to Azure Table Storage
SELECT
    DeviceId,
    EventTime,
    Temperature,
    Humidity
INTO
    TemperatureTableStorage
from TempSensors
WHERE
   DeviceId is not null
   and EventTime is not null

-- Forward messages that have
-- Temperatures over 25c to
-- The event hub
SELECT
    DeviceId,
    EventTime,
    Temperature,
    Humidity
INTO   
    TemperatureAlertToEventHub
FROM
    TempSensors
WHERE Temperature>25