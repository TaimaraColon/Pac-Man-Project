#pragma once
#include "PowerUp.h"
#include "Player.h"

class ApplePowerUp:public PowerUp{
    public:
        ApplePowerUp(int x, int y, int width, int height);
        ~ApplePowerUp();        
        string name(){
            return "apple"; 
        }

        void activate();        //activate method inherited from PowerUp class


};