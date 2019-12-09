
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "wall.h"
#include "snake.h"
#include "food.h"
#include <conio.h>
#include <windows.h>

void getoxy(HANDLE hOut,int x,int y){
    COORD pos;
    pos.X=x;
    pos.Y=y;
    SetConsoleCursorPosition(hOut,pos);
}
HANDLE hOut=GetStdHandle(STD_OUTPUT_HANDLE);

int main(){
    bool isDead=false;
    char preKey=NULL;
    Wall wall;
    wall.initWall();
    wall.drawWall();
    Food food(wall);
    food.setFood();
    Snake snake(wall,food);
    snake.initSnake();
    getoxy(hOut,0,Wall::ROW);
    cout<<"当前得分："<<snake.getScore()<<endl;
    while(!isDead){
        char key=_getch();
        if(preKey==NULL && key==snake.LEFT)
            continue;
        do{
            if((key==snake.UP&&preKey==snake.DOWN) ||
               (key==snake.DOWN&&preKey==snake.UP) ||
               (key==snake.LEFT&&preKey==snake.RIGHT) ||
               (key==snake.RIGHT&&preKey==snake.LEFT))
                key=preKey;
            else
                preKey=key;
            if(key==snake.UP || key==snake.DOWN || key==snake.LEFT || key==snake.RIGHT)
            if(snake.move(key)){
                getoxy(hOut,0,Wall::ROW);
                cout<<"当前得分："<<snake.getScore()<<endl;
                Sleep(snake.getSleepTime());
            }
            else{
                isDead=true;
                break;
            }
            else{
                preKey=key;
            }
            preKey=key;
        } while(!_kbhit());
    }

    return 0;
}
