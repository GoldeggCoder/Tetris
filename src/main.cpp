/*
	Autor:	Benedikt Walter
	Klasse:	2AHELS
	Titel:	Tetris
	Datum:	24.3.2022
*/

#include <iostream>
#include "console.cpp"

#define AE 132
#define OE 148
#define UE 129
#define UE_GROSS 154
#define AE_GROSS 142
#define OE_GROSS 153

#define BLOCK 219

#define START_X 1
#define START_Y 4

#define HEIGHT 15
#define WIDTH 10

using namespace std;

void initAll();
void closeAll();

class block
{
public:
    int objectID;
    int direction;
    int currentXY[2];
    int lastXY[2];
    void initVars();
    void printBlock();
    void deleteBlock();
    void nextPeriod();
    int checkValid();
};

void block::initVars()
{
    this->objectID = 0;
    this->direction = 0;
    this->currentXY[0] = 0;
    this->currentXY[1] = 0;
    this->lastXY[0] = 0;
    this->lastXY[1] = 0;
}

void block::printBlock()
{
    gotoxy(START_X+(WIDTH/2)+this->currentXY[0], START_Y+this->currentXY[1]+1);
    textcolor(BLUE);
    cout << (char)BLOCK;
    textcolor(GREEN);
}

void block::deleteBlock()
{
    gotoxy(START_X+(WIDTH/2)+this->lastXY[0], START_Y+this->lastXY[1]+1);
    textcolor(BLACK);
    cout << (char)BLOCK;
    textcolor(GREEN);
}

void block::nextPeriod()
{
    if(this->currentXY[1]+1 <= HEIGHT)
    {
        this->lastXY[1] = this->currentXY[1];
        (this->currentXY[1])++;
    }
}

int block::checkValid()
{
    if((this->currentXY[1]) < HEIGHT)
        return 1;
    else
        return 0;
}

int checkOtherBlocks(block *blocks, int currentBlock, int counter)
{
    for(int i = 0; i <= counter; i++)
    {
        if((blocks[currentBlock].currentXY[1])+1 == blocks[i].currentXY[1])
            return 0;
    }
    return 1;
}

int main()
{
    int counter = 0;
    block blocks[200];

    initAll();

    while(1)
    {
        blocks[counter].initVars();
        do
        {
            blocks[counter].deleteBlock();
            blocks[counter].printBlock();
            delay(200);
            blocks[counter].nextPeriod();
        }
        while(blocks[counter].checkValid() && checkOtherBlocks(blocks, counter, counter));
        counter++;
    }
    
    closeAll();
    return 0;
}

void initAll()
{
    setCursorType(0);
    initConsole();
    textcolor(GREEN);
    gotoxy(1,1);
    cout << "Tetris V1.0" << endl;

    gotoxy(START_X+1, START_Y);
    for(int i = 0; i < WIDTH; i++)
    {
        cout << "-";
    }

    gotoxy(START_X+1, START_Y+HEIGHT+1);
    for(int i = 0; i < WIDTH; i++)
    {
        cout << "-";
    }

    gotoxy(START_X-1, START_Y+1);
    for(int i = 0; i < HEIGHT; i++)
    {
        cout << " |" << endl;
    }

    for(int i = 0; i < HEIGHT; i++)
    {
        gotoxy(START_X+WIDTH+1, START_Y+i+1);
        cout << "|";
    }
}

void closeAll()
{
    getch();
    clrscr();
    closeConsole();
}