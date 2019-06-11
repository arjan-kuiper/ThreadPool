#include <Arduino.h>
#include <ThreadPool.h>

void setup() {
  Serial.begin(115200);
  ThreadPool tp(5, 3);
}

void loop() {
  
}