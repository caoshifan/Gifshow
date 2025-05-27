/*
  GIF动画库简单测试程序（修正版）
  功能：每个GIF完整播放一遍后自动切换
  硬件：SSD1306 OLED (128x64)
  连接：SDA=26, SCL=14
  
  修正：播放时长 = 每帧延迟 × 该GIF的总帧数
*/

#include <Wire.h>
#include "MyLibrary.h"

// 硬件配置
#define SDA_PIN 26
#define SCL_PIN 14
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1

// 播放配置
#define FRAME_DELAY 100      // 每帧延迟100ms

// 创建显示对象
MyLibrary gifDisplay(SCREEN_WIDTH, SCREEN_HEIGHT, OLED_RESET);

// 引用外部的帧数变量
extern const int bath_total_frames;
extern const int beady_total_frames;
extern const int book_total_frames;
extern const int birdvisit_total_frames;
extern const int cake_total_frames;
extern const int cry_total_frames;
extern const int dance_total_frames;
extern const int escape_total_frames;
extern const int eyebrow_total_frames;
extern const int sneeze_total_frames;
extern const int snow_total_frames;
extern const int transformers_total_frames;

// GIF信息
struct GifData {
  DisplayModel model;
  const char* name;
  const int* frameCount;
};

// 所有可用的GIF（按字母顺序）
GifData gifs[] = {
  {DisplayModel::BATH, "BATH", &bath_total_frames},
  {DisplayModel::BEADY, "BEADY", &beady_total_frames},
  {DisplayModel::BOOK, "BOOK", &book_total_frames},
  {DisplayModel::BIRDVISIT, "BIRDVISIT", &birdvisit_total_frames},
  {DisplayModel::CAKE, "CAKE", &cake_total_frames},
  {DisplayModel::CRY, "CRY", &cry_total_frames},
  {DisplayModel::DANCE, "DANCE", &dance_total_frames},
  {DisplayModel::ESCAPE, "ESCAPE", &escape_total_frames},
  {DisplayModel::EYEBROW, "EYEBROW", &eyebrow_total_frames},
  {DisplayModel::SNEEZE, "SNEEZE", &sneeze_total_frames},
  {DisplayModel::SNOW, "SNOW", &snow_total_frames},
  {DisplayModel::TRANSFORMERS, "TRANSFORMERS", &transformers_total_frames}
};

int currentGif = 0;
unsigned long gifStartTime = 0;
unsigned long gifDuration = 0;
const int totalGifs = sizeof(gifs) / sizeof(gifs[0]);

void setup() {
  Serial.begin(115200);
  Serial.println("🎬 GIF测试程序启动（修正版）");
  
  // 初始化I2C
  Wire.begin(SDA_PIN, SCL_PIN);
  Serial.printf("I2C: SDA=%d, SCL=%d\n", SDA_PIN, SCL_PIN);
  
  // 初始化显示屏
  gifDisplay.begin();
  gifDisplay.setFrameDelay(FRAME_DELAY);
  
  Serial.printf("共 %d 个GIF，每帧延迟 %d ms\n", totalGifs, FRAME_DELAY);
  Serial.println("每个GIF将完整播放一遍后切换\n");
  
  // 开始播放第一个GIF
  playGif(0);
}

void loop() {
  // 更新动画
  gifDisplay.update();
  
  // 检查当前GIF是否播放完成
  if (millis() - gifStartTime >= gifDuration) {
    nextGif();
  }
}

void playGif(int index) {
  currentGif = index;
  GifData& gif = gifs[currentGif];
  
  // 开始播放GIF
  gifDisplay.show(gif.model);
  gifStartTime = millis();
  
  // 计算这个GIF的总播放时长：帧数 × 每帧延迟
  gifDuration = (*gif.frameCount) * FRAME_DELAY;
  
  Serial.printf("[%d/%d] 播放: %s (帧数: %d, 时长: %.1f秒)\n", 
                currentGif + 1, totalGifs, gif.name, 
                *gif.frameCount, gifDuration / 1000.0);
}

void nextGif() {
  int next = (currentGif + 1) % totalGifs;
  if (next == 0) {
    Serial.println("--- 轮播重新开始 ---");
  }
  playGif(next);
} 