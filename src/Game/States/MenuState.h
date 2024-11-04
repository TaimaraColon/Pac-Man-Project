#pragma once

#include "State.h"
#include "Button.h"
#include "Animation.h" 
#include "MapBuilder.h"

class MenuState : public State {
private:
	ofImage img1;
	Button *startButton;
	Animation* anim;

	ofSoundPlayer music;
	ofImage mapImage;
	Map* map;
	int finalScore=0;

public:
	MenuState();
	~MenuState();
	void tick();
	void render();
	void keyPressed(int key);
	void mousePressed(int x, int y, int button);
	void reset();
};
