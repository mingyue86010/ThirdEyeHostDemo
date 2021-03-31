
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
