#include <Arduino.h>
#include <Wire.h>
#include "ServerI2C.h"
#include "Params.h"
#include "I2CMessage.h"

namespace Ktne 
{
    ServerI2C::ServerI2C(uint8_t pinSsRight, uint8_t pinSsBottom) 
    {
        this->_pinSsRight = pinSsRight;
        this->_pinSsBottom = pinSsBottom;
    }
    void ServerI2C::Setup() 
    {
        pinMode(this->_pinSsRight, OUTPUT);
        pinMode(this->_pinSsBottom, OUTPUT);
        digitalWrite(this->_pinSsRight, LOW);
        digitalWrite(this->_pinSsBottom, LOW);
        Wire.begin();

    }
    ServerModule* ServerI2C::Init() 
    {
        ServerModule* ret = NULL;
        ServerModule* cur = NULL;
        uint8_t id = 0x40;

        ServerModule* lineParent = NULL;
        for(uint8_t y=0; y<MAX_VERTICAL_COUNT_MODULE; y++)
        {
            ServerModule* parent = lineParent;
            lineParent = NULL;
            for(uint8_t x=0; x<MAX_HORIZONTAL_COUNT_MODULE; x++)
            {
                if (x + y == 0) continue; // Pas d'init pour le master

                // On test le prochain module. Et on lui assigne un ID
                ServerModule* next = this->CheckModule(x, y, id, parent);
#ifdef DEBUG
                Serial.write("x=");
                Serial.write(x);
                Serial.write("y=");
                Serial.write(y);
                Serial.write("id=");
                Serial.write(id);
                Serial.write("result=");
                Serial.write(next==NULL?"NULL":"Success");
#endif
                if (x==0) lineParent = next; // Enregistre le parent de la prochaine ligne

                if (next != NULL)
                {
                    id++;
                    if (ret == NULL)
                        ret = next;
                    else
                        cur->next = next;

                    cur = next;
                    parent = next;
                }
                else break; // Dernier module de la ligne.
            }
            if (y>1 && lineParent==NULL) break;
        }
        return ret; 
    }

    ServerModule* ServerI2C::CheckModule(uint8_t x, uint8_t y, uint8_t id, ServerModule* parent)
    {
        // Activation du SS
        if (parent==NULL)
        {
            if (x!=0)
                digitalWrite(this->_pinSsRight, HIGH);
            else
                digitalWrite(this->_pinSsBottom, HIGH);
        }
        else
            this->SendMessageActiveSs(parent, x!=0);

        return (this->SendMessageSetId(id)) ?
            new ServerModule(x, y, id) :
            NULL;
    }
    
    
    void ServerI2C::SendMessageActiveSs(ServerModule* dest, bool horizontal) 
    {
        Wire.beginTransmission(dest->id);
        Wire.write(ID_ACTIVE_SS);
        Wire.write(horizontal?1:0);
        Wire.endTransmission();
    }
    bool ServerI2C::SendMessageSetId(uint8_t id) 
    {
        Wire.beginTransmission(0);
        Wire.write(ID_SET_ID);
        Wire.write(id);
        Wire.endTransmission(false);
        Wire.requestFrom(id, (uint8_t)1);
        if (1 >= Wire.available())
            return Wire.read()==1;
        return false;
    }


};