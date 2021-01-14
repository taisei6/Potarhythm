class Note {
  public:
  Note(){};
  ~Note(){};
  void setup(){
    pinMode(notePIN[0],OUTPUT);
    pinMode(notePIN[1],OUTPUT);
    pinMode(notePIN[2],OUTPUT);
    pinMode(notePIN[3],OUTPUT);
  }
  void on(int _note,long _ms) {
    timestamp = millis();
    flg_note_on = true;
    note = _note;
    ms = _ms;
    digitalWrite(notePIN[note],HIGH);
  }
  void off(int _note) {
    flg_note_on = false;
    digitalWrite(notePIN[note],LOW);
  }
  void update(){
    if ( (millis()-timestamp) >= ms && flg_note_on == true ) {
      off(note);
    }
  }
  long ms;
  boolean flg_note_on;
  long timestamp;
  int notePIN[5] = {7,8,9,10,11};
  int note;
};
