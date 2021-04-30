
void processSerialUSBCommand( void )
{ 
  String inputString = "";         // a String to hold incoming data
  bool isNumber = true;
  
  while (SerialUSB.available()) 
  {
    char inChar = (char)SerialUSB.read();
    inputString += inChar;
    if (inChar == '\n') {
      /* Simulate sensor value changes by inputing an integer from SerialUSB monitor */
      int i = 0;
      while ( inputString.charAt(i) != '\n' )
      {
        isNumber = isDigit(inputString.charAt(i)) ? true : false;
        i++;
      }
      if ( isNumber )
      {
        temperatureVal = inputString.toInt();
      }

      /* Debug Commands */
      if ( inputString.equals( "disconnect\n" ))
      {
        /*-- Code added for ThirdEye --*/
        serial1_send( thirdEyeCommandStr[DISCONNECT] );
        debugPrint( "Send to serial --> " + String(thirdEyeCommandStr[DISCONNECT]) );
        /*-- End --*/
      }
      else if ( inputString.equals( "connect\n" ))
      {
        /*-- Code added for ThirdEye --*/
        serial1_send( thirdEyeCommandStr[CONNECT] );
        debugPrint( "Send to serial --> " + String(thirdEyeCommandStr[CONNECT]) );
        /*-- End --*/
      }
      else if ( inputString.equals( "send\n" ))
      {
        /*-- Code added for ThirdEye --*/
        serial1_send( thirdEyeCommandStr[SEND] );
        debugPrint( "Send to serial --> " + String(thirdEyeCommandStr[SEND]) );
        /*-- End --*/
      }
      else if ( inputString.equals( "run\n" ))
      {
        /*-- Code added for ThirdEye --*/
        global_demo_run = true;
        /*-- End --*/
      }
    }
  }
}


void debugPrint( String str )
{
  SerialUSB.println( "DEBUG:" + str );
}


void serial1_send( String str )
{
  Serial1.print(str);
}
