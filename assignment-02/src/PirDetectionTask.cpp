#include "../lib/PirDetectionTask.hpp"

extern bool startDetecting;
extern bool carDetected;
bool sleep_ok = false;
PirDetectionTask::PirDetectionTask(int pin)
{
    this->pin = pin;
}

void PirDetectionTask::init(int period)
{
    attachInterrupt(
        0, [] {},
        RISING);
    this->pir = new Pir(this->pin);
    this->l2 = new Led(L2);
    this->l2->switchOn();
    for (int i = 0; i < PIR_CALIBRATION_TIME; i++)
    {
        delay(1000);
    }
    this->l2->switchOff();
    Task::init(period);
}

void PirDetectionTask::wake()
{
    if (sleep_ok)
    {
        sleep_disable();
        Serial.println("sleepoff");
        sleep_ok = false;
    }
}

void PirDetectionTask::tick()
{
    Serial.println("looking for some cars");
    if (this->pir->detect())
    {
        carDetected = true;
        this->setActive(false);
    }
    else
    {
        Serial.println("sleepon");
        delay(250);
        sleep_ok = true;
        set_sleep_mode(SLEEP_MODE_PWR_DOWN);
        sleep_enable();
        sleep_mode();
        delay(500);
        wake();
    }
    startDetecting = false;
}

bool PirDetectionTask::isActive()
{
    if (startDetecting)
    {
        this->setActive(true);
        return true;
    }
    return false;
}
