#pragma once
#include "Entity.h"


class Player; 
class Dot; 


class PowerUp: public Entity{
    protected:
        Player* p;
        Dot* d;      //for cherry  

        bool strawberryActive = false;
        int strawberryTimer = 0;

        bool AppleActive= false; 
        int appleTimer = 0; 

    public:
        PowerUp(int x, int y, int width, int height);
        virtual string name() = 0;
        virtual void activate() = 0;

    // necessary to give all the cherries the player pointer
        void setPlayer(Player* p) { this->p = p; }



    //Auxiliary method for the cherry PowerUp logic    
        void handOverDot(Dot* dot) { this->d = dot; }

    // Auxiliary method for the strawberry powerup logic
        void setActivatedState(bool state) { strawberryActive = state; }
        bool getActivatedState() { return strawberryActive; }

        void setTimer(int time) { strawberryTimer = time; }
        int getTimer() { return strawberryTimer; }

    // Auxiliary method for the apple powerup logic
        void setAppleActivated(bool state) { AppleActive = state;  }
        bool getAppleActivated() { return AppleActive; }

        void setAppleTimer(int time) { appleTimer = time; }
        int getAppleTimer() { return appleTimer; }

};