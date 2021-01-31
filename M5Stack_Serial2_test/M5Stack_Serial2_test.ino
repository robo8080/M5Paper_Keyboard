#include <M5Stack.h>

 #define LGFX_M5STACK               // M5Stack (Basic / Gray / Go / Fire)
//  #define LGFX_AUTODETECT // 自動認識 (M5Stack, M5StickC/CPlus, ODROID-GO, TTGO T-Watch, TTGO T-Wristband, LoLin D32 Pro, ESP-WROVER-KIT)
#include <LovyanGFX.hpp>

static LGFX lcd;                 // LGFXのインスタンスを作成。
void setup() {
  M5.begin(false, false, false, false);
  // put your setup code here, to run once:
  Serial.begin(115200);
  // Serial2.begin(unsigned long baud, uint32_t config, int8_t rxPin, int8_t txPin, bool invert)
  Serial2.begin(115200, SERIAL_8N1, 16, 17);
  lcd.init();
  lcd.clear();
  lcd.setRotation(1);
  lcd.setCursor(0, 0);
  lcd.setTextScroll(true);
  lcd.setTextSize(2);
  Serial.println("START");
  lcd.println("START");
}

void loop() {
   M5.update();     // update button state
  // put your main code here, to run repeatedly:
  // シリアル通信を受信したときの処理
  if(Serial2.available()) {
    lcd.print("Recived : ");
    // 受信データを取得
    char ch = Serial2.read();
    Serial.printf("%c : %02x\r\n", ch, ch);
    lcd.printf("%c : %02x\r\n", ch, ch);
  }
  // ボタンAが押された時の処理
  if (M5.BtnA.wasPressed()) {
    lcd.clear();
    lcd.setRotation(1);
    lcd.setCursor(0, 0);
    Serial.println("START");
    lcd.println("START");
  } 
  // ボタンBが押された時の処理
  if (M5.BtnB.wasPressed()) {
    lcd.clear();
    lcd.setRotation(3);
    lcd.setCursor(0, 0);
    Serial.println("START");
    lcd.println("START");
  } 
}
