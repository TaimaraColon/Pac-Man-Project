#include "PauseState.h"

using namespace std;

PauseState::PauseState(){
    ResumeButton = new Button(ofGetWidth()/2-32, ofGetHeight()/2, 64, 50, "Resume");    
    QuitButton = new Button(ofGetWidth()/2-32, ofGetHeight()/2+51, 64, 50, "Quit");
	img1.load("images/pacman.png");         //loads a pause state with pacman animation
	vector<ofImage> rightAnimframes;
    ofImage temp;
	for(int i=0; i<3; i++){
        temp.cropFrom(img1, i*16, 0, 16, 16);
        rightAnimframes.push_back(temp);
    }
	anim = new Animation(10,rightAnimframes);

}
void PauseState::tick() {
	anim->tick();
	ResumeButton->tick();
	if(ResumeButton->wasPressed()){
		setNextState("Game");			//when pressing resume, the game will continue
		setFinished(true);				
	}
    QuitButton->tick();
	if(QuitButton->wasPressed()){
		setNextState("Menu");           //when pressing quit, it takes  you to the menu
		setFinished(true);	
	}
	
}
void PauseState::render() {
	string title = "PAUSED !";
	ofDrawBitmapString(title, ofGetWidth()/2-4*title.size(), ofGetHeight()/2-300, 50);
	ofSetBackgroundColor(0, 0, 0);
	ofSetColor(256, 256, 256);
	anim->getCurrentFrame().draw(ofGetWidth()/2-50, ofGetHeight()/2-100, 100, 100);
	ResumeButton->render();
    QuitButton->render();
	


}
void PauseState::keyPressed(int key){
   
}
void PauseState::mousePressed(int x, int y, int button){
	ResumeButton->mousePressed(x,y);
	QuitButton->mousePressed(x,y);
}

void PauseState::reset(){
	setFinished(false);
	setNextState("");
	ResumeButton->reset();
    QuitButton->reset();
}

PauseState::~PauseState(){
	delete QuitButton;
    delete ResumeButton;
	delete anim;
	
}