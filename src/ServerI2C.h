#ifndef KTNE_ServerI2C_h
#define KTNE_ServerI2C_h

//#include <Wire.h>
//#include <Arduino.h>
#include <stdlib.h>
#include <stdint.h>
//#include <cstddef>
 #include "ServerModule.h"
// #include "Display.h"
// #include "Lang.h"
// #include "Params.h"

namespace Ktne
{
    class ServerI2C
    {
        public:
            ServerI2C(uint8_t pinSsRight, uint8_t pinSsBottom);
            void Setup();
            ServerModule* Init();

            void SendMessageActiveSs(ServerModule* dest, bool horizontal);
            bool SendMessageSetInfo(uint8_t x, uint8_t y,uint8_t id);
            
        protected:
            ServerModule* CheckModule(uint8_t x, uint8_t y, uint8_t id, ServerModule* parent);
        private:
            uint8_t _pinSsRight;
            uint8_t _pinSsBottom;
    };
};

#endif