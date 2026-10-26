#include "HangarTask.h"

HangarTask::HangarTask(HangarContext* context) : ctx(context), timerStarted(false) {}

void HangarTask::startTimer() { stateTimer = millis(); timerStarted = true; }
void HangarTask::resetTimer() { timerStarted = false; }
bool HangarTask::checkTimer(unsigned long targetTime) {
    return timerStarted && (millis() - stateTimer >= targetTime);
}

void HangarTask::tick() {
    static bool previousPreAlarm = false;

    if (ctx->isPreAlarm && !previousPreAlarm && ctx->currentState != ALARM) {
        ctx->lcd->clear(); 
        ctx->lcd->print("PRE-ALARM");
    } 
    else if (!ctx->isPreAlarm && previousPreAlarm && ctx->currentState != ALARM) {
        ctx->lcd->clear();
        switch(ctx->currentState) {
            case DRONE_INSIDE: ctx->lcd->print("DRONE INSIDE"); break;
            case TAKE_OFF:     ctx->lcd->print("TAKE OFF"); break;
            case DRONE_OUT:    ctx->lcd->print("DRONE OUT"); break;
            case LANDING:      ctx->lcd->print("LANDING"); break;
            case INIT:         ctx->lcd->print("DRONE INSIDE"); break;
            default: break;
        }
    }
    previousPreAlarm = ctx->isPreAlarm;

    if (ctx->isCriticalAlarm && ctx->currentState != ALARM) {
        ctx->previousState = ctx->currentState;
        ctx->door->close(); 
        ctx->l3->turnOn(); 
        ctx->l1->turnOff();
        ctx->lcd->clear(); ctx->lcd->print("ALARM");
        Serial.println("STATE:ALARM");
        ctx->currentState = ALARM;
        ctx->isBlinkingPhase = false;
    }

    switch (ctx->currentState) {
        case INIT:
            ctx->door->close(); 
            ctx->l1->turnOn(); ctx->l2->turnOff(); ctx->l3->turnOff();
            ctx->lcd->clear(); ctx->lcd->print("DRONE INSIDE");
            Serial.println("STATE:NORMAL");
            ctx->currentState = DRONE_INSIDE;
            break;

        case DRONE_INSIDE:
            if (ctx->serialCommand == "TAKEOFF" && !ctx->isPreAlarm) {
                ctx->door->open(); 
                ctx->lcd->clear(); ctx->lcd->print("TAKE OFF");
                ctx->isBlinkingPhase = true; 
                resetTimer(); 
                ctx->currentState = TAKE_OFF;
            }
            ctx->serialCommand = "";
            break;

        case TAKE_OFF:
            if (ctx->sonar->getDistance() > D1) {
                if (!timerStarted) startTimer();
                if (checkTimer(T1)) {
                    ctx->door->close(); 
                    ctx->lcd->clear(); ctx->lcd->print("DRONE OUT");
                    ctx->isBlinkingPhase = false; 
                    ctx->currentState = DRONE_OUT;
                }
            } else { 
                resetTimer(); 
            }
            break;

        case DRONE_OUT:
            if (ctx->serialCommand == "LAND" && ctx->pir->isDetected() && !ctx->isPreAlarm) {
                ctx->door->open(); 
                ctx->lcd->clear(); ctx->lcd->print("LANDING");
                ctx->isBlinkingPhase = true; 
                resetTimer(); 
                ctx->currentState = LANDING;
            }
            ctx->serialCommand = "";
            break;

        case LANDING: {
            long dist = ctx->sonar->getDistance();
            Serial.print("DIST:"); Serial.println(dist);
            if (dist < D2) {
                if (!timerStarted) startTimer();
                if (checkTimer(T2)) {
                    ctx->door->close(); 
                    ctx->lcd->clear(); ctx->lcd->print("DRONE INSIDE");
                    ctx->isBlinkingPhase = false; 
                    ctx->currentState = DRONE_INSIDE;
                }
            } else { 
                resetTimer(); 
            }
            break;
        }

        case ALARM:
            if (ctx->btnReset->isPressed()) {
                float currentTemp = ctx->tempSensor->getTemperature();
                Serial.println("STATE:ALARM");
                if (currentTemp < 38.0) { 
                    ctx->l3->turnOff(); 
                    ctx->isCriticalAlarm = false; 
                    ctx->isPreAlarm = false;
                    
                    ctx->lcd->clear();
                    if (ctx->previousState == DRONE_OUT) {
                        ctx->lcd->print("DRONE OUT");
                        Serial.println("STATE:NORMAL");
                    } else if (ctx->previousState == DRONE_INSIDE || ctx->previousState == INIT) {
                        ctx->lcd->print("DRONE INSIDE");
                        ctx->l1->turnOn();
                        Serial.println("STATE:NORMAL");
                    }
                    ctx->currentState = ctx->previousState;
                } else {
                    Serial.println("Impossibile resettare: Temperatura ancora alta.");
                }
            }
            break;
    }
}