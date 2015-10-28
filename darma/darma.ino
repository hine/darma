/*
 * DaRMA 太鼓コントローラー
 * Copyright (c) 2015 Daisuke IMAI
 *
 * This software is released under the MIT License.
 * http://opensource.org/licenses/mit-license.php
 */
#include <SoftwareSerial.h>

// ピンの設定
int ledPin = 13;        // LEDをデジタルピン13に接続
int controler0_pin = 0; // 太鼓コントローラ0番の接続
int controler1_pin = 1; // 太鼓コントローラ0番の接続
int controler2_pin = 2; // 太鼓コントローラ0番の接続
int controler3_pin = 3; // 太鼓コントローラ0番の接続

// コントローラーの値の処理に必要な変数定義
int controler0 = 0;     // 読み取った値を格納する変数
int controler1 = 0;     // 読み取った値を格納する変数
int controler2 = 0;     // 読み取った値を格納する変数
int controler3 = 0;     // 読み取った値を格納する変数
int controler0_old = 0;     // 読み取った値を格納する変数
int controler1_old = 0;     // 読み取った値を格納する変数
int controler2_old = 0;     // 読み取った値を格納する変数
int controler3_old = 0;     // 読み取った値を格納する変数
int controler0_hit = false;     // 読み取った値を格納する変数
int controler1_hit = false;     // 読み取った値を格納する変数
int controler2_hit = false;     // 読み取った値を格納する変数
int controler3_hit = false;     // 読み取った値を格納する変数

SoftwareSerial konashiSerial(8, 9); // RX, TX

void setup() {
  // 初期化

  // デバグ用のシリアル
  Serial.begin(9600);        // シリアル通信の初期化

  // konashiと通信するためのシリアルの準備
  konashiSerial.begin(9600);

  // ピンの出力設定（コントローラーのピンはアナログ入力なので設定しなくても良い）
  pinMode(ledPin, OUTPUT);   // ピン13を出力に設定
}

// アナログ値を11桁のデジタル値にマッピングする
int a_to_d(int analog_value) {
  int digital_value = 0;
  if (analog_value < 23) {
    digital_value = 0;
  } else {
    digital_value = int((analog_value - 24) / 100) + 1;
  }
  return digital_value;
}

void loop() {
  controler0 = a_to_d(analogRead(controler0_pin));    // アナログピンを読み取る
  controler1 = a_to_d(analogRead(controler1_pin));    // アナログピンを読み取る
  controler2 = a_to_d(analogRead(controler2_pin));    // アナログピンを読み取る
  controler3 = a_to_d(analogRead(controler3_pin));    // アナログピンを読み取る
  Serial.write(255);
  delay(3);
  Serial.write(controler0 * 16 + controler1);
  delay(3);
  Serial.write(controler2 * 16 + controler3);
  delay(3);
}


