#pragma once
#include<windows.h>
#include <iostream>
#include "CPicture.h"

class GameStart
{
public:
	GameStart();
	static VOID LoadMap();
	VOID DrawMap(HWND);
	void KeyDown(WPARAM);
	void MouseMove(LPARAM);
	~GameStart();
	static void SetGamestatus(int);
	static int getGamestatus();
	static void freeOption();
private:
	static Picture* Option[7];
	static int Gamestatus;
};

