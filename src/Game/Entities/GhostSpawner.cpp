#include "GhostSpawner.h"
#include "Ghost.h"

GhostSpawner::GhostSpawner(int x, int y, int width, int height, EntityManager* em, ofImage sprite) : Entity(x, y, width, height){
    this->em = em;
    this->sprite = sprite;
    spawnGhost("red");
    spawnGhost("pink");
    spawnGhost("cyan");
    spawnGhost("orange");

}

void GhostSpawner::tick(){
    
    colors.push_back("red");
    colors.push_back("pink");
    colors.push_back("cyan");
    colors.push_back("orange");

    if(em->ghosts.size()<4){
        if(spawnCounter == 0){
            spawnGhost(colors[ofRandom(4)]);
            spawnCounter = 30*5;
            
        }else{
            spawnCounter--;
        }
    }
}
void GhostSpawner::spawnGhost(string color){
    Ghost* g = new Ghost(x,y,width-2,height-2,sprite,em, color);   
    em->ghosts.push_back(g);
}

void GhostSpawner::keyPressed(int key){
    if(key == 'g'){
        if (ghostCounter < 4){ //since it is defaulted that it spawns 4 ghosts, ghostCounter counts how many times the user manually soawns more and limit it to 4 new ghosts (no more than 8 in total)
            spawnGhost(colors[ofRandom(4)]);   //spawns  a ghost with a random color (either red, pink, cyan, or orange)
            ghostCounter++;      // increments the counter when a new ghost is spawned
        }
       
    }
}