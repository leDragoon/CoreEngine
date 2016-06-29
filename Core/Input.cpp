#include "Input.h"

void InputHandler::handleMessage(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	mouseDeltaX = 0;
	mouseDeltaY = 0;

	if (msg == WM_KEYDOWN)
	{
		bool contains = false;

		for (unsigned int i = 0; i < keysPressed.size(); i++)
		{
			if (keysPressed[i] == wParam)
			{
				contains = true;
			}
		}

		if (contains == false)
		{
			keysPressed.push_back(wParam);
		}
	}

	else if (msg == WM_KEYUP)
	{
		for (unsigned int i = 0; i < keysPressed.size(); i++)
		{
			if (keysPressed[i] == wParam)
			{
				keysPressed.erase(keysPressed.begin() + i, keysPressed.begin() + i + 1);
			}
		}
	}

	else if (msg == WM_LBUTTONDOWN)
	{
		mouseButtonsPressed[0] = true;
	}

	else if (msg == WM_RBUTTONDOWN)
	{
		mouseButtonsPressed[1] = true;
	}

	else if (msg == WM_MBUTTONDOWN)
	{
		mouseButtonsPressed[2] = true;
	}

	else if (msg == WM_LBUTTONUP)
	{
		mouseButtonsPressed[0] = false;
	}

	else if (msg == WM_RBUTTONUP)
	{
		mouseButtonsPressed[1] = false;
	}

	else if (msg == WM_MBUTTONUP)
	{
		mouseButtonsPressed[2] = false;
	}

	else if(msg == WM_MOUSEMOVE)
	{
		if (ignoreMouseMove == false)
		{
			mouseDeltaX = LOWORD(lParam) - mousePosX;
			mouseDeltaY = HIWORD(lParam) - mousePosY;
		}

		else
		{
			ignoreMouseMove = false;
		}

		mousePosX = LOWORD(lParam);
		mousePosY = HIWORD(lParam);
	}
}

void InputHandler::ignoreNextMouseMove()
{
	ignoreMouseMove = true;
}

bool InputHandler::getKeyPressed(int toGet)
{
	for (unsigned int i = 0; i < keysPressed.size(); i++)
	{
		if (keysPressed[i] == toGet)
		{
			return true;
		}
	}

	return false;
}

bool InputHandler::getMouseButtonPressed(int buttonToGet)
{
	if (buttonToGet < 3 && buttonToGet >= 0)
	{
		return mouseButtonsPressed[buttonToGet];
	}

	return false;
}

int InputHandler::getMousePosX()
{
	return mousePosX;
}

int InputHandler::getMousePosY()
{
	return mousePosY;
}

int InputHandler::getMouseDeltaX()
{
	return mouseDeltaX;
}

int InputHandler::getMouseDeltaY()
{
	return mouseDeltaY;
}

InputHandler::InputHandler()
{
	mouseButtonsPressed[0] = false;
	mouseButtonsPressed[1] = false;
	mouseButtonsPressed[2] = false;
	mousePosX = 0;
	mousePosY = 0;
	mouseDeltaX = 0;
	mouseDeltaY = 0;
}
