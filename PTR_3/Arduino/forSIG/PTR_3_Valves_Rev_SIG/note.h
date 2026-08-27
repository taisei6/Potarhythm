class Note {
  public:
  Note(){};
  ~Note(){};
  void setup(){
    pinMode(notePIN[0],OUTPUT);
    pinMode(notePIN[1],OUTPUT);
    pinMode(notePIN[2],OUTPUT);
    pinMode(notePIN[3],OUTPUT);
    pinMode(notePIN[4],OUTPUT);
    pinMode(notePIN[5],OUTPUT);
    pinMode(notePIN[6],OUTPUT);
    pinMode(notePIN[7],OUTPUT);
  }
  void on(int _note,long _ms) {
    timestamp = millis();
    flg_note_on = true;
    isAutoOff = true;
    note = _note;
    ms = _ms;
    digitalWrite(notePIN[note],HIGH);
  }
  void hold(int _note) {
    flg_note_on = true;
    note = _note;
    isAutoOff = false; // 自動消音を無効にする
    digitalWrite(notePIN[note], HIGH);
  }

  void off(int _note) {
    flg_note_on = false;
    digitalWrite(notePIN[note],LOW);
  }
  void update(){
    if ( (millis()-timestamp) >= ms && flg_note_on == true && isAutoOff == true) {
      off(note);
    }
  }

  long ms;
  boolean flg_note_on;
  long timestamp;
  int notePIN[8] = {6,7,8,9,10,11,12,5};
  int note;
  boolean isAutoOff = false;
};
