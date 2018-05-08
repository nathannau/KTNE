#ifndef KTNE_Display_h
#define KTNE_Display_h

namespace Ktne
{
    class Display
    {
        public:
            enum Mode 
            {
                Menu = 0,
                Timer = 1
            };

            Display() {}
            void Setup() {}
            void ExecuteOnce() {}

            void Start() {}

            void SetMode(Mode mode) {}

            void SetMenuItems(const char* items[]);
            void SetCurrentItem(int item);
            int GetCurrentItem();
            void MoveToNextItem();
            void MoveToPrevItem();

            void SetTime(int nbSecond) {}
            void SetNbError(int count) {}
            void SetNbErrorMax(int count) {}
        protected:


        private:
            const char** _items;
            int _currentItem;
    };
};
// the #include statment and code go here...

#endif