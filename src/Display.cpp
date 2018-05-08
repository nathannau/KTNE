
#include "Server.h"

namespace Ktne 
{
    void Display::SetMenuItems(const char* items[]) 
    {
        this->_items = items;
    }
    void Display::SetCurrentItem(int item) 
    {
        this->_currentItem = item;
    }
    int Display::GetCurrentItem() 
    { 
        return this->_currentItem; 
    }
    void Display::MoveToNextItem() 
    {
        this->_currentItem++;
        if (!this->_items[this->_currentItem])
            this->_currentItem = 0;
    }
    void Display::MoveToPrevItem() 
    {
        this->_currentItem--;
        if (this->_currentItem<0)
            while (this->_items[this->_currentItem+1]) 
                this->_currentItem++;
    }

}