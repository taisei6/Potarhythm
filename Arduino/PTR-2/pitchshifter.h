#include <SparkFun_TB6612.h>

#define AIN1 3
#define BIN1 7
#define AIN2 4
#define BIN2 8
#define PWMA 5
#define PWMB 6
#define STBY 9

class P_shifter {
  public:
  P_shifter(){};
  ~P_shifter(){};
  
  void setup(){
  }
  
  void on(int _note) {
    note = _note;
    flg_note_on = true;
  }
  
  void off(int _note) {
    note = _note;
    flg_note_on = false;
    timestamp = millis();
  }
  
  void drive(int _note){
    note = _note;
    if(note < 6){
      mf_v = analogRead(mf_pin1);
      p_height = map(mf_v, 0, 1023, 0, 99);
      
      if(p_height < p_val[note]){
      motor1.drive(200,7);
      motor1.brake();
      }
      if(p_height - p_val[note]>=2){
      motor1.drive(-200,7);
      motor1.brake();
      }
    }
    if(note >= 6){
      mf_v = analogRead(mf_pin2);
      p_height = map(mf_v, 0, 1023, 0, 99);
      
      if(p_height < p_val[note]){
      motor2.drive(200,7);
      motor2.brake();
      }
      if(p_height - p_val[note]>=2){
      motor2.drive(-200,7);
      motor2.brake();
      }
    }
  }
  
  void update(){
    if(flg_note_on == true){
      drive(note);
    }    
    if ( (millis()-timestamp) <= ms && flg_note_on == false ) {
      drive(note);
    }
  }
  
  long ms = 500;//バルブが閉まった後の高度のキープ時間
  boolean flg_note_on;
  long timestamp;
  int note;

  const int offsetA = 1;
  const int offsetB = 1;
  Motor motor1 = Motor(AIN1, AIN2, PWMA, offsetA, STBY);
  Motor motor2 = Motor(BIN1, BIN2, PWMB, offsetB, STBY);

  const int mf_pin1 = A0;
  const int mf_pin2 = A1;
  int mf_v = 0;
  int p_val[12]= {5,10,15,20,25,30,35,40,45,50,55,60};//実施に計測した高度に設定する min5 Max95
  int p_height = 5;
};
