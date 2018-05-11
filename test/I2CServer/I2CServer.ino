

#define DEBUG

#include <ServerI2C.h>

#define PIN_BTN 7

#define PIN_SS_RIGHT 8
#define PIN_SS_BOTTOM 9

Ktne::ServerI2C serverI2C(PIN_SS_RIGHT, PIN_SS_BOTTOM); 


void setup() {
    Serial.begin(9600);

    pinMode(PIN_BTN,INPUT_PULLUP);

    serverI2C.Setup();
}

bool lastBtnState = false;

void loop() 
{
    if ((digitalRead(PIN_BTN)==HIGH) != lastBtnState)
    {
        lastBtnState ^= 1;
        if (lastBtnState)
        { 
            Serial.write("Start Init !");
            serverI2C.Init();
        }
    }
}