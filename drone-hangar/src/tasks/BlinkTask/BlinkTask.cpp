#include "BlinkTask.h"

BlinkTask::BlinkTask(HangarContext* context) : ctx(context) {}

void BlinkTask::tick() {
  if (ctx->isBlinkingPhase) ctx->l2->toggle();
  else ctx->l2->turnOff();
}
