#pragma once

#include "State.h"
#include "Button.h"
#include "Animation.h" 
#include "Player.h"
#include "MapBuilder.h"

class PauseState: public State{
    private:
	ofImage img1;
	Button *ResumeButton;
    Button *QuitButton;
	Animation* anim;

public:
	PauseState();
	~PauseState();
	void tick();
	void render();
	void keyPressed(int key);
	void mousePressed(int x, int y, int button);
	void reset();
};