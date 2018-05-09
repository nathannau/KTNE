#ifndef KTNE_Server_h
#define KTNE_Server_h

//#include <Wire.h>
//#include <Arduino.h>
 #include <stdlib.h>
#include <stdint.h>
//#include <cstddef>
#include "ServerModule.h"
#include "ServerI2C.h"
#include "Display.h"
#include "Lang.h"
#include "Params.h"

namespace Ktne
{
    class Server
    {
        public:
            enum State
            {
                NotInit = 0,
                Init = 1,
                Playing = 2,
                InPause = 3,
                Config = 4,
            };


            Server(Display *display, ServerI2C *serverI2C);
            void Setup();
            void ExecuteOnce();

            void Start();

            void ActionNext();
            void ActionPrev();
            void ActionValid();

            void SetState(State state);

        protected:

            static const char* Menu_Config;
            static const char* Menu_GameNumber;
            static const char* Menu_Init;
            static const char* Menu_MaxError;
            static const char* Menu_Pause;
            static const char* Menu_Restart;
            static const char* Menu_Resume;
            static const char* Menu_Return;
            static const char* Menu_Start;
            static const char* Menu_Stop;
            static const char* Menu_TimeByModule;

            void OnMenu_Config();
            void OnMenu_GameNumber();
            void OnMenu_Init();
            void OnMenu_MaxError();
            void OnMenu_Pause();
            void OnMenu_Restart();
            void OnMenu_Resume();
            void OnMenu_Return();
            void OnMenu_Start();
            void OnMenu_Stop();
            void OnMenu_TimeByModule();

            void (Server::*menuActions[])();

            uint8_t GetModulesCount();

        private:
            bool _started;
            Display *_display;
            ServerI2C *_serverI2C;
            State _state;
            ServerModule* _modules;
            int _time;
            int _timeByModule;

            static const char* _menuItems_NotInit[];
            static const char* _menuItems_Init[];
            static const char* _menuItems_InPause[];
            static const char* _menuItems_Config[];

            typedef void (Server::* cbMenuAction)();
            cbMenuAction _menuActions_NotInit[3] = { &Server::OnMenu_Init, &Server::OnMenu_Config, 0 };
            cbMenuAction _menuActions_Init[3] = { &Server::OnMenu_Start, &Server::OnMenu_Config, 0 };
            cbMenuAction _menuActions_InPause[4] = { &Server::OnMenu_Resume, &Server::OnMenu_Restart, &Server::OnMenu_Stop, 0 };
            cbMenuAction _menuActions_Config[5] = { &Server::OnMenu_GameNumber, &Server::OnMenu_MaxError, &Server::OnMenu_TimeByModule, &Server::OnMenu_Return, 0 };
            cbMenuAction* _currentMenuActions;
            
            //void (Server::*)()* _currentMenuActions;
    };
};
// the #include statment and code go here...

#endif