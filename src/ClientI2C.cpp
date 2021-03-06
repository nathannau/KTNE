#include <Arduino.h>
#include <Wire.h>
#include "clientI2C.h"
#include "Params.h"
#include "I2CMessage.h"

// #include <stdlib.h>
// #include <stdint.h>

namespace Ktne
{
    ClientI2C::ClientI2C(uint8_t pinTrigger, uint8_t pinSsRight, uint8_t pinSsBottom) : 
        _pinTrigger(pinTrigger), 
        _pinSsRight(pinSsRight), 
        _pinSsBottom(pinSsBottom) { }

    void ClientI2C::Setup(void(fnToReceive)(int)) 
    {
        pinMode(this->_pinTrigger, INPUT_PULLUP);
        pinMode(this->_pinSsRight, OUTPUT);
        pinMode(this->_pinSsBottom, OUTPUT);
        digitalWrite(this->_pinSsRight, LOW);
        digitalWrite(this->_pinSsBottom, LOW);
        Wire.begin(0x0);
        TWAR = 1;

        Wire.onReceive(fnToReceive);
    }

    void ClientI2C::ExecuteOnce()
    {
        if (!this->_isActif && digitalRead(this->_pinTrigger)==HIGH)
            this->_isActif = true;

    }

    void ClientI2C::onReceive(int numBytes)
    {
        if (!this->_isActif || numBytes<1 || Wire.available()<1) 
        {
            while (Wire.available()>0) Wire.read();
            return;
        } 
        switch(Wire.read())
        {
            case ID_ACTIVE_SS:
            {
                bool isHorizontal = Wire.read()==1;
                if (isHorizontal)
                    digitalWrite(this->_pinSsRight, HIGH);
                else
                    digitalWrite(this->_pinSsBottom, HIGH);
                this->onActiveSs(isHorizontal);
            }
            break;
            case ID_SET_INFO:
            {
                this->_x = Wire.read();
                this->_y = Wire.read();
                this->_id = Wire.read();
                Wire.begin(this->_id);
                TWAR = (this->_id << 1) | 1;
                Wire.write(1);
                this->onSetInfo(this->_x, this->_y, this->_id); 
            }
            break;
        }
    }

    bool ClientI2C::isActif() 
    {
        return this->_isActif;
    }

    bool ClientI2C::isInit() 
    {
        return this->_isInit;
    }

    uint8_t ClientI2C::getId()
    {
        return this->_id;
    }

};
