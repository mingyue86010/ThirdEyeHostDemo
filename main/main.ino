#include <Arduino.h>

#include "thirdeye.h"

void setup()
{ 
  /* HW init */
  SerialUSB.begin(115200); // Initialize Serial Monitor USB
  Serial1.begin(115200); // Initialize hardware serial port, pins 0/1
  while (!SerialUSB) ; // Wait for Serial monitor to open
  SerialUSB.println( "Host rebooted.");
  
  /* Config Wifi */
  SerialUSB.println( "Configuring WiFi");
  send_to_thirdeye( "AT+CONF SSID=NETGEAR90" );
  send_to_thirdeye( "AT+CONF PASSPHRASE=boldvalley718" );  
  /* Config Topics */
  SerialUSB.println( "Configuring MQTT Topics");
  send_to_thirdeye( "AT+CONF TOPIC#0=/data/temperature/" );
  send_to_thirdeye( "AT+CONF TOPIC#1=/data/moisture/" );
  /*-- Wifi On --*/
  SerialUSB.println( "Starting WiFi");
  send_to_thirdeye( "AT+WIFION \n" );
}


void loop()
{
  /* Connect */
  SerialUSB.println("Reporting to AWS");
  if(OK == send_to_thirdeye( "AT+CONNECT" )
  {
  delay(2000);
  send_to_thirdeye( "AT+SEND /info/=\"Host-Connect!\"" );
  
  for (int i = 0; i < 4; i++ )
  {
    send_to_thirdeye( "AT+SEND#0 " + String(i) );
    send_to_thirdeye( "AT+SEND#1 " + String(100 + i) );
    delay(1000);
  }
  SerialUSB.println("Disconnecting from AWS");
  send_to_thirdeye( "AT+SEND /info/=\"Host-Going-To-Disconnect!\"" );
  send_to_thirdeye( "AT+DISCONNECT" );
  }
  else
  {
    SerialUSB.println("Connection failed");
  }
  delay(5000);
}

thirdeye_responses_t send_to_thirdeye( String command )
{
  Serial1.println( command + String("\n"));
  // TODO: receive the response from thirdeye

  // copy command to USB so PC can follow what is happening
  SerialUSB.println("To ThirdEye --> " + command);
  
  delay(2000);// delay for now.  final commands will get a response from ThirdEye

  return OK; // assume command was successful
}
