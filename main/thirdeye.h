
enum {
 CONNECT = 0,
 DISCONNECT,
 SEND
};

const char* thirdEyeCommandStr[] = 
{  
  "AT+CONNECT \n",      //FreeRTOS CLI command must always be null/space terminated
  "AT+DISCONNECT \n",
  "AT+SEND Hello123! \n",
};
