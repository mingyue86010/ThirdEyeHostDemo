
enum {
 CONNECT = 0,
 DISCONNECT,
 SET
};

const char* thirdEyeCommandStr[] = 
{  
  "AT+CONNECT \n",      //FreeRTOS CLI command must always be null/space terminated
  "AT+DISCONNECT \n",
  "AT+SET \n",
};
