#include "serial.h"
#include "sensor_sim.h"
#include "thirdeye.h"

static int temperatureLastReadVal = 0;

void setup()
{
  SerialUSB.begin(115200); // Initialize Serial Monitor USB
  Serial1.begin(115200); // Initialize hardware serial port, pins 0/1

  while (!SerialUSB) ; // Wait for Serial monitor to open

  /*-- Code added for ThirdEye --*/
  //serial1_send( thirdEyeCommandStr[CONNECT] );
  //debugPrint( "Send to serial --> " + String(thirdEyeCommandStr[CONNECT]) );
  /*-- End --*/
}


void loop()
{
  /* Simulate sensor value changes by inputing an integer from SerialUSB monitor */
  //temperatureSensorSimulator();

  /* Process USB debug port command */
  processSerialUSBCommand();

  /* Read Sensor Value */
  int readVal;
  readVal = readTemperature();

  /* If value changed then send an update */
  if ( readVal != temperatureLastReadVal )
  {
    temperatureLastReadVal = readVal;
    reportTemperature( readVal );
  }
}
