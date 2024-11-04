#include "GameState.h"
#include "Entity.h"


GameState::GameState() {
	music1.load("music/MarioSong.mp3");  //added super mario bros theme song
	music.load("music/pacman_chomp.wav");
	mapImage.load("images\\map2.png");		//controls the map based off an image in the bin folder
	map = MapBuilder().createMap(mapImage);
}
void GameState::tick() {			//es el update() del game state
	if(map->getPlayer()->getisMario()){  //checks which player was chosen and sets the corresponding music
		if(!music1.isPlaying()){
			music1.play();
		}
	}else{
		if(!music.isPlaying()){
			music.play();
		}
	}
	
	map->tick();
	if(map->getPlayer()->getHealth() == 0 ){
		
		setFinished(true);
		setNextState("over");
		map->getPlayer()->setHealth(3);
		finalScore = map->getPlayer()->getScore();
		map->getPlayer()->setScore(0);
		map= MapBuilder().createMap(mapImage); 		//creates the map again after the player finishes all of his lives
	}
	
	if(map->getEntityManager()->entities.size() == 0){   //if there are not dots in the map left, it means we won !
		finalScore = map->getPlayer()->getScore();
		setFinished(true);
		setNextState("Win");       //sets state to win 
	}
}

void GameState::render() {
	map->render();
}

void GameState::keyPressed(int key){
	map->keyPressed(key);
	if (key == 'p'){
		setFinished(true);
        setNextState("Pause");     //if 'p' was pressed during gamestate it means we want to pause the game; sets next state to pause
    }
	if(key == 'y'){                //activates the win state manually
		setFinished(true);
		setNextState("Win");
	}
}

void GameState::mousePressed(int x, int y, int button){
	map->mousePressed(x, y, button);
}

void GameState::keyReleased(int key){
	map->keyReleased(key);
}

void GameState::reset(){
	setFinished(false);
	setNextState("");
}

int GameState::getFinalScore(){
	return finalScore;
}

void GameState::resetGame(){                   
		setFinished(true);          
		setNextState("over");
		
		map->getPlayer()->setHealth(3);
		finalScore = map->getPlayer()->getScore();
		map->getPlayer()->setScore(0);
		map= MapBuilder().createMap(mapImage);	
}
void GameState::stopMusic(){
	music1.stop();
	music.stop();
}

void GameState::setisMario(volatile bool isMario){
	map->getPlayer()->setisMario(isMario);
}
GameState::~GameState(){
	delete map;
}