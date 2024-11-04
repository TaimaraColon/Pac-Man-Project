#pragma once
#include "PowerUp.h"
#include "Player.h"

using namespace std; 

class StrawberryPowerUp: public PowerUp{
    public: 
    StrawberryPowerUp(int x, int y, int width, int height); 
    ~StrawberryPowerUp(); 
    
    string name(){
        return "strawberry";
    }

    void activate();    //activate method inherited from parent class PowerUp
    
};