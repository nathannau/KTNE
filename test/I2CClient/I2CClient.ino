#define DEBUG

#include <ClientI2C.h>

#define PIN_TRIGGER 7
#define PIN_SS_RIGHT 8
#define PIN_SS_BOTTOM 9

Ktne::ClientI2C clientI2C(PIN_TRIGGER, PIN_SS_RIGHT, PIN_SS_BOTTOM); 


void setup() {
    Serial.begin(9600);

    clientI2C.Setup();
}


void loop() 
{
    clientI2C.ExecuteOnce();
}