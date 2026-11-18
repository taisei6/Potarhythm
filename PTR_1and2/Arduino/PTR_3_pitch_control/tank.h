#include <SPI.h>

// --- L6470関数のプロトタイプ宣言（.hファイル内で呼び出すために必要） ---
void L6470_resetdevice();
void L6470_run(int dia, long spd);
void L6470_softstop();
void L6470_setparam_acc(long val);
void L6470_setparam_dec(long val);
void L6470_setparam_maxspeed(long val);
void L6470_setparam_minspeed(long val);
void L6470_setparam_fsspd(long val);
void L6470_setparam_kvalhold(long val);
void L6470_setparam_kvalrun(long val);
void L6470_setparam_kvalacc(long val);
void L6470_setparam_kvaldec(long val);
void L6470_setparam_stepmood(long val);
// ----------------------------------------------------------------

// 競合を避けるため、BUSYピンをA0からA2に変更
#define PIN_SPI_SS 10
#define PIN_BUSY A2

class Tank {
  public:
  Tank(){};
  ~Tank(){};
  
  void setup(){
    pinMode(2, INPUT_PULLUP);
    
    // SPIとL6470のピン設定
    pinMode(PIN_SPI_SS, OUTPUT);
    pinMode(PIN_BUSY, INPUT);
    digitalWrite(PIN_SPI_SS, HIGH);
    
    SPI.begin();
    SPI.setDataMode(SPI_MODE3);
    SPI.setBitOrder(MSBFIRST);

    // L6470の初期化とパラメータ設定
    L6470_resetdevice();
    L6470_setup();

    // ==========================================================
    // 【パターン1】 電源を入れたら常に一定速度で回り続ける場合
    // ※ パターン2を使用する場合は、下の2行をコメントアウトしてください。
    // ==========================================================
    L6470_run(0, targetSpeed); 
    isRunning = true;
  }
  
  void update(){
    int sensorVal = digitalRead(2);
    
    // ==========================================================
    // 【パターン2】 2番ピンがHIGHの時だけモーターを回す場合
    // ※ パターン1を使用する場合は、以下のif〜elseブロック全体を
    //    コメントアウトしてください。
    // ==========================================================
    // if (sensorVal == HIGH) {
    //   if (isRunning == false) {
    //     // 停止中なら回転開始（内部設定に従い自動で滑らかに加速します）
    //     L6470_run(0, targetSpeed);
    //     isRunning = true;
    //   }
    // } else {
    //   if (isRunning == true) {
    //     // 回転中なら減速して停止（保持トルクあり）
    //     L6470_softstop(); 
    //     isRunning = false;
    //   }
    // }
  }

  private:
  boolean isRunning = false;
  long targetSpeed = 50000;

  // L6470内部のレジスタ設定（ハードウェア自動加減速の設定）
  void L6470_setup() {
    L6470_setparam_acc(0x40);      // 加速度
    L6470_setparam_dec(0x40);      // 減速度
    L6470_setparam_maxspeed(0x100); 
    L6470_setparam_minspeed(0x01); // 最小速度
    L6470_setparam_fsspd(0x3ff);   
    L6470_setparam_kvalhold(0x50); 
    L6470_setparam_kvalrun(0x50);  
    L6470_setparam_kvalacc(0x50);  
    L6470_setparam_kvaldec(0x50);  
    L6470_setparam_stepmood(0x03); 
  }
};