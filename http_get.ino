#include <SoftwareSerial.h>
SoftwareSerial SIM800(7,5); // RX, TX 


void setup(){
    SIM800.begin(9600);
    Serial.begin(9600);
    readHTTPRequest();
}

void loop()
{
  SIM800.println("AT+CSPN?");
  delay(100);
  readHTTPRequest();
  }

void readHTTPRequest()
{
 
  SIM800.println("AT+CSQ"); // Signal quality check

  delay(100);
 
  ShowSerialData(); // this code is to show the data from gprs shield, in order to easily see the process of how the gprs shield submit a http request, and the following is for this purpose too.
  
  SIM800.println("AT+CGATT?"); //Attach or Detach from GPRS Support
  delay(100);
 
  ShowSerialData();
  
  SIM800.println("AT+SAPBR=3,1,\"CONTYPE\",\"GPRS\"");//setting the SAPBR, the connection type is using gprs
  delay(1000);
 
  ShowSerialData();
 
  SIM800.println("AT+SAPBR=3,1,\"APN\",\"Safaricom\"");//setting the APN, Access point name string
  delay(4000);
 
  ShowSerialData();
 
  SIM800.println("AT+SAPBR=1,1");//setting the SAPBR
  delay(2000);
 
  ShowSerialData();
 
  SIM800.println("AT+HTTPINIT"); //init the HTTP request
 
  delay(2000); 
 ShowSerialData();

   SIM800.print("AT+HTTPPARA=\"URL\",\"https://faree.rapando");// setting the httppara, the second parameter is the website you want to access
    
  SIM800.println("\"");
  delay(1000);
  
   
 
 
  ShowSerialData();
 
  SIM800.println("AT+HTTPACTION=0");//submit the request 
  delay(5000);//the delay is very important, the delay time is base on the return from the website, if the return datas are very large, the time required longer.
  while(!SIM800.available());
 
  ShowSerialData();
 
  SIM800.println("AT+HTTPREAD");// read the data from the website you access
  delay(300);
  ShowSerialData();
 
  SIM800.println("");
  delay(100);
}


void ShowSerialData()
{
  while(SIM800.available()!=0)
    Serial.write(char (SIM800.read()));
}
