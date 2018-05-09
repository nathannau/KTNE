/*

 */

#include <Lang-fr.h>
#include <ServerKtne.h>
#include <Display1602.h>

#define PIN_BTN_UP 5
#define PIN_BTN_DOWN 6
#define PIN_BTN_RIGHT 7
#define PIN_SS_RIGHT 8
#define PIN_SS_BOTTOM 9





Ktne::Display1602 display;
Ktne::ServerI2C serverI2C(PIN_SS_RIGHT, PIN_SS_BOTTOM); 
Ktne::Server server(&display, &serverI2C);
//SoftwareSerial mySerial(10, 11); // RX, TX

bool lastBtnUpState = false;
bool lastBtnDownState = false;
bool lastBtnRightState = false;

void setup() {
    // Open serial communications and wait for port to open:
    Serial.begin(9600);
    server.Setup();


    pinMode(PIN_BTN_UP,INPUT_PULLUP);
    pinMode(PIN_BTN_DOWN,INPUT_PULLUP);
    pinMode(PIN_BTN_RIGHT,INPUT_PULLUP);

    // mySerial.begin(9600);
    // mySerial.println("Hello, world?");

    server.Start();
}

void checkBtn(uint8_t pin, bool* registre, void (*actionHigh)(), void (*actionLow)()) 
{
    if ((digitalRead(pin)==HIGH) != *registre)
    {
        *registre ^= 1;
        if (*registre) 
        { if (actionHigh!=NULL) actionHigh(); }
        else 
        { if (actionLow!=NULL) actionLow(); }
    }
}
inline void onBtnUpHigh() { server.ActionPrev(); }
//inline void onBtnUpLow() { }
inline void onBtnDownHigh() { server.ActionNext(); }
//inline void onBtnDownLow() { }
inline void onBtnRightHigh() { server.ActionValid(); }
//inline void onBtnRightLow() { }

void loop() 
{
    checkBtn(PIN_BTN_UP, &lastBtnUpState, &onBtnUpHigh, NULL);
    checkBtn(PIN_BTN_DOWN, &lastBtnDownState, &onBtnDownHigh, NULL);
    checkBtn(PIN_BTN_RIGHT, &lastBtnRightState, &onBtnRightHigh, NULL);

    server.ExecuteOnce();
    // if (mySerial.available()) {
    //     Serial.write(mySerial.read());
    // }
    // if (Serial.available()) {
    //     mySerial.write(Serial.read());
    // }
}

