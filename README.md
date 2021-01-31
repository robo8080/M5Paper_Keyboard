# M5Paper_Keyboard
M5Paper_Keyboardは、M5Paperで動くシリアルI/Fのキーボードです。<br>
これは、M5Paper_FactoryTestのキーボードの処理を抜き出して改造したものです。<br><br>
ベースにしたオリジナルはこちら。<br>
M5Paper_FactoryTest <https://github.com/m5stack/M5Paper_FactoryTest><br>

![画像1](images/image1.png)<br><br>

### 必要な物 ###
* [M5Paper](http://www.m5stack.com/ "Title")<br>
* Arduino IDE (1.8.13で動作確認をしました。)<br>
* [Arduino core for the ESP32](https://github.com/espressif/arduino-esp32 "Title")
* [M5Paper Library](https://github.com/m5stack/M5EPD "Title")
<br>

ライブラリはArduino IDEの[スケッチ | ライブラリをインクルード |ライブラリを管理...] からインストールすると簡単です。

### シリアルポートの仕様 ###
* M5PaperのPORT Cを使用します。設定は以下の通り。<br>
    // Serial2.begin(unsigned long baud, uint32_t config, int8_t rxPin, int8_t txPin, bool invert)<br>
    Serial2.begin(115200, SERIAL_8N1, 19, 18);

### 補足 ###
* 電源を切る場合は、M5Paperの裏側の”BATTERY OFF”ボタンを使用してください。<br>
* "Fn"キーは未使用ですので機能拡張等に使用してください。<br><br>

---

M5Paper_Keyboardの動作確認用のM5Stackプログラム(M5Stack_Serial2_test)を用意してあります。<br>

![画像2](images/image2.png)<br><br>

### 必要な物 ###
* [M5Stack](http://www.m5stack.com/ "Title") (Fireで動作確認をしました。)<br>
* Arduino IDE (1.8.13で動作確認をしました。)<br>
* [Arduino core for the ESP32](https://github.com/espressif/arduino-esp32 "Title")<br>
* [M5Stack Library](https://github.com/m5stack/M5Stack "Title")
* [LovyanGFXライブラリ](https://github.com/lovyan03/LovyanGFX "Title")

ライブラリはArduino IDEの[スケッチ | ライブラリをインクルード |ライブラリを管理...] からインストールすると簡単です。

### シリアルポートの仕様 ###
* M5StackのPORT Cを使用します。設定は以下の通り。<br>
    // Serial2.begin(unsigned long baud, uint32_t config, int8_t rxPin, int8_t txPin, bool invert)<br>
    Serial2.begin(115200, SERIAL_8N1, 16, 17);<br><br>
注意：M5Stack Fireを使用する場合はPSRAMを無効にする必要があります。<br><br>
![画像3](images/image3.png)<br><br>

---

### クロスケーブルの作り方 ###
* M5StackSerial2_testでM5StackとM5Paper_Keyboardを接続するにはクロスケーブルが必要です。<br>
赤のケーブル(電源）を抜き、白と黄色のケーブルをクロスさせます。<br><br>
![画像4](images/image4.png)<br><br>
* コネクタの爪の部分を尖った物で持ち上げてやればケーブルは簡単に抜けます。 <br><br>
![画像5](images/image5.png)<br><br>
<br><br>

