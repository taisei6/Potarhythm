class Tank {
  public:
  Tank(){};
  ~Tank(){};
  
  void setup(){
    pinMode(2, INPUT_PULLUP);
    pinMode(13,OUTPUT);  
  }
  void update(){
    int sensorVal = digitalRead(2);
    if (sensorVal == HIGH) {
      digitalWrite(13, LOW);
    } else {
      digitalWrite(13, HIGH);
    }
  }
  
};
