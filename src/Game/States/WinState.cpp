#include "WinState.h"

WinState::WinState() {
	PlayAgainButton = new Button(ofGetWidth()/2, ofGetHeight()/2, 64, 50, "Play Again");
	QuitButton = new Button(ofGetWidth()/2, ofGetHeight()/2+51, 64, 50, "Quit");
	//loads pacman image to be in the winstate screen
	img1.load("images/pacman.png");
	vector<ofImage> rightAnimframes;
    ofImage temp;
	for(int i=0; i<3; i++){
        temp.cropFrom(img1, i*16, 0, 16, 16);
        rightAnimframes.push_back(temp);
    }
	anim = new Animation(10,rightAnimframes);

}
void WinState::tick() {
	PlayAgainButton->tick();
	QuitButton->tick();
	anim->tick();
	if(PlayAgainButton->wasPressed()){
		setNextState("Game");           //when play again is hit the game starts again
		setFinished(true);
	}
	if(QuitButton->wasPressed()){
		setNextState("Menu");           //when quit is hit it switches to the menu
		setFinished(true);	
	}
}
void WinState::render() {
	ofDrawBitmapString("YOU WON !", ofGetWidth()/2, ofGetHeight()/2-150, 50);
	ofDrawBitmapString("Score: " + to_string(score), ofGetWidth()/2, ofGetHeight()/2-300, 50);
	ofSetBackgroundColor(0, 0, 0);
	ofSetColor(256, 256, 256);
	anim->getCurrentFrame().draw(ofGetWidth()/2, ofGetHeight()/2-100, 100, 100);
	PlayAgainButton->render();
	QuitButton->render();


}

void WinState::keyPressed(int key){
	
}

void WinState::mousePressed(int x, int y, int button){
	PlayAgainButton->mousePressed(x, y);
	QuitButton->mousePressed(x,y);
}

void WinState::reset(){
	setFinished(false);
	setNextState("");
	PlayAgainButton->reset();
	QuitButton->reset();
}

void WinState::setScore(int sc){
    score = sc;
}

WinState::~WinState(){		//destructor para que una vez acabe el scope, se borre el gameover state
	delete PlayAgainButton;
	delete QuitButton;
	delete anim;
}