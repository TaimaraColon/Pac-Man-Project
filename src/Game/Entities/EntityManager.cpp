#include "EntityManager.h"
#include "Ghost.h"
#include "Power-Ups/PowerUp.h"

void EntityManager::tick(){
    if(killable){
        killableCounter--;
        if (killableCounter == 0){
            killable = false;
            for(Entity* entity : ghosts){
                Ghost* ghost = dynamic_cast<Ghost*>(entity); 
                ghost->setKillable(false);
            }
        }
    }
    
    for(unsigned int i=0;i<entities.size();i++){ //Updates the entities

        if(!entities[i]->remove){
            entities[i]->tick();

        }else{  //Removes the entity from the game
            Entity* entityPointer = entities[i];
            entities.erase(entities.begin() + i--);
            if(!dynamic_cast<PowerUp*>(entityPointer)){
                delete entityPointer;
            }
        }
    }

    for(BoundBlock* BoundBlock: boundBlocks){ //Updates the boundary blocks
        BoundBlock->tick();
    }
    
    for(unsigned int i=0;i<ghosts.size();i++){ //Updates the ghosts
        if(!ghosts[i]->remove){
            ghosts[i]->tick();

        }else{
            Ghost* ghostPtr = dynamic_cast<Ghost*>(ghosts[i]);
            ghosts.erase(ghosts.begin() + i--);
            delete ghostPtr;
        }
    }

}

void EntityManager::render(){
    for(Entity* entity: entities){
        entity->render();
    }
    for(BoundBlock* BoundBlock: boundBlocks){
        BoundBlock->render();
    }
    for(Entity* ghost: ghosts){
        ghost->render();
    }

}

void EntityManager::setKillable(bool k){
    killable = true;
    killableCounter=10*ofGetFrameRate();
    for(Entity* entity:ghosts){
        Ghost* ghost = dynamic_cast<Ghost*>(entity); 
        ghost->setKillable(true);
    }
}

EntityManager::~EntityManager(){
    for(Entity* e: boundBlocks) delete dynamic_cast<BoundBlock*>(e);

    for(Entity* e: ghosts) delete dynamic_cast<Ghost*>(e);

    for(Entity* e: entities) delete e;

    boundBlocks.clear();
    ghosts.clear();
    entities.clear();
}

