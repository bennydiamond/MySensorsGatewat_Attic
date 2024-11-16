#include "SensorsReader.h"
#include <Arduino.h>

auto const NoInvert = false;
auto const Invert = true;
auto const DoorSensorPin = 6;
auto const SHT21_Temperature_Calibration = -5.8;
auto const SHT21_Humidity_Calibration = 18.6;
auto const ForceUpdate = true;

SensorsReader::SensorsReader() :
m_sht(),
m_trapDoor(DOORSENSOR_CHILD_ID, V_TRIPPED),
m_temperature1(TEMPERATURE_CHILD_ID, V_TEMP),
m_humidity1(HUMIDITY_CHILD_ID, V_HUM),
m_climateSensorTimer(0),
m_doorDebounceTimer(0),
m_previousDoorSensor(0),
m_previousMillis(0)
{

}

void SensorsReader::init (void)
{
  Wire.begin();
  m_sht.begin();

  pinMode(DoorSensorPin, INPUT_PULLUP);
  m_previousDoorSensor = !digitalRead(DoorSensorPin);
}

void SensorsReader::presentSensors (void)
{
// Register binary input sensor to sensor_node (they will be created as child devices)
	// You can use S_DOOR, S_MOTION or S_LIGHT here depending on your usage.
	// If S_LIGHT is used, remember to update variable type you send in. See "msg" above.
	present(DOORSENSOR_CHILD_ID, S_DOOR);
	present(TEMPERATURE_CHILD_ID, S_TEMP);
  present(HUMIDITY_CHILD_ID, S_HUM);
}

void SensorsReader::loop (void)
{
  auto const current = millis();
  if(m_previousMillis != current)
  {
    m_previousMillis = current;

    if(m_doorDebounceTimer)
    {
      m_doorDebounceTimer--;
    }
    else
    {
      if(readPublishDoor())
      {
        m_doorDebounceTimer = DoorDebounceTimerResetValue_ms;
      }
    }

    if(m_climateSensorTimer)
    {
      m_climateSensorTimer--;
    }
    else
    {
      readPublishClimate();
      m_climateSensorTimer = ClimateSensorTimerResetValue_ms;
    }
  }
}

void SensorsReader::readPublishClimate (void)
{
  char szTemp[10];
  char szHumi[10];

  dtostrf(m_sht.getTemperature() + SHT21_Temperature_Calibration, 2, 2, szTemp);
  dtostrf(m_sht.getHumidity() + SHT21_Humidity_Calibration, 2, 2, szHumi);
  //Serial.print(szTemp);
  //Serial.print(F("°C,  "));
  //Serial.print(szHumi);
  //Serial.println(F("%"));

  send(m_temperature1.set(szTemp));
  send(m_humidity1.set(szHumi));
}

boolean SensorsReader::readPublishDoor (void)
{
  boolean const currentDoorState = digitalRead(DoorSensorPin);

  if(m_previousDoorSensor != currentDoorState)
  {
    if(send(m_trapDoor.set(currentDoorState)))
    {
      //Serial.print("Door: ");
      //Serial.println(currentDoorState);
      m_previousDoorSensor = currentDoorState;
      return true;
    }
  }

  return false;
}
