#include <Arduino.h>
#include "MyLibrary.h"

// 定义 OLED 屏幕的尺寸和复位引脚
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET    -1

// 初始化 MyLibrary
MyLibrary myDisplay(SCREEN_WIDTH, SCREEN_HEIGHT, OLED_RESET);

void setup() {
    Serial.begin(115200);
    myDisplay.begin(); // 初始化屏幕
    myDisplay.setFrameDelay(20); // 设置每帧间隔时间（毫秒）
}

void loop() {
    static bool isSnow = true; // 交替播放 SNOW 和 BATH
    myDisplay.show(isSnow ? DisplayModel::DANCE : DisplayModel::BATH);
    isSnow = !isSnow;  // 切换模式

    for (int i = 0; i < 200; i++) {  // 播放 200 次帧动画后切换模式
        myDisplay.update();
        delay(50); // 防止过快刷新
    }
}
