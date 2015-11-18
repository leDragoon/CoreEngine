#pragma once
#include<DirectXMath.h>
#include<Vector2i.h>
#include<string>
#include<SystemInfo.h>
#include<vector>
#include<Windows.h>
#include<SettingsFile.h>

using std::string;
using std::vector;

typedef vector2i windowDims;

class CoreWindow
{
private:
	int windowWidth;
	int windowHeight;
	int windowPositionX;
	int windowPositionY;
	bool windowVisible;
	bool windowIsWindowed;
	string windowTitle;
	HWND hWnd;
	WNDCLASSEX wClass;
	void open();
public:
	void setWindowSize(int width, int height);
	void setWindowSize(windowDims size);
	void setWindowTitle(string title);
	void setWindowPosition(int xPosition, int yPosition);
	void setWindowPosition(windowDims position);
	void setHandle(HWND handle);
	void setWindowedMode(bool windowedMode);
	bool getWindowedMode();
	HWND getHandle();
	string getWindowTitle();
	windowDims getWindowSize();
	windowDims getWindowPosition();
	void setWindowVisible(bool visible);
	bool getWindowVisibility();
	

	CoreWindow();
	CoreWindow(string winTitle);
	CoreWindow(string winTitle, int width, int height);
	CoreWindow(string winTitle, windowDims size);
	CoreWindow(SettingsCategory windowSettings);
	~CoreWindow();
};
