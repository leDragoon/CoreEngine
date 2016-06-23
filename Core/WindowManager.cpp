#include "WindowManager.h"

void CoreWindow::open()
{

}

void CoreWindow::setWindowSize(int width, int height)
{
	windowWidth = width;
	windowHeight = height;
}

void CoreWindow::setWindowSize(windowDims size)
{
	windowWidth = size.x;
	windowHeight = size.y;
}

void CoreWindow::setWindowTitle(string title)
{
	windowTitle = title;
}

void CoreWindow::setWindowPosition(int xPosition, int yPosition)
{
	windowPositionX = xPosition;
	windowPositionY = yPosition;
}

void CoreWindow::setWindowPosition(windowDims position)
{
	windowPositionX = position.x;
	windowPositionY = position.y;
}

void CoreWindow::setHandle(HWND handle)
{
	hWnd = handle;
}

void CoreWindow::setWindowedMode(bool windowedMode)
{
	windowIsWindowed = windowedMode;
}

bool CoreWindow::getWindowedMode()
{
	return windowIsWindowed;
}

HWND CoreWindow::getHandle()
{
	return hWnd;
}

string CoreWindow::getWindowTitle()
{
	return windowTitle;
}

windowDims CoreWindow::getWindowSize()
{
	return windowDims(windowWidth, windowHeight);
}

windowDims CoreWindow::getWindowPosition()
{
	return windowDims(windowPositionX, windowPositionY);
}

void CoreWindow::setWindowVisible(bool visible)
{
	windowVisible = visible;
}

bool CoreWindow::getWindowVisibility()
{
	return windowVisible;
}

CoreWindow::CoreWindow()
{
	windowTitle = "CoreWindow";
	windowWidth = 640;
	windowHeight = 480;
	windowPositionX = CW_USEDEFAULT;
	windowPositionY = CW_USEDEFAULT;
	windowVisible = true;
	windowIsWindowed = true;
	open();
}

CoreWindow::CoreWindow(string winTitle)
{
	windowTitle = winTitle;
	windowWidth = 640;
	windowHeight = 480;
	windowVisible = true;
	windowPositionX = CW_USEDEFAULT;
	windowPositionY = CW_USEDEFAULT;
	windowIsWindowed = true;
	open();
}

CoreWindow::CoreWindow(string winTitle, int width, int height)
{
	windowTitle = winTitle;
	windowWidth = width;
	windowHeight = height;
	windowVisible = true;
	windowPositionX = CW_USEDEFAULT;
	windowPositionY = CW_USEDEFAULT;
	windowIsWindowed = true;
	open();
}

CoreWindow::CoreWindow(string winTitle, windowDims size)
{
	windowTitle = winTitle;
	windowWidth = size.x;
	windowHeight = size.y;
	windowVisible = true;
	windowPositionX = CW_USEDEFAULT;
	windowPositionY = CW_USEDEFAULT;
	windowIsWindowed = true;
	open();
}

CoreWindow::CoreWindow(SettingsCategory windowSettings)
{
	windowTitle = windowSettings.getString("windowTitle");
	windowWidth = windowSettings.getInt("windowWidth");
	windowHeight = windowSettings.getInt("windowHeight");
	windowVisible = true;
	windowIsWindowed = windowSettings.getBool("windowWindowed");
	open();
}

CoreWindow::~CoreWindow()
{

}
