#include "src/core/HangarContext/HangarContext.h"
#include "src/core/Scheduler/Scheduler.h"
#include "src/tasks/HangarTask/HangarTask.h"
#include "src/tasks/TempTask/TempTask.h"
#include "src/tasks/BlinkTask/BlinkTask.h"
#include "src/tasks/SerialTask/SerialTask.h"

HangarContext* ctx;
Scheduler* scheduler;

void setup() {
    Serial.begin(9600);

    Led* l1 = new Led(2); 
    Led* l2 = new Led(3); 
    Led* l3 = new Led(4);
    Button* btnReset = new Button(5);
    Sonar* sonar = new Sonar(6, 7);
    Pir* pir = new Pir(8);
    TempSensor* tempSensor = new TempSensor(A0);
    HangarDoor* door = new HangarDoor(9);
    LiquidCrystal_I2C* lcd = new LiquidCrystal_I2C(0x27, 16, 2);

    door->init();
    lcd->init(); 
    lcd->backlight();

    ctx = new HangarContext(l1, l2, l3, btnReset, sonar, pir, tempSensor, door, lcd);
    scheduler = new Scheduler();

    HangarTask* hangar = new HangarTask(ctx); 
    hangar->init(50);
    scheduler->addTask(hangar);

    TempTask* temp = new TempTask(ctx); 
    temp->init(200);
    scheduler->addTask(temp);

    BlinkTask* blink = new BlinkTask(ctx); 
    blink->init(500);
    scheduler->addTask(blink);

    SerialTask* serialTask = new SerialTask(ctx); 
    serialTask->init(50);
    scheduler->addTask(serialTask);
}

void loop() {
    scheduler->schedule();
}