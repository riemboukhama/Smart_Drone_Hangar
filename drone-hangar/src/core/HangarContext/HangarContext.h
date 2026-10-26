#ifndef HANGAR_CONTEXT_H
#define HANGAR_CONTEXT_H

#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
#include "../../hal/Led/Led.h"
#include "../../hal/Button/Button.h"
#include "../../hal/Sonar/Sonar.h"
#include "../../hal/Pir/Pir.h"
#include "../../hal/TempSensor/TempSensor.h"
#include "../../hal/HangarDoor/HangarDoor.h"

enum HangarState { INIT, DRONE_INSIDE, TAKE_OFF, DRONE_OUT, LANDING, ALARM };

class HangarContext {
public:
    HangarState currentState = INIT;
    HangarState previousState = INIT;
    bool isPreAlarm = false;
    bool isCriticalAlarm = false;
    String serialCommand = "";
    bool isBlinkingPhase = false;

    Led* l1; Led* l2; Led* l3;
    Button* btnReset;
    Sonar* sonar;
    Pir* pir;
    TempSensor* tempSensor;
    HangarDoor* door;
    LiquidCrystal_I2C* lcd;

    HangarContext(Led* led1, Led* led2, Led* led3, Button* btn, Sonar* snr, 
                  Pir* p, TempSensor* ts, HangarDoor* dr, LiquidCrystal_I2C* dsp)
        : l1(led1), l2(led2), l3(led3), btnReset(btn), sonar(snr), 
          pir(p), tempSensor(ts), door(dr), lcd(dsp) {}
};

#endif