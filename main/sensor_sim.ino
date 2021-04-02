
static int temperatureVal = 0;

int readTemperature()
{
  return temperatureVal;
}


void reportTemperature( int value )
{
    String toSendStr = ""; // Create a new string
    
    toSendStr = "Temperature=" + String(value);
    
    // Send the assembled string out over the hardware Serial1 port (TX pin 1).
    serial1_send( toSendStr );
    debugPrint("Send to serial --> " + toSendStr);
}
