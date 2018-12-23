#define motor1 3
#define motor2 4
#define motor3 5
String stringOne;
String stringTwo;
int temp=0,i=0;          
int led=13;
int inPin=12;
int power;
char msg;             
char str[15];        //for string to store messages
void setup()
{
  Serial.begin(9600);
  pinMode(led, OUTPUT);
  pinMode(power, INPUT);
   pinMode(motor1, OUTPUT);
    pinMode(motor2, OUTPUT);
     pinMode(motor3, OUTPUT);
 Serial.println("AT+CNMI=2,2,0,0,0");   // for Receiving and Reading SMS Messages
  delay(500);
  Serial.println("AT+CMGF=1");          //Sets the GSM Module in Text Mode
  delay(1000); 
}

void loop()
{
   if(temp==1)         
  {
    check();          //for Checking the messages 
    temp=0;
    i=0;
    delay(1000);
  }
}
void powerCheck()    //checking power
{
  power=digitalRead(inPin);
  if(power==HIGH){
   stringOne="POWER IS IN ON STATE"; 
   SendMessage();
  }
  if(power==LOW){
   stringOne="POWER IS IN OFF STATE"; 
   SendMessage();
  }
}
 void serialEvent() 
 {
  while(Serial.available())    //for checking if serial data available or not 
  {
    if(Serial.find("#"))       //starting symbol of command
    {
      digitalWrite(led, HIGH);
      delay(1000);
      digitalWrite(led, LOW);
      while (Serial.available()) 
      {
      char inChar=Serial.read();
      str[i++]=inChar;
      if(inChar=='*')        //ending symbol of command
      {
        temp=1;
        return;
      } 
      } 
    }
   }
 }
void SendMessage()            //for sending messages
{
  Serial.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
  delay(1000);  // Delay of 1000 milli seconds or 1 second
  Serial.println("AT+CMGS=\"+91xxxxxxxxxx\"\r"); // Replace x with mobile number
  delay(1000);
  Serial.println(stringOne);// The SMS text you want to send
  delay(100);
   Serial.println((char)26);// ASCII code of CTRL+Z
  delay(1000);
}
void check()
{
    if(!(strncmp(str,"motor1 on",9)))   //if(!(strncmp(str,command,command length))) 
    {
      digitalWrite(motor1, HIGH);
       stringOne="motor1 is turned on";
      SendMessage();
     
      delay(200);
    }
 
    else if(!(strncmp(str,"motor1 off",10)))
    {
      digitalWrite(motor1, LOW);
      
      stringOne="motor1 is turned off";
      SendMessage(); 
      delay(200);
    }
 
    else if(!(strncmp(str,"motor2 on",9)))
    {
      digitalWrite(motor2, HIGH);
      stringOne="motor2 is turned on";
      SendMessage();
      
      delay(200);
    }
 
    else if(!(strncmp(str,"motor2 off",10)))
    {
      digitalWrite(motor2, LOW);
      stringOne="motor2 is turned off";
      SendMessage();
      delay(200);
    }
    else if(!(strncmp(str,"motor3 on",9)))
    {
      digitalWrite(motor3, HIGH);
       stringOne="motor3 is turned on";
      SendMessage();
      delay(200);
    }  
   
   else if(!(strncmp(str,"motor3 off",10)))
    {
      digitalWrite(motor3, LOW);
       stringOne="motor3 is turned off";
      SendMessage();
      
      delay(200);
    } 
    
    else if(!(strncmp(str,"all on",6)))
    {
      digitalWrite(motor1, HIGH);
      digitalWrite(motor2, HIGH);
      digitalWrite(motor3, HIGH);
     stringOne="all devices turned off";
      SendMessage();
      delay(200);
    }
 
    else if(!(strncmp(str,"all off",7)))
    {
      digitalWrite(motor1, LOW);
      digitalWrite(motor2, LOW);
      digitalWrite(motor3, LOW);
      stringOne="all devices turned on";
      SendMessage();
      delay(200);
    }     
     else if(!(strncmp(str,"status",6)))
    {
      SendMessage();
      delay(200);
    }   
    else if(!(strncmp(str,"powercheck",10)))
    {
      powerCheck();
      delay(200);
    }     
    
}
