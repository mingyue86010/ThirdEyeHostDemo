#include "thirdeye.h"

#define THIRDEYE_EVENT_PIN 5

void setup()
{ 
  /*-- HW init --*/
  SerialUSB.begin(115200); // Initialize Serial Monitor USB
  Serial1.begin(115200); // Initialize hardware serial port, pins 0/1
  while (!SerialUSB) ; // Wait for Serial monitor to open
  pinMode(THIRDEYE_EVENT_PIN, INPUT);
  
  SerialUSB.println( "Host rebooted.");

  while ( SerialUSB.read() != 'a' ){} //let the code stop here for waiting the TE board get flashed 
  
  /*-- Config Wifi --*/
  SerialUSB.println( "Configuring WiFi");
  send_to_thirdeye( "AT+CONF SSID=MyWifi" );
  send_to_thirdeye( "AT+CONF PASSPHRASE=19901007" );  
  
  /*-- Config Topics --*/
  SerialUSB.println( "Configuring MQTT Topics");
  send_to_thirdeye( "AT+CONF TOPIC#0=/data/temperature/" );
  send_to_thirdeye( "AT+CONF TOPIC#1=/data/moisture/" );
  
  /*-- Wifi On --*/
  SerialUSB.println( "Starting WiFi");
  send_to_thirdeye( "AT+WIFION" );
  delay(15000);

  /*-- Connect to MQTT Broker --*/
  while (OK != send_to_thirdeye( "AT+CONNECT" ) ){}
  delay(10000);
  SerialUSB.println("Connection Success.");  
  
  send_to_thirdeye( "AT+SEND /info/=\"Host-Connect!\"" );
}



void loop()
{
  static int temperature; 
  static int moisture;
  int event_flag = 0; 
  String incomming_string;
  
  temperature = random(0, 60);
  moisture = random(2, 60);
   
  send_to_thirdeye( "AT+SEND#0 " + String(temperature) );
  send_to_thirdeye( "AT+SEND#1 " + String(moisture) );
  
  event_flag = digitalRead(THIRDEYE_EVENT_PIN);
  if ( event_flag )
  {
      SerialUSB.println( "EVENT_FLAG SET!");
      send_to_thirdeye( "AT+GET " );

      incomming_string = Serial1.readString();
      if ( incomming_string.length() > 0 )
      {
        SerialUSB.println( "Recv: " + incomming_string);
        incomming_string = String();
      }
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

thirdeye_responses_t recv_from_thirdeye( void )
{
  
}
