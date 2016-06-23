#include "Input.h"

void InputHandler::handleMessage(MSG msg)
{
	mouseDeltaX = 0;
	mouseDeltaY = 0;

	if (msg.message == WM_KEYDOWN)
	{
		bool contains = false;

		for (unsigned int i = 0; i < keysPressed.size(); i++)
		{
			if (keysPressed[i] == msg.wParam)
			{
				contains = true;
			}
		}

		if (contains == false)
		{
			keysPressed.push_back(msg.wParam);
		}
	}

	else if (msg.message == WM_KEYUP)
	{
		for (unsigned int i = 0; i < keysPressed.size(); i++)
		{
			if (keysPressed[i] == msg.wParam)
			{
				keysPressed.erase(keysPressed.begin() + i, keysPressed.begin() + i + 1);
			}
		}
	}

	else if (msg.message == WM_LBUTTONDOWN)
	{
		mouseButtonsPressed[0] = true;
	}

	else if (msg.message == WM_RBUTTONDOWN)
	{
		mouseButtonsPressed[1] = true;
	}

	else if (msg.message == WM_MBUTTONDOWN)
	{
		mouseButtonsPressed[2] = true;
	}

	else if (msg.message == WM_LBUTTONUP)
	{
		mouseButtonsPressed[0] = false;
	}

	else if (msg.message == WM_RBUTTONUP)
	{
		mouseButtonsPressed[1] = false;
	}

	else if (msg.message == WM_MBUTTONUP)
	{
		mouseButtonsPressed[2] = false;
	}

	else if (msg.message == WM_MOUSEMOVE)
	{
		if (ignoreMouseMove == false)
		{
			mouseDeltaX = LOWORD(msg.lParam) - mousePosX;
			mouseDeltaY = HIWORD(msg.lParam) - mousePosY;
		}

		else
		{
			ignoreMouseMove = false;
		}

		mousePosX = LOWORD(msg.lParam);
		mousePosY = HIWORD(msg.lParam);
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
