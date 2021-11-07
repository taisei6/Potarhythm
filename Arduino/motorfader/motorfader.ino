
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



void setup()
{
 
 Serial.begin(9600);
 
 forward(motor1,motor2, 200);
 delay(500);
 brake(motor1,motor2);
 delay(100);
}


void loop()
{
  sli_v = analogRead(s_pin);
  mf_v = analogRead(mf_pin);
  Serial.print(sli_v);
  Serial.print("___");
  Serial.println(mf_v);

  if(mf_v < sli_v){
    motor1.drive(250,15);
//    motor1.brake();
  }
  
  if(mf_v > sli_v){
    motor1.brake();
  }

//  if(mf_v > sli_v){
//    forward(motor1,motor2, 50);
////   delay(100);
//    }
//  if(mf_v < sli_v){
//    back(motor1,motor2, 50);
////   delay(100);
//    }
    
//   brake(motor1,motor2);
//   delay(100);
  
}
