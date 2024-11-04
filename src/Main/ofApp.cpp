#include "ofApp.h"
using namespace std;
//--------------------------------------------------------------
void ofApp::setup(){
	ofSetFrameRate(30);
	ofSetWindowTitle("C++ Game Box");
	//States
	menuState = new MenuState();		//keyword "new" makes them permanent in the memory
	gameState = new GameState();
	gameOverState = new GameOverState();
	pauseState = new PauseState();
	winState = new WinState();
	choosePlayer = new ChoosePlayer();

	// Initial State
	currentState = menuState;
}

void ofApp::exit() {
	// delete menuState;		
	// delete gameState;
	// delete gameOverState;
	// delete pauseState;
	// delete winState;
	// delete choosePlayer;
}

//--------------------------------------------------------------
void ofApp::update(){
	if (currentState != nullptr){
		currentState->tick();		//tick()
		if(currentState->hasFinished()){

			if(currentState->getNextState() == "Menu"){
				if (currentState == pauseState){           //if the next state is menu and the current is pause it means the button quit was clicked, therefore a reset of the game must me done
					gameState->resetGame();                //resets the game
				}	
						
					currentState = menuState;
					
			}
			else if(currentState->getNextState() == "ChoosePlayer"){
				
				currentState = choosePlayer;
			}
			else if(currentState->getNextState() == "Game"){
				volatile ChoosePlayer *chooseplayer = dynamic_cast<ChoosePlayer*>(currentState);
				if(chooseplayer != nullptr){
					gameState->setisMario(choosePlayer->getisMario());   //sets which player was chosen
				}
	
				currentState = gameState;
			}else if(currentState->getNextState() == "over"){
				gameOverState->setScore(gameState->getFinalScore());
				if (currentState == gameState){
					gameState->resetGame();	          //if the next state is over and the current state is game it means that a new game started so a reset of the game must be done
				}
				gameState->stopMusic();
				currentState = gameOverState;
			}else if (currentState->getNextState() == "Win"){
				winState->setScore(gameState->getFinalScore());    //sets the score
				if(currentState == gameState){
					gameState->resetGame();         //resets the game if the current state is win
				}
				gameState->stopMusic();    //if the current state is win state, stop the music
				currentState = winState;
			}
			else if (currentState->getNextState() == "Pause"){
				gameState->stopMusic();        //if the current state is pause then stop the music
				currentState = pauseState;
			}
			currentState->reset();         //reset the current state
			gameState->reset();      
			
		}
	}
		
}

//--------------------------------------------------------------
void ofApp::draw(){
	if (currentState != nullptr)
		currentState->render();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	if (currentState != nullptr){
		currentState->keyPressed(key);
	}
	//Turn Volume Down (Mute)	
	if( key == '-' ){
		ofSoundSetVolume(0);
	}
	
	//Turn Volume Back Up
	if( key == '=' ){
		ofSoundSetVolume(1);
	}

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
	if (currentState != nullptr)
			currentState->keyReleased(key);
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
	if (currentState != nullptr)
		currentState->mouseMoved(x, y);
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
	if (currentState != nullptr)
		currentState->mouseDragged(x, y, button);
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
	if (currentState != nullptr)
		currentState->mousePressed(x, y, button);
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
	if (currentState != nullptr)
		currentState->mouseReleased(x, y, button);
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){
	if (currentState != nullptr)
			currentState->mouseEntered(x, y);
}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){
	if (currentState != nullptr)
		currentState->mouseExited(x, y);
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){
	if (currentState != nullptr)
			currentState->windowResized(w, h);
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){
	if (currentState != nullptr)
		currentState->gotMessage(msg);
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 
	if (currentState != nullptr)
		currentState->dragEvent(dragInfo);
}
