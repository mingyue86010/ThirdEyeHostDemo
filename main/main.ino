#include "serial.h"
#include "sensor_sim.h"
#include "thirdeye.h"

static int temperatureLastReadVal = 0;
int global_demo_run = false;

void(* softReset) (void) = setup;//declare reset function at address 0

void setup()
{ 
  /* HW init */
  SerialUSB.begin(115200); // Initialize Serial Monitor USB
  Serial1.begin(115200); // Initialize hardware serial port, pins 0/1
  while (!SerialUSB) ; // Wait for Serial monitor to open
  debugPrint( "Host rebooted.");

  /* For Demo Debug */
  break_point();
  
  /* --- Code added for ThirdEye --- */
  /* Config Wifi */
  send_to_thirdeye( "AT+CONF SSID=NETGEAR90 \n" );
  send_to_thirdeye( "AT+CONF PASSPHRASE=boldvalley718 \n" );  
  /* Config Topic */
  send_to_thirdeye( "AT+CONF TOPIC#0=/data/temperature/ \n" );
  send_to_thirdeye( "AT+CONF TOPIC#1=/data/moisture/ \n" );
  /*-- Wifi On --*/
  send_to_thirdeye( "AT+WIFION \n" );
  /* --- Code for ThirdEye End --- */

  /* For Demo Debug */
  break_point();
  
  debugPrint( "--- Host Demo Start ---" );
}


void loop()
{
  int i;

  /* Connect */
  send_to_thirdeye( "AT+CONNECT \n" );
  delay(2000);
  send_to_thirdeye( "AT+SEND /info/=\"Host-Connect!\" \n" );
  
  /* Temperature Sensor */
  for ( i = 0; i < 4; i++ )
  {
    send_to_thirdeye( "AT+SEND#0 " + String(i) + " \n" );
  }
  
  /* Moisture Sensor */
  for ( i = 0; i < 4; i++ )
  {
    send_to_thirdeye( "AT+SEND#1 " + String(100 + i) + " \n" );
  }

  /* Reset */
  send_to_thirdeye( "AT+SEND /info/=\"Host-Going-To-Disconnect!\" \n" );
  send_to_thirdeye( "AT+DISCONNECT \n" );
  //softReset();
  /* For Demo Debug */
  break_point();
}


String simpleJson( char* key, char* value )
{
  char buff[100] = {0};
  String returnString;
  
  snprintf(buff, sizeof(buff), "{\"%s\":\"%s\"}", key, value);
  
  return String(buff);
}


void send_to_thirdeye( String command )
{
  serial1_send( command );
  debugPrint("To ThirdEye --> " + command);
  delay(2000);
}


/*--- Bebug ---*/

void break_point( void )
{
  debugPrint("--- Code Break Point ---");
  while ( !global_demo_run )
  {
    processSerialUSBCommand();
  }
  global_demo_run = false;
}
