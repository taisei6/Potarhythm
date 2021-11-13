
#include <SparkFun_TB6612.h>


#define AIN1 2
#define BIN1 7
#define AIN2 4
#define BIN2 8
#define PWMA 5
#define PWMB 6
#define STBY 9

const int offsetA = 1;
const int offsetB = 1;

Motor motor1 = Motor(AIN1, AIN2, PWMA, offsetA, STBY);
Motor motor2 = Motor(BIN1, BIN2, PWMB, offsetB, STBY);

const int s_pin = A0;
const int mf_pin = A1;

int sli_v,mf_v = 0;

const int flg0Pin = 10;         // the number of the pushflg pin
const int ledPin = LED_BUILTIN;  // the number of the LED pin
int flg0 = 0; 

int count,count_pre,count2 = 0;

void setup()
{
 pinMode(ledPin, OUTPUT);
 pinMode(flg0Pin, INPUT);
 
 Serial.begin(9600);
 
// forward(motor1,motor2, 200);
// delay(500);
// brake(motor1,motor2);
// delay(100);
}


void loop(){
  
  flg0 = digitalRead(flg0Pin);
  sli_v = analogRead(s_pin);
  mf_v = analogRead(mf_pin);
  Serial.print(sli_v);
  Serial.print("___");
  Serial.println(mf_v);
  
 

 if (flg0 == HIGH) {
    
    if(mf_v < sli_v){
      motor1.drive(250,10);
    motor1.brake();
    }else{
     motor1.brake();
    }
//    digitalWrite(ledPin, HIGH);
    
  } else {
    if(mf_v > sli_v){
     motor1.brake();
    }
//    digitalWrite(ledPin, LOW);
  }
    
}
