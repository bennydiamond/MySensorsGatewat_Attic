#include "MyConfig.h"
#include "core/MySensorsCore.h"
#include <Wire.h>
#include "tinySHT2x.h"
#include <stdint.h>

class SensorsReader
{
public:
  SensorsReader();

  void init (void);
  void presentSensors (void);
  void loop (void);

private:
  static auto const ClimateSensorTimerResetValue_ms = 60000; 
  static auto const DoorDebounceTimerResetValue_ms = 100; 

  tinySHT2x m_sht;

  MyMessage m_trapDoor;
  MyMessage m_temperature1;
  MyMessage m_humidity1;

  void readPublishClimate (void);
  boolean readPublishDoor (void);
  
  uint16_t m_climateSensorTimer;
  uint16_t m_doorDebounceTimer;
  boolean  m_previousDoorSensor;
  uint32_t m_previousMillis;
};