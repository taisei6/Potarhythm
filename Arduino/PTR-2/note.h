class Note {
  public:
  Note(){};
  ~Note(){};
  void setup(){
    pinMode(11,OUTPUT);
    pinMode(12,OUTPUT);  
//    pinMode(13,OUTPUT);  //Lチカデバック用
  }
  void on(int _note) {
    note = _note;
//    digitalWrite(13,HIGH);
    digitalWrite(11,HIGH);
  }
  void off(int _note) {
    note = _note;
    digitalWrite(11,LOW);
//    digitalWrite(13,LOW);
  }
  void update(){
  }
  
  long ms;
//  ms= xxxxミリ秒
  boolean flg_note_on;;
  long timestamp;
  int notePIN[12] = {11,11,11,11,11,11,12,12,12,12,12,12};
  int note;

};
