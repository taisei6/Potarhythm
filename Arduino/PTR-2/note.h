class Note {
  public:
  Note(){};
  ~Note(){};
  void setup(){
    pinMode(10,INPUT_PULLUP);
    pinMode(11,OUTPUT);
    pinMode(12,OUTPUT);  
//    pinMode(13,OUTPUT);  //Lチカデバック用
  }
  void on(int _note) {
    note = _note;
    digitalWrite(notePIN[note],HIGH);
    timestamp = millis();
    flg_note_on = true;
  }
  void off(int _note) {
    note = _note;
    flg_note_on = false;
    digitalWrite(notePIN[note],LOW);
//    digitalWrite(13,LOW);
  }
  void update(){
    if ( (millis()-timestamp) >= opentime && flg_note_on == true ) {
      off(note);
    }
  }
  
  boolean flg_note_on;;
  long timestamp;
  int notePIN[21] = {12,12,12,12,12,12,12, 11,11,11,11,11,11,11,11,11,11,11,11,11,11};
//  int notePIN[12] = {12,12,12,12,12,12,11,11,11,11,11,11};//12音を繰り返し使う用
//12がA250mm管,11がB200mm管

  int note;
  int opentime = 75;

};
