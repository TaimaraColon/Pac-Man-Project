// #pragma once
#include "PowerUp.h"
#include "Player.h"
#include "Dot.h"
#include "EntityManager.h"

using namespace std; 


class CherryPowerUp: public PowerUp{

    public:
        CherryPowerUp(int x, int y, int width, int height); 
        string name() { return "cherry"; }
        void activate();

        EntityManager* em;

        ~CherryPowerUp(); 

};