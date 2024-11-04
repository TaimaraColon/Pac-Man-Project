#include "ChoosePlayer.h"

ChoosePlayer::ChoosePlayer() {
    choosePacman = new Button(ofGetWidth()/2-150, ofGetHeight()/2, 64, 50, "PACMAN");
    chooseMario = new Button(ofGetWidth()/2+50, ofGetHeight()/2, 64, 50, "MARIO");
    pacman.load("images/pacman.png");   //pacman animation
	vector<ofImage> rightAnimframes;
    ofImage temp;
	for(int i=0; i<3; i++){
        temp.cropFrom(pacman, i*16, 0, 16, 16);
        rightAnimframes.push_back(temp);
    }
	pacmanAnim = new Animation(10,rightAnimframes);

    mario.load("images/mario3.png");     //mario animation
    vector<ofImage> rightAnimframes2;
    ofImage temp2;
	for(int i=0; i<4; i++){
        temp2.cropFrom(mario, i*60+4, 0, 52, 80);
        rightAnimframes2.push_back(temp2);
    }
    marioAnim = new Animation(10,rightAnimframes2);

}

ChoosePlayer::~ChoosePlayer(){
	delete pacmanAnim;
    delete marioAnim;
    delete choosePacman;
    delete chooseMario;

}

void ChoosePlayer::tick() {
    choosePacman->tick();
    chooseMario->tick();
    if(choosePacman->wasPressed()){
		setNextState("Game");		//el proximo state que va a hacer cuando se acabe ese estado va a ser Game
		setFinished(true);				//when i hit the next button, se apaga mi state y va al proximo que su finished va a estar false
        setisMario(false);
	}
    if(chooseMario->wasPressed()){
		setNextState("Game");		//el proximo state que va a hacer cuando se acabe ese estado va a ser Game
		setFinished(true);				//when i hit the next button, se apaga mi state y va al proximo que su finished va a estar false
        setisMario(true);
	}
    pacmanAnim->tick();
	marioAnim->tick();
}
void ChoosePlayer::render() {
    string title = "CHOOSE YOUR CHARACTER";
	ofDrawBitmapString(title, ofGetWidth()/2-4*title.size(), ofGetHeight()/2-300, 50);
    ofSetBackgroundColor(0, 0, 0);
	ofSetColor(256, 256, 256);
    
    pacmanAnim->getCurrentFrame().draw(ofGetWidth()/2-150, ofGetHeight()/2-100, 100, 100);
    marioAnim->getCurrentFrame().draw(ofGetWidth()/2+50, ofGetHeight()/2-100, 100, 100);
    choosePacman->render();
    chooseMario->render();
}
void ChoosePlayer::setisMario(bool isMario){
    this->isMario = isMario;                   //sets chosen player
}

void ChoosePlayer::keyPressed(int key){
	
}

void ChoosePlayer::mousePressed(int x, int y, int button){
	choosePacman->mousePressed(x, y);
    chooseMario->mousePressed(x, y);
	
}

void ChoosePlayer::reset(){
	setFinished(false);
	setNextState("");
    chooseMario->reset();
    choosePacman->reset();
}

