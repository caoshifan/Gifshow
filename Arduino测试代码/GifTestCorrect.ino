/*
  GIF动画库测试程序（修正版）
  功能：每个GIF完整播放一遍后切换到下一个
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
extern const int cry_total_frames;
extern const int book_total_frames;
extern const int birdvisit_total_frames;
extern const int cake_total_frames;
extern const int snow_total_frames;
extern const int transformers_total_frames;
extern const int sneeze_total_frames;
extern const int eyebrow_total_frames;
extern const int escape_total_frames;
extern const int beady_total_frames;
extern const int dance_total_frames;
extern const int bath_total_frames;

// GIF信息结构体
struct GifInfo {
  DisplayModel model;
  const char* name;
  const int* frameCount;
};

// 所有GIF信息数组
GifInfo gifList[] = {
  {DisplayModel::CRY, "CRY", &cry_total_frames},
  {DisplayModel::BOOK, "BOOK", &book_total_frames},
  {DisplayModel::BIRDVISIT, "BIRDVISIT", &birdvisit_total_frames},
  {DisplayModel::CAKE, "CAKE", &cake_total_frames},
  {DisplayModel::SNOW, "SNOW", &snow_total_frames},
  {DisplayModel::TRANSFORMERS, "TRANSFORMERS", &transformers_total_frames},
  {DisplayModel::SNEEZE, "SNEEZE", &sneeze_total_frames},
  {DisplayModel::EYEBROW, "EYEBROW", &eyebrow_total_frames},
  {DisplayModel::ESCAPE, "ESCAPE", &escape_total_frames},
  {DisplayModel::BEADY, "BEADY", &beady_total_frames},
  {DisplayModel::DANCE, "DANCE", &dance_total_frames},
  {DisplayModel::BATH, "BATH", &bath_total_frames}
};

int currentGif = 0;
unsigned long gifStartTime = 0;
unsigned long currentGifDuration = 0;  // 当前GIF的总播放时长
const int totalGifs = sizeof(gifList) / sizeof(gifList[0]);

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
  if (millis() - gifStartTime >= currentGifDuration) {
    nextGif();
  }
  
  // 可选：检查串口命令
  checkSerialCommands();
}

void playGif(int index) {
  if (index < 0 || index >= totalGifs) return;
  
  currentGif = index;
  GifInfo& gif = gifList[currentGif];
  
  // 开始播放GIF
  gifDisplay.show(gif.model);
  gifStartTime = millis();
  
  // 计算这个GIF的总播放时长
  currentGifDuration = (*gif.frameCount) * FRAME_DELAY;
  
  // 输出详细信息
  Serial.printf("[%d/%d] 播放: %s\n", 
                currentGif + 1, totalGifs, gif.name);
  Serial.printf("       帧数: %d, 播放时长: %.1f 秒\n", 
                *gif.frameCount, currentGifDuration / 1000.0);
}

void nextGif() {
  int next = (currentGif + 1) % totalGifs;
  if (next == 0) {
    Serial.println("\n--- 🔄 轮播完成，重新开始 ---\n");
  }
  playGif(next);
}

void printGifList() {
  Serial.println("\n📋 GIF信息列表:");
  Serial.println("序号 | 名称        | 帧数 | 播放时长");
  Serial.println("-----|-------------|------|----------");
  
  for (int i = 0; i < totalGifs; i++) {
    GifInfo& gif = gifList[i];
    float duration = (*gif.frameCount) * FRAME_DELAY / 1000.0;
    Serial.printf("%2d   | %-11s | %3d  | %.1f 秒\n", 
                  i + 1, gif.name, *gif.frameCount, duration);
  }
  Serial.println();
}

void showCurrentStatus() {
  GifInfo& gif = gifList[currentGif];
  unsigned long elapsed = millis() - gifStartTime;
  float progress = (float)elapsed / currentGifDuration * 100;
  
  Serial.printf("当前: %s (%d/%d)\n", gif.name, currentGif + 1, totalGifs);
  Serial.printf("帧数: %d, 总时长: %.1f秒\n", *gif.frameCount, currentGifDuration / 1000.0);
  Serial.printf("进度: %.1f%% (%.1f/%.1f秒)\n", 
                progress, elapsed / 1000.0, currentGifDuration / 1000.0);
}

// 串口命令处理
void checkSerialCommands() {
  if (Serial.available()) {
    String command = Serial.readString();
    command.trim();
    
    if (command == "list") {
      printGifList();
    } else if (command == "next") {
      Serial.println("手动切换到下一个GIF");
      nextGif();
    } else if (command == "info") {
      showCurrentStatus();
    } else if (command.startsWith("speed ")) {
      int newDelay = command.substring(6).toInt();
      if (newDelay > 0 && newDelay <= 1000) {
        gifDisplay.setFrameDelay(newDelay);
        Serial.printf("帧延迟设置为: %dms\n", newDelay);
        // 重新计算当前GIF的剩余时间
        currentGifDuration = (*gifList[currentGif].frameCount) * newDelay;
        gifStartTime = millis();  // 重新开始计时
      } else {
        Serial.println("无效的延迟值 (1-1000ms)");
      }
    } else if (command.startsWith("show ")) {
      int gifIndex = command.substring(5).toInt() - 1;
      if (gifIndex >= 0 && gifIndex < totalGifs) {
        Serial.printf("手动播放GIF: %s\n", gifList[gifIndex].name);
        playGif(gifIndex);
      } else {
        Serial.printf("无效的GIF索引 (1-%d)\n", totalGifs);
      }
    } else if (command == "help") {
      printHelp();
    } else if (command == "stats") {
      printStats();
    }
  }
}

void printHelp() {
  Serial.println("\n🆘 可用命令:");
  Serial.println("  list          - 显示所有GIF信息");
  Serial.println("  next          - 切换到下一个GIF");
  Serial.println("  info          - 显示当前播放状态");
  Serial.println("  speed <1-1000> - 设置帧延迟(ms)");
  Serial.println("  show <1-12>   - 播放指定GIF");
  Serial.println("  stats         - 显示统计信息");
  Serial.println("  help          - 显示此帮助信息\n");
}

void printStats() {
  Serial.println("\n📊 统计信息:");
  
  int totalFrames = 0;
  float totalTime = 0;
  int minFrames = 999, maxFrames = 0;
  
  for (int i = 0; i < totalGifs; i++) {
    int frames = *gifList[i].frameCount;
    totalFrames += frames;
    if (frames < minFrames) minFrames = frames;
    if (frames > maxFrames) maxFrames = frames;
  }
  
  totalTime = totalFrames * FRAME_DELAY / 1000.0;
  
  Serial.printf("GIF总数: %d\n", totalGifs);
  Serial.printf("总帧数: %d\n", totalFrames);
  Serial.printf("完整轮播时长: %.1f 秒 (%.1f 分钟)\n", totalTime, totalTime / 60);
  Serial.printf("平均帧数: %.1f\n", (float)totalFrames / totalGifs);
  Serial.printf("帧数范围: %d - %d\n", minFrames, maxFrames);
  Serial.printf("当前帧延迟: %d ms\n", FRAME_DELAY);
  Serial.println();
} 