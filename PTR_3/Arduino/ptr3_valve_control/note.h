class Note {
  public:
  Note(){};
  ~Note(){};

  void setup(int pin){
    notePIN = pin;
    pinMode(notePIN, OUTPUT);
    digitalWrite(notePIN, LOW);
  }

  // 1. 従来のON（指定時間後に自動で閉じるモード）
  void on(long _ms) {
    timestamp = millis();
    flg_note_on = true;
    isAutoOff = true; // 自動消音を有効にする
    ms = _ms;
    digitalWrite(notePIN, HIGH);
  }

  // 2. 新しいON（Note Off信号が来るまで開きっぱなしにするモード）
  void on() {
    flg_note_on = true;
    isAutoOff = false; // 自動消音を無効にする
    digitalWrite(notePIN, HIGH);
  }

  void off() {
    flg_note_on = false;
    digitalWrite(notePIN, LOW);
  }

  void update(){
    // 自動消音モード、かつ時間が経過した場合のみ自動でoffにする
    if (flg_note_on == true && isAutoOff == true && (millis() - timestamp) >= ms) {
      off();
    }
  }

  long ms;
  boolean flg_note_on = false;
  boolean isAutoOff = false; // 自動消音を判定するフラグ
  long timestamp;
  int notePIN;
};