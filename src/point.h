#ifndef _POINT_H_
#define _POINT_H_

#include <iostream>
#include <stdlib.h>
#include <ncurses.h>
#include <ctime>
#include <fstream>

using namespace std;

class Point{
    int x, y, moves;
  public:
    Point();
    Point(int, int);
    ~Point();
    int getX();
    int getY();
    void showPos();
    void keyPressed(char);
    bool probe();
    void isGameOver();
};

//misc
void menu();
int read(int, int);
//kejs1
void drawBoard(Point s);
void newGame();
//kejs2
void credits();

#endif
