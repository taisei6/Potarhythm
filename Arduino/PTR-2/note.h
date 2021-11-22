class Note {
  public:
  Note(){};
  ~Note(){};
  void setup(){
    pinMode(7,OUTPUT);
    pinMode(8,OUTPUT);    
  }
  void on(int _note) {
    flg_note_on = true;
    note = _note;
    digitalWrite(notePIN[note],HIGH);
  }
  void off(int _note) {
    flg_note_on = false;
    note = _note;
    digitalWrite(notePIN[note],LOW);
  }
  void update(){
//    if ( (millis()-timestamp) >= ms && flg_note_on == false ) {
//      drive_off(note);
//    }
  }
  
  long ms;
//  ms= xxxxミリ秒
  boolean flg_note_on;;
  long timestamp;
  int notePIN[12] = {7,7,7,7,7,7,8,8,8,8,8,8};
  int note;

};