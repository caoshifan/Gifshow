// MyLibrary.h
#ifndef MyLibrary_h
#define MyLibrary_h

#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "gif_frames.h"  // 包含帧数据头文件

enum class DisplayModel {
    SNEEZE,
    EYEBROW,
    ESCAPE,
    BEADY,
    DANCE,
    SNOW, 
    BATH,
    INVALID
};

class MyLibrary {
public:
    MyLibrary(int width, int height, int resetPin);
    void begin();
    void show(DisplayModel model);             // 播放GIF动画
    void update();
    void setFrameDelay(int delayMs); 
    int getFrameDelay() const;// 设置帧间隔时间

private:
    Adafruit_SSD1306 display;
    unsigned long lastFrameTime = 0;
    int currentFrame = 0;
    int frameDelay = 100;    // 默认每帧100ms
    DisplayModel currentModel = DisplayModel::INVALID;
};

#endif