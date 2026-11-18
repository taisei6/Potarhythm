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
    if(0<= note < 7){
      digitalWrite(12,HIGH);
      timestamp = millis();
      flg_note_on = true;
    }
    if(21 > note >= 7){
      digitalWrite(11,HIGH);
      timestamp = millis();
      flg_note_on = true;
    }
  }
  void off(int _note) {
    note = _note;
    if(0 <=note < 7){
      flg_note_on = false;
      digitalWrite(12,LOW);
      }
    if(21>note >= 7){
      flg_note_on = false;
      digitalWrite(11,LOW);
    }
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
  int opentime = 70;

};
