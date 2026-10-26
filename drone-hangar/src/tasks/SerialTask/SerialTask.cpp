#include "SerialTask.h"

SerialTask::SerialTask(HangarContext* context) : ctx(context) {}

void SerialTask::tick() {
  if (Serial.available() > 0) {
    String msg = Serial.readStringUntil('\n'); 
    msg.trim();
    if (msg == "TAKEOFF" || msg == "LAND") {
        ctx->serialCommand = msg;
    }
  }
}
