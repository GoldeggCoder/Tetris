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
    int currentXY[2];
    int lastXY[2];
    void initVars();
    void printBlock();
    void deleteLastBlock();
    void deleteCurrentBlock();
    void moveDown();
    void moveLeft();
    void moveRight();
    int checkValidDown();
    int checkValidLeft();
    int checkValidRight();
};

void block::initVars()
{
    this->currentXY[0] = (WIDTH/2);
    this->currentXY[1] = 1;
    this->lastXY[0] = (WIDTH/2);
    this->lastXY[1] = 1;
}

void block::printBlock()
{
    gotoxy(START_X+this->currentXY[0], START_Y+this->currentXY[1]);
    textcolor(BLUE);
    cout << (char)BLOCK;
    textcolor(GREEN);
}

void block::deleteLastBlock()
{
    gotoxy(START_X+this->lastXY[0], START_Y+this->lastXY[1]);
    textcolor(BLACK);
    cout << (char)BLOCK;
    textcolor(GREEN);
}

void block::moveDown()
{
    if(this->currentXY[1] < HEIGHT)
    {
        this->lastXY[0] = this->currentXY[0];
        this->lastXY[1] = this->currentXY[1];
        (this->currentXY[1])++;
    }
}

void block::moveLeft()
{
    if(this->checkValidLeft())
    {
        (this->currentXY[0])--;
    }
}

void block::moveRight()
{
    if(this->checkValidRight())
    {
        (this->currentXY[0])++;
    }
}

int block::checkValidDown()
{
    if((this->currentXY[1]) < HEIGHT)
        return 1;
    else
        return 0;
}

int block::checkValidLeft()
{
    if((this->currentXY[0]-1) > 0)
        return 1;
    else
        return 0;
}

int block::checkValidRight()
{
    if((this->currentXY[0]+1) <= WIDTH)
        return 1;
    else
        return 0;
}

int checkOtherBlocks(block *blocks, int currentBlock, int counter, int direction)
{
    for(int i = 0; i <= counter; i++)
    {
        if(direction == 0)
        {
            if(blocks[currentBlock].currentXY[0] == blocks[i].currentXY[0] && (blocks[currentBlock].currentXY[1])+1 == blocks[i].currentXY[1])
                return 0;
        }
        else if(direction == 1)
        {
            if((blocks[currentBlock].currentXY[0]-1) == blocks[i].currentXY[0] && blocks[currentBlock].currentXY[1] == blocks[i].currentXY[1])
                return 0;
        }
        else if(direction == 2)
        {
            if((blocks[currentBlock].currentXY[0]+1) == blocks[i].currentXY[0] && blocks[currentBlock].currentXY[1] == blocks[i].currentXY[1])
                return 0;
        }
    }
    return 1;
}

int checkKey()
{
    char key = getch();
    if(key == LEFT)
        return 1;
    else if(key == RIGHT)
        return 2;
    else
        return 0;
}

int main()
{
    int counter = 0, key = 0;
    unsigned long startTime;
    block blocks[200];

    initAll();

    while(1)
    {
        blocks[counter].initVars();
        do
        {
            blocks[counter].deleteLastBlock();
            blocks[counter].printBlock();
            blocks[counter].moveDown();
            startTime = clock();
            while(clock() - startTime < (20 * (CLOCKS_PER_SEC / 1000)))
            {
                fflush(stdin);
                if(kbhit())
                {
                    key = checkKey();
                    if(key == 1 && checkOtherBlocks(blocks, counter, counter, 1))
                        blocks[counter].moveLeft();
                    else if(key == 2 && checkOtherBlocks(blocks, counter, counter, 2))
                        blocks[counter].moveRight();
                }
            }
        }
        while(blocks[counter].checkValidDown() && checkOtherBlocks(blocks, counter, counter, 0));
        blocks[counter].deleteLastBlock();
        blocks[counter].printBlock();
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