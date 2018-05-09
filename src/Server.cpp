

//#include <Arduino.h>
#include "Server.h"

namespace Ktne 
{
    const char* Server::Menu_Config = T_CONFIG;
    const char* Server::Menu_GameNumber = T_GAME_NUMBER;
    const char* Server::Menu_Init = T_INIT;
    const char* Server::Menu_MaxError = T_MAX_ERROR;
    const char* Server::Menu_Pause = T_PAUSE;
    const char* Server::Menu_Restart = T_RESTART;
    const char* Server::Menu_Resume = T_RESUME;
    const char* Server::Menu_Return = T_RETURN;
    const char* Server::Menu_Start = T_START;
    const char* Server::Menu_Stop = T_STOP;
    const char* Server::Menu_TimeByModule = T_TIME_BY_MODULE;
    
    const char* Server::_menuItems_NotInit[] = { Server::Menu_Init, Server::Menu_Config, 0 };
    const char* Server::_menuItems_Init[] = { Server::Menu_Start, Server::Menu_Config, 0 };
    const char* Server::_menuItems_InPause[] = { Server::Menu_Resume, Server::Menu_Restart, Server::Menu_Return, 0 };
    const char* Server::_menuItems_Config[] = { Server::Menu_GameNumber, Server::Menu_MaxError, Server::Menu_TimeByModule, Server::Menu_Return, 0 };

    Server::Server(Display *display, ServerI2C *serverI2C) 
    {
        this->_display = display;
        this->_serverI2C = serverI2C;
        this->_state = State::NotInit;
        this->_timeByModule = DEFAULT_TIME_BY_MODULE;
    }

    void Server::Setup() {
        this->_display->Setup();
        this->_serverI2C->Setup();
    }

    void Server::Start() {
        this->SetState(State::NotInit);
    }

    void Server::ExecuteOnce() {



        this->_display->ExecuteOnce();
    }

    void Server::SetState(State state)
    {
        this->_state = state;
        switch(state)
        {
            case State::NotInit:
            {
                this->_display->SetMode(Display::Mode::Menu);
                this->_currentMenuActions = this->_menuActions_NotInit;
                this->_display->SetMenuItems(Server::_menuItems_NotInit);
                this->_display->SetCurrentItem(0);
                break;
            }
            case State::Init:
            {
                this->_display->SetMode(Display::Mode::Menu);
                this->_currentMenuActions = this->_menuActions_Init;
                this->_display->SetMenuItems(Server::_menuItems_Init);
                this->_display->SetCurrentItem(0);
                break;
            }
            case State::Config:
            {
                this->_display->SetMode(Display::Mode::Menu);
                this->_currentMenuActions = this->_menuActions_Config;
                this->_display->SetMenuItems(Server::_menuItems_Config);
                this->_display->SetCurrentItem(0);
                break;
            }
            case State::Playing:
            {
                this->_display->SetMode(Display::Mode::Timer);
                this->_time = this->_timeByModule * this->GetModulesCount();
                this->_display->SetTime(this->_time);
                break;
            }
            case State::InPause:
            {
                this->_display->SetMode(Display::Mode::Menu);
                this->_currentMenuActions = this->_menuActions_InPause;
                this->_display->SetMenuItems(Server::_menuItems_InPause);
                this->_display->SetCurrentItem(0);
                break;
            }
        }
    }

    uint8_t Server::GetModulesCount()
    {
        uint8_t ret = 0;
        for(ServerModule* module = this->_modules; module != NULL; module = module->next, ret++) ;
        return ret;
        
    }

    void Server::ActionNext()
    {
        switch (this->_state)
        {
            case State::NotInit:
            case State::Init:
            case State::Config:
            case State::InPause:
                this->_display->MoveToNextItem();
            break;
            case State::Playing:
                this->OnMenu_Pause();
            break;
        }
    }
    void Server::ActionPrev()
    {
        switch (this->_state)
        {
            case State::NotInit:
            case State::Init:
            case State::Config:
            case State::InPause:
                this->_display->MoveToPrevItem();
            break;
            case State::Playing:
                this->OnMenu_Pause();
            break;
        }
    }
    void Server::ActionValid()
    {
        switch (this->_state)
        {
            case State::NotInit:
            case State::Init:
            case State::Config:
            case State::InPause:
            {
                cbMenuAction action = this->_currentMenuActions[this->_display->GetCurrentItem()];
                (this->*action)();
            }
            break;
            case State::Playing:
                this->OnMenu_Pause();
            break;
        }
    }

    void Server::OnMenu_Config()
    {
        this->SetState(State::Config);
    }
    void Server::OnMenu_GameNumber()
    {
        
    }
    void Server::OnMenu_Init()
    {
        



    }


    void Server::OnMenu_MaxError()
    {
        
    }
    void Server::OnMenu_Pause()
    {
        this->SetState(State::InPause);
    }
    void Server::OnMenu_Restart()
    {
        
    }
    void Server::OnMenu_Resume()
    {
        
    }
    void Server::OnMenu_Return()
    {
        this->SetState(State::Init);
    }
    void Server::OnMenu_Start()
    {
        
    }
    void Server::OnMenu_Stop()
    {
        
    }
    void Server::OnMenu_TimeByModule()
    {
        
    }


}

// void Ktne::Server::AddSerialPort(int i, int o) {}

