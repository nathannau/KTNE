#ifndef KTNE_ServerModule_h
#define KTNE_ServerModule_h

 #include <stdlib.h>
#include <stdint.h>

namespace Ktne
{
    class ServerModule {
        public:
            ServerModule(uint8_t x, uint8_t y, uint8_t id)
            {
                this->x = x;
                this->y = y;
                this->id = id;
                this->solved = false;
                this->next = NULL;
            }
            bool solved;
            uint8_t x;
            uint8_t y;
            uint8_t id;
            ServerModule* next;
            ~ServerModule() { delete this->next; }
    };
};

#endif