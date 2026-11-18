#include <SPI.h>
#include <MsTimer2.h>

// モーターピン設定
#define PIN_SPI_MOSI 11
#define PIN_SPI_MISO 12
#define PIN_SPI_SCK 13
#define PIN_SPI_SS 10
#define PIN_BUSY 9

#define TARGET_SPEED 50000 // 目標速度
#define MIN_SPEED   100     // 開始時の最低速度
#define ACCEL_STEP 100     // 1ステップあたりの加速量
#define ACCEL_INTERVAL 50  // 加速の間隔(ms)
#define MOTOR_DIRECTION 1 //回転方向

void setup() {
  delay(1000);
  pinMode(PIN_SPI_MOSI, OUTPUT);
  pinMode(PIN_SPI_MISO, INPUT);
  pinMode(PIN_SPI_SCK, OUTPUT);
  pinMode(PIN_SPI_SS, OUTPUT);
  pinMode(PIN_BUSY, INPUT);
  SPI.begin();
  SPI.setDataMode(SPI_MODE3);
  SPI.setBitOrder(MSBFIRST);

  digitalWrite(PIN_SPI_SS, HIGH);

  L6470_resetdevice(); // L6470リセット
  L6470_setup();       // L6470を設定
  
  // --- 加速処理 ---
  // 最低速度から目標速度まで、少しずつ速度を上げていく
  for (long s = MIN_SPEED; s <= TARGET_SPEED; s += ACCEL_STEP) {
    L6470_run(MOTOR_DIRECTION, s);            // 現在の速度(s)で回転命令
    delay(ACCEL_INTERVAL);      // 次の加速まで少し待機
  }
  
  // 念のため、加速完了後に最終的な目標速度のコマンドを1回だけ送信
  L6470_run(MOTOR_DIRECTION, TARGET_SPEED);
}

void loop() {
  // 【修正ポイント1】通信スパムの解消
  // L6470は一度「run」コマンドを受け取ると、停止命令が来るまで
  // マイコン側で勝手にパルスを生成して回り続けます。
  // ここで連続送信するとICの処理がパンクして熱を持つ原因になるため、空にしておきます。
}

void L6470_setup() {
  // L6470内部のレジスタ設定
  L6470_setparam_acc(0x40);      // 加速度
  L6470_setparam_dec(0x40);      // 減速度
  L6470_setparam_maxspeed(0x100); // 最大速度
  L6470_setparam_minspeed(0x01);  // 最小速度
  L6470_setparam_fsspd(0x3ff);   // フルステップへの切替速度
  
  // 【修正ポイント2】熱対策のためのKVAL（電圧/電流）最適化設定
  // 12V電源 ＆ 17HS15-1684S-HG5 (相抵抗1.6Ω/定格1.68A) 用
  // 発熱を確実に防ぐため、計算上の最大値(0x39)から少し余裕を持たせた「0x30」に設定しています。
  
  L6470_setparam_kvalhold(0x15); // 停止時の電圧 (約0.6A) - 停止中の発熱防止のため低めに設定
  L6470_setparam_kvalrun(0x30);  // 定速回転時の電圧 (約1.4A) - 定格より約15%下げて発熱を抑制
  L6470_setparam_kvalacc(0x30);  // 加速時の電圧
  L6470_setparam_kvaldec(0x30);  // 減速時の電圧
  
  L6470_setparam_stepmood(0x03); // ステップモード
}