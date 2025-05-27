/*
  GIF动画库测试程序
  功能：轮播显示所有可用的GIF动画
  硬件：SSD1306 OLED显示屏 (128x64)
  连接：SDA=26, SCL=14
  
  作者：GIF动画库管理器 v2.1.1
  日期：2024
*/

#include <Wire.h>
#include "MyLibrary.h"

// OLED显示屏配置
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1   // 没有使用复位引脚

// I2C引脚配置
#define SDA_PIN 26
#define SCL_PIN 14

// 动画播放配置
#define FRAME_DELAY 80        // 每帧延迟时间(ms)
#define GIF_DURATION 5000     // 每个GIF播放时长(ms)

// 创建库实例
MyLibrary gifDisplay(SCREEN_WIDTH, SCREEN_HEIGHT, OLED_RESET);

// 可用的GIF动画数组
DisplayModel gifList[] = {
  DisplayModel::CRY,          // 哭泣
  DisplayModel::BOOK,         // 书本
  DisplayModel::BIRDVISIT,    // 鸟儿来访
  DisplayModel::CAKE,         // 蛋糕
  DisplayModel::SNOW,         // 雪花
  DisplayModel::TRANSFORMERS, // 变形金刚
  DisplayModel::SNEEZE,       // 打喷嚏
  DisplayModel::EYEBROW,      // 眉毛
  DisplayModel::ESCAPE,       // 逃跑
  DisplayModel::BEADY,        // 眼珠
  DisplayModel::DANCE,        // 舞蹈
  DisplayModel::BATH          // 洗澡
};

// GIF名称数组（用于串口输出）
const char* gifNames[] = {
  "CRY", "BOOK", "BIRDVISIT", "CAKE", 
  "SNOW", "TRANSFORMERS", "SNEEZE", "EYEBROW",
  "ESCAPE", "BEADY", "DANCE", "BATH"
};

// 全局变量
int currentGifIndex = 0;                    // 当前GIF索引
unsigned long lastGifChange = 0;            // 上次切换GIF的时间
const int totalGifs = sizeof(gifList) / sizeof(gifList[0]);  // GIF总数

void setup() {
  // 初始化串口
  Serial.begin(115200);
  Serial.println("=================================");
  Serial.println("🎬 GIF动画库测试程序启动");
  Serial.println("=================================");
  
  // 初始化I2C（自定义引脚）
  Wire.begin(SDA_PIN, SCL_PIN);
  Serial.printf("📡 I2C初始化完成 (SDA:%d, SCL:%d)\n", SDA_PIN, SCL_PIN);
  
  // 初始化显示屏
  gifDisplay.begin();
  Serial.println("🖥️ OLED显示屏初始化完成");
  
  // 设置帧延迟
  gifDisplay.setFrameDelay(FRAME_DELAY);
  Serial.printf("⏱️ 帧延迟设置为: %dms\n", FRAME_DELAY);
  
  // 显示启动信息
  Serial.printf("🎯 准备轮播 %d 个GIF动画\n", totalGifs);
  Serial.printf("⏰ 每个GIF播放时长: %dms\n", GIF_DURATION);
  Serial.println("🚀 开始播放...\n");
  
  // 开始播放第一个GIF
  startGif(0);
}

void loop() {
  // 更新当前GIF动画
  gifDisplay.update();
  
  // 检查是否需要切换到下一个GIF
  if (millis() - lastGifChange >= GIF_DURATION) {
    nextGif();
  }
  
  // 小延迟以避免过度占用CPU
  delay(1);
}

void startGif(int index) {
  if (index >= 0 && index < totalGifs) {
    currentGifIndex = index;
    gifDisplay.show(gifList[currentGifIndex]);
    lastGifChange = millis();
    
    // 串口输出当前播放的GIF信息
    Serial.printf("🎬 正在播放: %s (第%d/%d个)\n", 
                  gifNames[currentGifIndex], 
                  currentGifIndex + 1, 
                  totalGifs);
  }
}

void nextGif() {
  // 切换到下一个GIF
  int nextIndex = (currentGifIndex + 1) % totalGifs;
  
  if (nextIndex == 0) {
    Serial.println("\n🔄 轮播完成，重新开始...\n");
  }
  
  startGif(nextIndex);
}

void printGifList() {
  Serial.println("\n📋 可用的GIF动画列表:");
  Serial.println("----------------------------");
  for (int i = 0; i < totalGifs; i++) {
    Serial.printf("%d. %s\n", i + 1, gifNames[i]);
  }
  Serial.println("----------------------------\n");
}

// 可选：手动控制函数（通过串口命令）
void checkSerialCommands() {
  if (Serial.available()) {
    String command = Serial.readString();
    command.trim();
    
    if (command == "list") {
      printGifList();
    } else if (command == "next") {
      nextGif();
    } else if (command == "info") {
      Serial.printf("当前: %s, 帧延迟: %dms\n", 
                    gifNames[currentGifIndex], 
                    gifDisplay.getFrameDelay());
    } else if (command.startsWith("speed ")) {
      int newDelay = command.substring(6).toInt();
      if (newDelay > 0 && newDelay <= 1000) {
        gifDisplay.setFrameDelay(newDelay);
        Serial.printf("帧延迟设置为: %dms\n", newDelay);
      } else {
        Serial.println("无效的延迟值 (1-1000ms)");
      }
    } else if (command.startsWith("show ")) {
      int gifIndex = command.substring(5).toInt() - 1;
      if (gifIndex >= 0 && gifIndex < totalGifs) {
        startGif(gifIndex);
      } else {
        Serial.printf("无效的GIF索引 (1-%d)\n", totalGifs);
      }
    } else if (command == "help") {
      printHelp();
    }
  }
}

void printHelp() {
  Serial.println("\n🆘 可用命令:");
  Serial.println("  list          - 显示所有GIF列表");
  Serial.println("  next          - 切换到下一个GIF");
  Serial.println("  info          - 显示当前状态");
  Serial.println("  speed <1-1000> - 设置帧延迟(ms)");
  Serial.println("  show <1-12>   - 播放指定GIF");
  Serial.println("  help          - 显示此帮助信息\n");
} 