
int temperatureLastReadVal = 0;

void setup()
{
  SerialUSB.begin(9600); // Initialize Serial Monitor USB
  Serial1.begin(9600); // Initialize hardware serial port, pins 0/1

  while (!SerialUSB) ; // Wait for Serial monitor to open
}

void loop()
{
  temperatureSensorSimulator();
  
  int readVal;
  readVal = readTemperature();
  if ( readVal != temperatureLastReadVal )
  {
    temperatureLastReadVal = readVal;
    reportTemperature( readVal );
  }
}


void reportTemperature( int value )
{
    String toSendStr = ""; // Create a new string

    toSendStr = "Temperature=" + String(value);
    // Send the assembled string out over the hardware
    // Serial1 port (TX pin 1).
    Serial1.print(toSendStr);
    SerialUSB.println(toSendStr);
}


/*---------- Code to Simulate a Temperature Sensor cd ----------*/


int temperatureVal = 0;

int readTemperature()
{
  return temperatureVal;
}

void temperatureSensorSimulator()
{
  if (SerialUSB.available()) // If data is sent to the monitor
  {
    int value = temperatureVal;
    while (SerialUSB.available()) // While data is available
    {
      // look for the next valid integer in the incoming SerialUSB stream
      value = SerialUSB.parseInt();
    }

    temperatureVal = value;
    SerialUSB.println("Temperature changed:" + String(value));
  }
}
