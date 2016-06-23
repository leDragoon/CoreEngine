#pragma once
#include<Windows.h>
#include<vector>

using std::vector;

class InputHandler
{
private:
	vector<INT> keysPressed;
	bool mouseButtonsPressed[3];
	bool ignoreMouseMove;
	int mousePosX;
	int mousePosY;
	int mouseDeltaX;
	int mouseDeltaY;
public:
	void handleMessage(MSG msg);
	void ignoreNextMouseMove();
	bool getKeyPressed(int toGet);
	bool getMouseButtonPressed(int buttonToGet);
	int getMousePosX();
	int getMousePosY();
	int getMouseDeltaX();
	int getMouseDeltaY();

	InputHandler();
};