
#pragma once
#include "wall.h"

class Food{
public:
    //Food(){};
    Food(Wall& tempWall);
    void setFood();
private:
    int foodX;
    int foodY;
    Wall& wall;
};
