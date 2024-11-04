#pragma once

#include "Animation.h"
#include "EntityManager.h"
#include "Ghost.h"
#include "Dot.h"
#include "BigDot.h"
#include "PowerUp.h"

enum MOVING {
	MUP,
	MDOWN,
	MLEFT,
	MRIGHT,
};

class PowerUp;
class Player: public Entity {

    private:
        int spawnX, spawnY;
        unsigned int health=3;
        int score=0;
        bool canMoveUp, canMoveDown, canMoveRight, canMoveLeft;
        int speed = 4;
        bool walking = false;
        MOVING moving;
        FACING facing = DOWN;
        ofImage up, down, left, right;
        Animation *walkUp;
        Animation *walkDown;
        Animation *walkLeft;
        Animation *walkRight;
        ofImage up2, down2, left2, right2;
        Animation *walkUp2;
        Animation *walkDown2;
        Animation *walkLeft2;
        Animation *walkRight2;
        EntityManager* em;
        
        Dot* dotFinder();       // Private method that lets us find a random dot to switch pac-man with in the cherry power-up
        void drawPowerUps();    
        void drawPowerUpTimer(); 

        PowerUp* currentPowerUp;

        int strawberryTimer = 0;
        bool strawBerryActivated =  false;

        int appleTimer= 0; 
        bool appleActivated = false; 

        
        ofImage sprite2;
        volatile bool isMario =false;

    public:
        Player(int, int, int , int, EntityManager*);
        ~Player();
        int getHealth();
        int getScore();
        FACING getFacing();
        void setHealth(int);
        void setScore(int);
        void setFacing(FACING facing);
        void tick();
        void render();
        void keyPressed(int);
        void keyReleased(int);
        void damage(Entity* damageSource);
        void mousePressed(int, int, int);
        void reset();
        void checkCollisions();
        void die();

        vector<PowerUp*> newPowerUps;

        PowerUp* getPowerUp(){return newPowerUps[0];}
        void activatePowerUp();


        EntityManager* getEntityManager(){return em; } 
        void setX(int temp) {this->x = temp; }
        void setY(int y){this->y = y; }

        ofImage getSprite(){ return sprite; }
    
        
        bool getisMario(){return isMario;}
        void setisMario(volatile bool isMario);
        void createPacman();
        void createMario();
};