#pragma once

#include "State.h"
#include "Player.h"
#include "MapBuilder.h"
#include "EntityManager.h"


class GameState: public State{
    public: 
        GameState();
		~GameState();
		void reset();
		void tick();
		void render();
		void keyPressed(int key);
		void mousePressed(int x, int y, int button);
		void keyReleased(int key);
		int getFinalScore();
		void resetGame();
		void FinalScore();
		void setisMario(bool isMario);
		void stopMusic();
	
	private:
		ofSoundPlayer music;
		ofSoundPlayer music1;
		ofImage mapImage;
		Map* map;
		
		int finalScore=0;
		



};