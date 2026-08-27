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
    switch(note){
      case 64:
        digitalWrite(12,HIGH);
        timestamp = millis();
        flg_note_on = true;
        break;
      case 65:
        digitalWrite(12,HIGH);
        timestamp = millis();
        flg_note_on = true;
        break;
      case 66:
        digitalWrite(12,HIGH);
        timestamp = millis();
        flg_note_on = true;
        break;
      case 67:
        digitalWrite(12,HIGH);
        timestamp = millis();
        flg_note_on = true;
        break;
      case 68:
        digitalWrite(12,HIGH);
        timestamp = millis();
        flg_note_on = true;
        break;
      case 69:
        digitalWrite(12,HIGH);
        timestamp = millis();
        flg_note_on = true;
        break;
      case 70:
        digitalWrite(12,HIGH);
        timestamp = millis();
        flg_note_on = true;
        break;
        
      case 71:
        digitalWrite(11,HIGH);
        timestamp = millis();
        flg_note_on = true;
        break;
      case 72:
        digitalWrite(11,HIGH);
        timestamp = millis();
        flg_note_on = true;
        break;
      case 73:
        digitalWrite(11,HIGH);
        timestamp = millis();
        flg_note_on = true;
        break;
      case 74:
        digitalWrite(11,HIGH);
        timestamp = millis();
        flg_note_on = true;
        break;
      case 75:
        digitalWrite(11,HIGH);
        timestamp = millis();
        flg_note_on = true;
        break;
      case 76:
        digitalWrite(11,HIGH);
        timestamp = millis();
        flg_note_on = true;
        break;
      case 77:
        digitalWrite(11,HIGH);
        timestamp = millis();
        flg_note_on = true;
        break;
      case 78:
        digitalWrite(11,HIGH);
        timestamp = millis();
        flg_note_on = true;
        break;
      case 79:
        digitalWrite(11,HIGH);
        timestamp = millis();
        flg_note_on = true;
        break;
      case 80:
        digitalWrite(11,HIGH);
        timestamp = millis();
        flg_note_on = true;
        break;
      case 81:
        digitalWrite(11,HIGH);
        timestamp = millis();
        flg_note_on = true;
        break;
      case 82:
        digitalWrite(11,HIGH);
        timestamp = millis();
        flg_note_on = true;
        break;
      case 83:
        digitalWrite(11,HIGH);
        timestamp = millis();
        flg_note_on = true;
        break;
      case 84:
        digitalWrite(11,HIGH);
        timestamp = millis();
        flg_note_on = true;
        break;
      }
  }
  void off(int _note) {
    note = _note;
    switch(note){
      case 64:
        digitalWrite(12,LOW);
        
        flg_note_on = false;
        break;
      case 65:
        digitalWrite(12,LOW);
        
        flg_note_on = false;
        break;
      case 66:
        digitalWrite(12,LOW);
        
        flg_note_on = false;
        break;
      case 67:
        digitalWrite(12,LOW);
        
        flg_note_on = false;
        break;
      case 68:
        digitalWrite(12,LOW);
        
        flg_note_on = false;
        break;
      case 69:
        digitalWrite(12,LOW);
        
        flg_note_on = false;
        break;
      case 70:
        digitalWrite(12,LOW);
        
        flg_note_on = false;
        break;
        
      case 71:
        digitalWrite(11,LOW);
        
        flg_note_on = false;
        break;
      case 72:
        digitalWrite(11,LOW);
        
        flg_note_on = false;
        break;
      case 73:
        digitalWrite(11,LOW);
        
        flg_note_on = false;
        break;
      case 74:
        digitalWrite(11,LOW);
        
        flg_note_on = false;
        break;
      case 75:
        digitalWrite(11,LOW);
        
        flg_note_on = false;
        break;
      case 76:
        digitalWrite(11,LOW);
        
        flg_note_on = false;
        break;
      case 77:
        digitalWrite(11,LOW);
        
        flg_note_on = false;
        break;
      case 78:
        digitalWrite(11,LOW);
        
        flg_note_on = false;
        break;
      case 79:
        digitalWrite(11,LOW);
        
        flg_note_on = false;
        break;
      case 80:
        digitalWrite(11,LOW);
        
        flg_note_on = false;
        break;
      case 81:
        digitalWrite(11,LOW);
        
        flg_note_on = false;
        break;
      case 82:
        digitalWrite(11,LOW);
        
        flg_note_on = false;
        break;
      case 83:
        digitalWrite(11,LOW);
        
        flg_note_on = false;
        break;
      case 84:
        digitalWrite(11,LOW);
        
        flg_note_on = false;
        break;
        }
  }
  
  void update(){
    if ( (millis()-timestamp) >= opentime && flg_note_on == true ) {
      off(note);
    }
  }
  
  boolean flg_note_on;;
  long timestamp;
  int note;
  int opentime = 70;

};
