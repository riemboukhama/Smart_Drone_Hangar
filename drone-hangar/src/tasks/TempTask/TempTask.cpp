#include "TempTask.h"

TempTask::TempTask(HangarContext* context) : ctx(context), timerTemp1(0), timerTemp2(0) {}

void TempTask::tick() {
    if (ctx->currentState != DRONE_OUT) {
        float temp = ctx->tempSensor->getTemperature();
        
        static unsigned long lastPrint = 0;
        if (millis() - lastPrint >= 2000) {
            Serial.print("Temperatura: ");
            Serial.print(temp);
            Serial.println(" °C");
            lastPrint = millis();
        }

        if (temp >= Temp2) {
            if (timerTemp2 == 0) timerTemp2 = millis();
            if (millis() - timerTemp2 >= T4) {
                ctx->isCriticalAlarm = true;
            }
        } else {
            timerTemp2 = 0;
            //reset manuale con pulsante
        }

        if (temp >= Temp1 && temp < Temp2) {
            if (timerTemp1 == 0) timerTemp1 = millis();
            if (millis() - timerTemp1 >= T3) {
                ctx->isPreAlarm = true;
            }
        } else {
            timerTemp1 = 0;
            ctx->isPreAlarm = false;
        }
    }
}