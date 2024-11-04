#include "ApplePowerUp.h"

ApplePowerUp::ApplePowerUp(int x, int y, int width, int height) : PowerUp(x, y, width, height){
    sprite.load("images\\applePowerUp.png");
}
ApplePowerUp::~ApplePowerUp(){
    
}
void ApplePowerUp::activate(){
    setAppleActivated(true); 
    setAppleTimer(300); 
}