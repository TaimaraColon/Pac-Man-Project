#include "Player.h"
#include "EntityManager.h"
#include "Dot.h"
#include "BigDot.h"
#include "Ghost.h"




Player::Player(int x, int y, int width, int height, EntityManager* em) : Entity(x, y, width, height){
    
    spawnX = x;
    spawnY = y;
    this->em = em;
    moving = MLEFT;
    //creates de characters
    createMario();      
    createPacman();
}
void Player::createPacman(){                    //Creates pacman !!
        sprite.load("images/pacman.png");
        down.cropFrom(sprite, 0, 48, 16, 16);
        up.cropFrom(sprite, 0, 32, 16, 16);
        left.cropFrom(sprite, 0, 16, 16, 16);
        right.cropFrom(sprite, 0, 0, 16, 16);
        
        vector<ofImage> downAnimframes;
        vector<ofImage> upAnimframes;
        vector<ofImage> leftAnimframes;
        vector<ofImage> rightAnimframes;
        ofImage temp;
        for(int i=0; i<3; i++){
            temp.cropFrom(sprite, i*16, 48, 16, 16);
            downAnimframes.push_back(temp);
        }
        for(int i=0; i<3; i++){
            temp.cropFrom(sprite, i*16, 32, 16, 16);
            upAnimframes.push_back(temp);
        }
        for(int i=0; i<3; i++){
            temp.cropFrom(sprite, i*16, 16, 16, 16);
            leftAnimframes.push_back(temp);
        }
        for(int i=0; i<3; i++){
            temp.cropFrom(sprite, i*16, 0, 16, 16);
            rightAnimframes.push_back(temp);
        }
        walkDown = new Animation(1,downAnimframes);
        walkUp = new Animation(1,upAnimframes);
        walkLeft = new Animation(1,leftAnimframes);
        walkRight = new Animation(1,rightAnimframes);
}

void Player::createMario(){                    //Creates mario !!
        sprite2.load("images/marioDir.png");
        down2.cropFrom(sprite, 0, 168, 56, 66);
        up2.cropFrom(sprite, 0, 132, 56, 66);
        left2.cropFrom(sprite, 0, 66, 56, 66);
        right2.cropFrom(sprite, 0, 0, 56, 66);
        
        vector<ofImage> downAnimframes2;
        vector<ofImage> upAnimframes2;
        vector<ofImage> leftAnimframes2;
        vector<ofImage> rightAnimframes2;
        ofImage temp2;
        for(int i=0; i<3; i++){
            temp2.cropFrom(sprite2, i*56, 0, 56, 66);
            downAnimframes2.push_back(temp2);
        }
        for(int i=0; i<3; i++){
            temp2.cropFrom(sprite2, i*56, 0, 56, 66);
            upAnimframes2.push_back(temp2);
        }
        for(int i=0; i<3; i++){
            temp2.cropFrom(sprite2, i*56, 66, 56, 66);
            leftAnimframes2.push_back(temp2);
        }
        for(int i=0; i<3; i++){
            temp2.cropFrom(sprite2, i*56, 0, 56, 66);
            rightAnimframes2.push_back(temp2);
        }
        walkDown2 = new Animation(2,downAnimframes2);
        walkUp2 = new Animation(2,upAnimframes2);
        walkLeft2 = new Animation(2,leftAnimframes2);
        walkRight2 = new Animation(2,rightAnimframes2);
}

void Player::setisMario(volatile bool isMario){
    this->isMario = isMario;        //sets which player was chosen
}



Dot* Player::dotFinder(){
    Dot* tempDot;    

    vector<Entity*> temp = em->entities;
    random_shuffle(temp.begin(), temp.end());
    
    for(Entity* entity : temp){
        tempDot = dynamic_cast<Dot*>(entity);
        if (tempDot) {
            return tempDot; // returns the dot
        }
    }
    return nullptr; // return null if it never found any dot (worst case)
 
}
void Player::tick(){

    checkCollisions();
    

    if (moving == MUP && canMoveUp) 
        facing = UP;
    else if (moving == MDOWN && canMoveDown) 
        facing = DOWN;
    else if (moving == MLEFT && canMoveLeft) 
        facing = LEFT;
    else if (moving == MRIGHT && canMoveRight)
        facing = RIGHT;

    if(facing == UP && canMoveUp){
        y-= speed;
        if(isMario){
            walkUp2->tick();
        }else{
            walkUp->tick();
        }
        
    }else if(facing == DOWN && canMoveDown){
        y+=speed;
        if(isMario){
            walkDown2->tick();
        }else{
            walkDown->tick();
        }
        
    }else if(facing == LEFT && canMoveLeft){
        x-=speed;
        if(isMario){
            walkLeft2->tick();
        }else{
            walkLeft->tick();
        }
        
    }else if(facing == RIGHT && canMoveRight){
        x+=speed;
        if(isMario){
           walkRight2->tick();
        }else{
            walkRight->tick();
        }

    if(strawberryTimer > 0){        //makes the timer for the strawberry power up "tick"
        strawberryTimer--;

    }
    if(strawberryTimer == 0){       //once the timer is finished, the strawberry power up is gonna be deactivated
        strawBerryActivated = false;
    }

    if(appleTimer > 0 ){            //makes the timer for the apple power up "tick"
        appleTimer--; 
    }
    if(appleTimer == 0){            //once the timer is finished, the apple power up is gonna be deactivated
        appleActivated = false; 
        }
    
    if(appleActivated){             //if the apple power up is activated, the player's speed will be increased to 8, otherwise, it's 4. 
        this->speed = 8;}
    else{
            this->speed = 4; 
        }; 
    

}
}
void Player::activatePowerUp(){
    PowerUp* currentPowerUp = getPowerUp();
    
    
    //for cherry
    currentPowerUp->handOverDot(dotFinder());
    currentPowerUp->setPlayer(this);
    

    //add additional stuff you need before activating other powerups
    
    currentPowerUp->activate();

    if(currentPowerUp->getActivatedState()) {   //A strawberry was activated
        strawberryTimer = currentPowerUp->getTimer();
        strawBerryActivated = true;

    }

    if(currentPowerUp->getAppleActivated()) {
        appleTimer = currentPowerUp->getAppleTimer(); 
        appleActivated= true; 
    }

    

}



void Player::drawPowerUps(){        //LOGIC OF DRAWING POWERUPS AND THE RECTANGLE (DO NOT TOUCH)
    ofNoFill();
    ofDrawRectangle(25, 40, 150, 60);
    ofFill();
    ofDrawLine(25 + 50, 40, 25 + 50, 100);
    ofDrawLine(25 + 100, 40, 25 + 100, 100);
    ofDrawBitmapString("Next", 30, 120);


    if(newPowerUps.size() >0){
        for(int i = 0; i < newPowerUps.size(); i++){
            PowerUp* p = newPowerUps[i];
            ofPoint pos = ofPoint(35 + (i*50), 56);
            ofSetColor(ofColor::white);
            p->getSprite().draw(pos, 30, 30);
        }
    }

}
void Player::drawPowerUpTimer(){
    if (appleActivated) {
        ofDrawBitmapString("Apple Activated:", 25, 195); 
        ofDrawRectangle(25, 200, appleTimer/5, 10);
    }
    if (strawBerryActivated) {
        ofDrawBitmapString("Strawberry Activated:", 25, 295); 
        ofDrawRectangle(25, 300, strawberryTimer/5, 10); 
    }
}



void Player::render(){

   ofSetColor(ofColor::blue);
    drawPowerUps();
    drawPowerUpTimer(); 
    int transparency = 100;

    if(strawBerryActivated){
        ofSetColor(256,256,256, transparency);
    }
    else{
        ofSetColor(256, 256, 256);
    }


    if(facing == UP){
        if(isMario){
        walkUp2->getCurrentFrame().draw(x, y, width, height);
    }else{
        walkUp->getCurrentFrame().draw(x, y, width, height);
    }
    }
    

        
    else if(facing == DOWN){
        if(isMario){
        walkDown2->getCurrentFrame().draw(x, y, width, height);
    }else{
        walkDown->getCurrentFrame().draw(x, y, width, height);
    }
    }
    
        
    else if(facing == LEFT){
        if(isMario){
            walkLeft2->getCurrentFrame().draw(x, y, width, height);
        }else{
            walkLeft->getCurrentFrame().draw(x, y, width, height);
        }
    }
         
        
    else if(facing == RIGHT){
        if(isMario){
            walkRight2->getCurrentFrame().draw(x, y, width, height);
        }else{
            walkRight->getCurrentFrame().draw(x, y, width, height);
        }
    }
        
        
    
    ofSetColor(256, 0, 0);
    ofDrawBitmapString("Health: ", ofGetWidth()/2 + 100, 50);

    for(unsigned int i=0; i<health; i++){
        ofDrawCircle(ofGetWidth()/2 + 25*i +200, 50, 10);
    }
    ofDrawBitmapString("Score:"  + to_string(score), ofGetWidth()/2-200, 50);
    ofDrawBitmapString("StrawberryTimer: " + to_string(strawberryTimer), ofGetWidth()/2-200, 70);
   
}



void Player::keyPressed(int key){
    switch(key){
        case 'w':
            moving = MUP;
            break;
        case 's':
            moving = MDOWN;
            break;
        case 'a':
            moving = MLEFT;;
            break;
        case 'd':
            moving = MRIGHT;;
            break;
        case 'n':
            die();
            break;
        case 'm':
            if(health <3){    //  limits pac-man to have no more than 3 lives
                health++;
            }
            break;

        case ' ': //Power-Up activation system:
            if(newPowerUps.size() > 0){    //if the PowerUp vector is not empty, it will activate the first powerup in the list
                activatePowerUp();  
                this->newPowerUps.erase(newPowerUps.begin()); //after the activated, the powerup will be erased from the vector
            }
    }
}




void Player::keyReleased(int key){
    if(key == 'w' || key =='s' || key == 'a' || key == 'd'){
        walking = false;
    }
}

void Player::mousePressed(int x, int y, int button){

}

int Player::getHealth(){ return health; }
int Player::getScore(){ return score; }
FACING Player::getFacing(){ return facing; }
void Player::setHealth(int h){ health = h; }
void Player::setFacing(FACING facing){ this->facing = facing; }
void Player::setScore(int h){ score = h; }

void Player::checkCollisions(){
    canMoveUp = true;
    canMoveDown = true;
    canMoveLeft = true;
    canMoveRight = true;

    for(BoundBlock* boundBlock: em->boundBlocks){
        if(this->getBounds(x, y-speed).intersects(boundBlock->getBounds()))
            canMoveUp = false;
        if(this->getBounds(x, y+speed).intersects(boundBlock->getBounds()))
            canMoveDown = false;
        if(this->getBounds(x-speed, y).intersects(boundBlock->getBounds()))
            canMoveLeft = false;
        if(this->getBounds(x+speed, y).intersects(boundBlock->getBounds()))
            canMoveRight = false;
    }
    
    for(int i = 0; i < em->entities.size(); i++){
        Entity* entity = em->entities[i];
         if(collides(entity)){
            if(dynamic_cast<Dot*>(entity) || dynamic_cast<BigDot*>(entity)){
                entity->remove = true;
                score += 10;
            }

            if(dynamic_cast<BigDot*>(entity)){
                score +=20;
                em->setKillable(true);
            }
            
            if(dynamic_cast<PowerUp*>(entity)){
                if(newPowerUps.size() < 3){
                    PowerUp* tempPointer = dynamic_cast<PowerUp*>(entity);
                    newPowerUps.push_back(dynamic_cast<PowerUp*>(tempPointer)); 
                    entity->remove = true;
                }
            }
        }
    }
    

    for(Entity* entity:em->ghosts){
        if(collides(entity)){
            Ghost* ghost = dynamic_cast<Ghost*>(entity);
            if(ghost->getKillable()){   //if you can kill the ghost
                ghost->remove = true;
            }
            if(!ghost->getKillable() && !strawBerryActivated){    
                //si el Strawberry Power Up no esta activated y el ghost no es killable, the player dies
                die();
        }
    }  
}
}
void Player::die(){
    health--;
    x = spawnX;
    y = spawnY;

}


Player::~Player(){
    delete walkUp;
    delete walkDown;
    delete walkLeft;
    delete walkRight;
     delete walkUp2;
    delete walkDown2;
    delete walkLeft2;
    delete walkRight2;
}
