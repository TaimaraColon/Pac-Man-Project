#pragma once

#include "State.h"
#include "Button.h"
#include "Animation.h" 
#include "Player.h"
#include "MapBuilder.h"

class WinState: public State{
    private:
	ofImage img1;
	Button *PlayAgainButton;
	Button *QuitButton;
	Animation* anim;
	int score=0;

public:
	WinState();
	~WinState();
	void tick();
	void render();
	void keyPressed(int key);
	void mousePressed(int x, int y, int button);
	void setScore(int);
	void reset();
};