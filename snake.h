
#pragma once
#include <iostream>
#include "wall.h"
#include "food.h"
using namespace std;

class Snake{
public:
    enum{
        UP='w',
        DOWN='s',
        LEFT='a',
        RIGHT='d'
    };
    struct Point{
        int x,y;
        Point* next;
    };
    //Snake(){};
    Snake(Wall& tempWall,Food& tempFood);
    void initSnake();
    void destoryPoint();
    void addPoint(int x,int y);
    void delPoint();
    bool move(char key);

    int getSleepTime();
    int countList();
    int getScore();

private:
    Point* pHead;
    Wall& wall;
    Food& food;
    bool isRool;
};
