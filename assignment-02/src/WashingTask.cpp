#include "../lib/WashingTask.hpp"
#include "../lib/config.h"

extern bool startWashing;
extern bool washingFinished;

WashingTask::WashingTask() {

}

void WashingTask::init() {
    Task::init(1);
    Serial.println("Init washing");
    this->button = new Button(BUTTON_PIN);
    this->lcd = new Lcd(0x27, LCD_COLS, LCD_ROWS);
    this->l2 = new BlinkingLed(L2);
    this->tmp = new Tmp(TMP_PIN);
    MsgService.init();
}

void WashingTask::tick() {
    Serial.println("Sono il tick di washing");
    while (!this->button->isPressed()) {}
    unsigned long start = millis();
    unsigned long startTemp;
    bool flag = false;
    Msg *msg;
    while (millis() - start < N3) {
        this->l2->blink(250);
        this->lcd->showMessage(String((N3 - (millis() - start)) / 1000));
        //Serial.println("Temperatura = " + String(tmp->detect()));
        startTemp = millis();
        if (millis() - start > 3000) {
            do {
                if (millis() - startTemp > N4) {
                    do {
                        MsgService.sendMsg("Maintenance required");
                        if (MsgService.isMsgAvailable()) {
                            this->lcd->showMessage("aaaaa");
                            msg = MsgService.receiveMsg();
                            String s = msg->getContent();
                            if (s == "fix") {
                                flag = true;
                            }
                        }
                    } while (!flag);
                    this->lcd->showMessage(msg->getContent());
                    start = millis();
                    MsgService.sendMsg("");
                    break;
                }
            } while (this->tmp->detect() > MAXTEMP);
        }
    }
    this->lcd->showMessage("Washing complete you can leave!");
    startWashing = false;
    washingFinished = true;
    Serial.println("Fine tick washing");
    this->setActive(false);
    delete msg;
}

bool WashingTask::isActive() {
    if (startWashing) {
        this->setActive(true);
        return true;
    }
    return false;
}