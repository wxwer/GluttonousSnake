
#include "snake.h"
#include <windows.h>


void getoxy1(HANDLE hOut1,int x,int y){
    COORD pos;
    pos.X=x;
    pos.Y=y;
    SetConsoleCursorPosition(hOut1,pos);
}
HANDLE hOut1=GetStdHandle(STD_OUTPUT_HANDLE);

Snake::Snake(Wall& tempWall,Food& tempFood):wall(tempWall),food(tempFood){
    pHead=NULL;
    isRool=false;
}
void Snake::initSnake(){
    destoryPoint();
    addPoint(5,3);
    addPoint(5,4);
    addPoint(5,5);
}
void Snake::destoryPoint(){
    Point* pCur=pHead;
    while(pHead){
        pCur=pHead->next;
        wall.setWall(pHead->x,pHead->y,' ');
        delete pHead;
        pHead=pCur;
    }
}
void Snake::addPoint(int x,int y){
    Point* newPoint=new Point;
    newPoint->x=x;
    newPoint->y=y;
    newPoint->next=NULL;
    if(pHead){
        wall.setWall(pHead->x,pHead->y,'=');
        getoxy1(hOut1,pHead->y*2,pHead->x);
        cout<<"=";
    }
    newPoint->next=pHead;
    pHead=newPoint;
    wall.setWall(pHead->x,pHead->y,'@');
    getoxy1(hOut1,pHead->y*2,pHead->x);
    cout<<"@";
}
void Snake::delPoint(){
    if(pHead==NULL || pHead->next==NULL)
        return;
    Point *pPre=pHead,*pCur=pHead->next;
    while(pCur->next){
        pCur=pCur->next;
        pPre=pPre->next;
    }
    wall.setWall(pCur->x,pCur->y,' ');
    getoxy1(hOut1,pCur->y*2,pCur->x);
    cout<<" ";
    delete pCur;
    pCur=NULL;
    pPre->next=NULL;
}
bool Snake::move(char key){
    int x=pHead->x;
    int y=pHead->y;
    switch(key){
    case UP:
        --x;
        break;
    case DOWN:
        ++x;
        break;
    case LEFT:
        --y;
        break;
    case RIGHT:
        ++y;
        break;
    default:
        break;
    }
    Point* pCur=pHead->next;
    while(pCur->next)
        pCur=pCur->next;
    if(pCur->x==x && pCur->y==y)
        isRool=true;
    else{
        if(wall.getWall(x,y)=='*' || wall.getWall(x,y)=='='){
            addPoint(x,y);
            delPoint();
            system("cls");
            wall.drawWall();
            cout<<"×îÖÕµÃ·Ö£º"<<getScore()<<endl;
            cout<<"game over!"<<endl;
            return false;
        }
    }
    if(wall.getWall(x,y)=='#'){
        addPoint(x,y);
        food.setFood();
    }
    else{
        addPoint(x,y);
        delPoint();
        if(isRool){
            wall.setWall(x,y,'@');
            getoxy1(hOut1,2*y,x);
            cout<<"@";
        }
    }
    return true;
}

int Snake::getSleepTime(){
    int size=countList();
    int sleepTime=0;
    if(size<=5)
        sleepTime=500;
    else if(size>5 && size<=10)
        sleepTime=300;
    else
        sleepTime=200;
    return sleepTime;
}
int Snake::countList(){
    Point* pTemp=pHead;
    int size=0;
    while(pTemp){
        pTemp=pTemp->next;
        size++;
    }
    return size;
}
int Snake::getScore(){
    int size=countList()-3;
    int score=0;
    if(size<=8)
        score=size*100;
    else if(size>8 && size<=15)
        score=800+(size-8)*200;
    else
        score=2200+(size-15)*300;
    return score;
}
