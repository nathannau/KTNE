#ifndef KTNE_ClientI2C_h
#define KTNE_ClientI2C_h

//#include <Wire.h>
//#include <Arduino.h>
#include <stdlib.h>
#include <stdint.h>
//#include <cstddef>
//#include "ServerModule.h"
// #include "Display.h"
// #include "Lang.h"
// #include "Params.h"

namespace Ktne
{
    class ClientI2C
    {
        public:
            ClientI2C(uint8_t pinTrigger, uint8_t pinSsRight, uint8_t pinSsBottom);
            void Setup(void(fnToReceive)(int));
            void ExecuteOnce();

            bool isActif();

            bool isInit();

            uint8_t getId();

            virtual void onActiveSs(bool horizontal) {}
            virtual bool onSetInfo(uint8_t x, uint8_t y,uint8_t id) {}

            void onReceive(int numBytes);

        protected:

        private:
            uint8_t _pinTrigger;
            uint8_t _pinSsRight;
            uint8_t _pinSsBottom;
            bool _isInit;
            bool _isActif;

            uint8_t _x; 
            uint8_t _y;
            uint8_t _id;
    };
};

#endif