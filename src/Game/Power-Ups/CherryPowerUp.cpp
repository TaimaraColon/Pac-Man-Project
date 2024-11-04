#include "CherryPowerUp.h" 



CherryPowerUp::CherryPowerUp(int x, int y, int width, int height) : PowerUp(x, y, width, height){
    sprite.load("images\\cherryPowerUp.png");
}

CherryPowerUp::~CherryPowerUp(){
}

void CherryPowerUp::activate(){     //moves the player to a random dot in the game
    this->p->setX(this->d->getX()); 
    this->p->setY(this->d->getY());
}


