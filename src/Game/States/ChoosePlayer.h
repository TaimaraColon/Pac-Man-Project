#pragma once

#include "State.h"
#include "Button.h"
#include "Animation.h" 
#include "MapBuilder.h"

class ChoosePlayer : public State {
private:
    ofImage pacman;
    ofImage mario;
	Animation* pacmanAnim;
    Animation* marioAnim;
	Button *choosePacman;
	Button *chooseMario;

	
	
public:
	ChoosePlayer();
	~ChoosePlayer();
	void tick();
	void render();
	void keyPressed(int key);
	void mousePressed(int x, int y, int button);
	void reset();
	volatile bool isMario = false;
	volatile bool getisMario(){return isMario;}
	void setisMario(bool isMario);
	
};

