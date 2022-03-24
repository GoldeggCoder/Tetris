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

using namespace std;

void initAll();
void closeAll();

int main()
{
    initAll();    

    return 0;
}

void initAll()
{
    setCursorType(0);
    initConsole();
    textcolor(GREEN);
    gotoxy(1,1);

    cout << "Tetris V1.0" << endl;
}

void closeAll()
{
    clrscr();
    closeConsole();
}