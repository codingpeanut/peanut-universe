#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <WiFi.h>
#include <HTTPClient.h>

// 設定Wi-Fi參數
const char* ssid = "Your-SSID";
const char* password = "password";

// 初始化LCD
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
    Serial.begin(115200);
    lcd.begin();
    lcd.backlight();

    // 連接Wi-Fi
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        Serial.println("Connecting to WiFi...");
    }
    Serial.println("Connected to WiFi");
    
    // 獲取公車資訊
    getBusInfo();
}

void loop() {
    // 定期更新公車資訊
    delay(60000); // 每分鐘更新一次
    getBusInfo();
}

void getBusInfo() {
    if (WiFi.status() == WL_CONNECTED) {
        HTTPClient http;
        http.begin("https://api.example.com/businfo"); // 替換為實際API網址
        int httpResponseCode = http.GET();

        if (httpResponseCode > 0) {
            String payload = http.getString();
            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print("Bus No: " + payload); // 根據API回應格式調整解析方式
        } else {
            Serial.println("Error on HTTP request");
        }
        http.end();
    } else {
        Serial.println("WiFi Disconnected");
    }
}