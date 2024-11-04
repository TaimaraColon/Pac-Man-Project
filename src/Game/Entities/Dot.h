#pragma once

#include "Entity.h"

class Dot: public Entity{
    public:
        Dot(int x, int y, int width, int height, ofImage);
        int getX(){ return x;}
        int getY(){ return y;}
};