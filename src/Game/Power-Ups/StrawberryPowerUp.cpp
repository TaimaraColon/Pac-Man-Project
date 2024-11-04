#include "StrawberryPowerUp.h"

StrawberryPowerUp::StrawberryPowerUp(int x, int y, int width, int height) : PowerUp(x, y, width, height){
    sprite.load("images\\strawberryPowerUp.png"); 
}; 

StrawberryPowerUp::~StrawberryPowerUp(){
    
}

void StrawberryPowerUp::activate(){
    setActivatedState(true);
    setTimer(300);
}
