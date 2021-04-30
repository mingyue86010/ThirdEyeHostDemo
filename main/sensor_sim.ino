
static int temperatureVal = 0;

int readTemperature()
{
  return temperatureVal;
}


void reportTemperature( int value )
{
    String toSendStr = ""; // Create a new string
    
    toSendStr = "AT+SEND /data/temperature/=" + String(value) + " \n";
    
    // Send the assembled string out over the hardware Serial1 port (TX pin 1).
    serial1_send( toSendStr );
    debugPrint("Send to serial --> " + toSendStr);

    String toSendStr2 = "AT+SEND /data/moisture/=" + String(value+10) + " \n";
    serial1_send( toSendStr2 );
    debugPrint("Send to serial --> " + toSendStr2);
}
