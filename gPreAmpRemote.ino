#define DEBUG 1
#include <IRremote.h>
/* https://github.com/shirriff/Arduino-IRremote */


#define RECV_PIN 12

#define SELECTOR_1 8
#define SELECTOR_2 9
#define SELECTOR_3 10
#define SELECTOR_4 11

IRrecv irrecv(RECV_PIN);
decode_results results;


void PrintDecodeType(int type)
{
  switch(type)
  {
    case NEC:Serial.println("NEC ");break;
    case SONY:Serial.println("SONY ");break;
    case RC5:Serial.println("RC5 ");break;
    case RC6:Serial.println("RC6 ");break;
    case DISH:Serial.println("DISH ");break;
    case SHARP:Serial.println("SHARP ");break;
    case PANASONIC:Serial.println("PANASONIC ");break;
    case JVC:Serial.println("JVC ");break;
    case SANYO:Serial.println("SANYO ");break;
    case MITSUBISHI:Serial.println("MITSUBISHI ");break;
    case UNKNOWN:Serial.println("UNKNOWN ");break;
  }
  
}

void MotorOff()
{
  digitalWrite(A0,LOW);
  digitalWrite(A1,LOW);
  digitalWrite(A2,LOW);
  digitalWrite(A3,LOW);
  digitalWrite(A4,LOW);
  digitalWrite(A5,LOW);
  
  digitalWrite(2,LOW);
  digitalWrite(3,LOW);
  digitalWrite(4,LOW);
  digitalWrite(5,LOW);
  digitalWrite(6,LOW);
  digitalWrite(7,LOW);
}

void MotorUp()
{
  digitalWrite(A0,HIGH);
  digitalWrite(A1,HIGH);
  digitalWrite(A2,HIGH);
  digitalWrite(A3,HIGH);
  digitalWrite(A4,HIGH);
  digitalWrite(A5,HIGH);
  
  digitalWrite(2,LOW);
  digitalWrite(3,LOW);
  digitalWrite(4,LOW);
  digitalWrite(5,LOW);
  digitalWrite(6,LOW);
  digitalWrite(7,LOW);
}


void MotorDown()
{
  digitalWrite(A0,LOW);
  digitalWrite(A1,LOW);
  digitalWrite(A2,LOW);
  digitalWrite(A3,LOW);
  digitalWrite(A4,LOW);
  digitalWrite(A5,LOW);
  
  digitalWrite(2,HIGH);
  digitalWrite(3,HIGH);
  digitalWrite(4,HIGH);
  digitalWrite(5,HIGH);
  digitalWrite(6,HIGH);
  digitalWrite(7,HIGH);
}


void setup()
{
  pinMode(SELECTOR_1,OUTPUT);digitalWrite(SELECTOR_1,HIGH);
  pinMode(SELECTOR_2,OUTPUT);digitalWrite(SELECTOR_2,LOW);
  pinMode(SELECTOR_3,OUTPUT);digitalWrite(SELECTOR_3,LOW);
  pinMode(SELECTOR_4,OUTPUT);digitalWrite(SELECTOR_4,LOW);

  pinMode(A0,OUTPUT);
  pinMode(A1,OUTPUT);
  pinMode(A2,OUTPUT);
  pinMode(A3,OUTPUT);
  pinMode(A4,OUTPUT);
  pinMode(A5,OUTPUT);
  
  pinMode(2,OUTPUT);
  pinMode(3,OUTPUT);
  pinMode(4,OUTPUT);
  pinMode(5,OUTPUT);
  pinMode(6,OUTPUT);
  pinMode(7,OUTPUT);
  
  MotorOff();
  
  Serial.begin(9600);
  Serial.println("Ready.");
    
  irrecv.enableIRIn(); // Start the receiver
}

void loop() 
{
	if (irrecv.decode(&results)) 
    {
	  PrintDecodeType(results.decode_type);
      Serial.print(results.bits, DEC);
      Serial.print("  "); 
      Serial.println(results.value, HEX); 
      irrecv.resume(); // Receive the next value
      
      
      if (results.decode_type==RC5)
      {
	      //0x800 bit is for repeat
	      if ((results.value==0xC10)||(results.value==0x410))
	      {
		   	MotorUp();
		   	delay(100);
		   	MotorOff();
	      }
	      else if ((results.value==0xC11)||(results.value==0x411))
	      {
		   	MotorDown();
		   	delay(100);
		   	MotorOff();
	      }
	      else if ((results.value==0x61F))/*Select Input 1 */
	      {
			  digitalWrite(SELECTOR_1,HIGH);
			  digitalWrite(SELECTOR_2,LOW);
			  digitalWrite(SELECTOR_3,LOW);
			  digitalWrite(SELECTOR_4,LOW);
	      }
	      else if ((results.value==0x620))/*Select Input 2 */
	      {
			  digitalWrite(SELECTOR_1,LOW);
			  digitalWrite(SELECTOR_2,HIGH);
			  digitalWrite(SELECTOR_3,LOW);
			  digitalWrite(SELECTOR_4,LOW);
	      }
	      else if ((results.value==0x621))/*Select Input 3 */
	      {
			  digitalWrite(SELECTOR_1,LOW);
			  digitalWrite(SELECTOR_2,LOW);
			  digitalWrite(SELECTOR_3,HIGH);
			  digitalWrite(SELECTOR_4,LOW);
	      }
	      else if ((results.value==0x622))/*Select Input 4 */
	      {
			  digitalWrite(SELECTOR_1,LOW);
			  digitalWrite(SELECTOR_2,LOW);
			  digitalWrite(SELECTOR_3,LOW);
			  digitalWrite(SELECTOR_4,HIGH);
	      }
	      
  	  }
    }
}

      
      
