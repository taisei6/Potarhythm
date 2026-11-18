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
    timestamp = millis();
  }
  
//  void off(int _note) {
//    note = _note;
//    flg_note_on = false;
//    timestamp = millis();
//  }
  
  void drive(int _note){
    note = _note;
    if(note < 6){
      mf_v = analogRead(mf_pin1);
      p_height = map(mf_v, 0, 1023, 0, 99);
      
      if(p_height < p_val[note]){
      motor1.drive(D_up,D_pitch);
      motor1.brake();
      }
//      if(p_height - p_val[note]>=2){
//      motor1.drive(D_down,D_pitch);
//      motor1.brake();
//      }
    }
    if(note >= 6){
      mf_v2 = analogRead(mf_pin2);
      p_height2 = map(mf_v2, 0, 1023, 0, 99);
//mf_v = analogRead(mf_pin1);
//      p_height = map(mf_v, 0, 1023, 0, 99);
//
//if(p_height < p_val[note]){
//      motor1.drive(D_up,D_pitch);
//      motor1.brake();
//      }
      
      if(p_height2 < p_val[note]){
      motor2.drive(D_up,D_pitch);
      motor2.brake();
      }
//      if(p_height2 - p_val[note]>=2){
//      motor2.drive(D_up,D_pitch);
//      motor2.brake();
//      }
    }
  }
  
  void update(){
    if(flg_note_on == true){
      drive(note);
    }    
    if ( (millis()-timestamp) >= opentime + ms && flg_note_on == true ) {
      flg_note_on = false;
    }
//    if ( (millis()-timestamp) <= ms && flg_note_on == false ) {
//      drive(note);
//    }
  }
  
  long ms = 500;//バルブが閉まった後の高度のキープ時間
  boolean flg_note_on;
  long timestamp;
  int note;
  const int opentime = 75;

  const int offsetA = 1;
  const int offsetB = 1;
  Motor motor1 = Motor(AIN1, AIN2, PWMA, offsetA, STBY);
  Motor motor2 = Motor(BIN1, BIN2, PWMB, offsetB, STBY);
  const int D_up = 255; //max255
  const int D_down = -255;
  const int D_pitch = 10;
  
  const int mf_pin1 = A0;
  const int mf_pin2 = A1;
  int mf_v = 0;
  int mf_v2 = 0;
//  int p_val[20]= {80,65,54,46,31,20,8,3, 74,61,38,25,13, 94,78,65,50,28,15,3};
//  int p_val[12]= {80,65,54,46,31,20,94,78,65,50,28,15};
  int p_val[12]= {8,3,74,65,61,54,46,38,31,25,20,13};

//------------------------tuning-------------------------
  //  E4~A#4MIDI Note No.[64~70]7音
  //  A250管155~255mm,[249,240,220,205,182,170,158]
  //  A250管0~100    ,[94,85,65,50,27,15,3]
  
  //  B4~C6,MIDI Note No.[71~84]14音
  //  B200管60~150mm,[145,140,134,125,121,114,106,98,91,85,80,73,68,63]
  //  B200管0~100   ,[85,80,74,65,61,54,46,38,31,25,20,13,8,3]
  
  //実際に計測した高度に設定する min5 Max95
  
//------------------------tuning-------------------------
  
  int p_height = 5;
  int p_height2 = 5;
};
