#pragma once
#include<Windows.h>
#include<WindowManager.h>
#include<d3d11.h>
#include<DirectXColors.h>

class Renderer
{
private:
	HWND hWnd;
	ID3D11Device *dev;
	ID3D11DeviceContext *devCon;
	IDXGISwapChain *swap;
	ID3D11RenderTargetView *backBuffer;
	int outputWidth;
	int outputHeight;
	int refreshRate;
	int hardwareAntiAliasingCount;
	bool windowedMode;
	bool canBeInitialized;

	void resize();
public:
	void init();
	void render();
	void setWidth(int width);
	void setHeight(int height);
	void setSize(vector2i size);
	void resize(int width, int height);
	vector2i getSize();
	void setRefreshRate(int refreshrate);
	int getRefreshRate();
	void setHardwareAntiAliasingCount(int count);
	int getHardwareAntiAliasingCount();
	void setWindowedMode(bool windowedmode);
	bool getWindowedMode();
	void readyToInitialize();
	void close();

	Renderer();
	Renderer(HWND handle);
	Renderer(CoreWindow window);
	Renderer(CoreWindow window, int refreshrate, int hardwareantialiasingcount);
	Renderer(HWND handle, int width, int height, int refreshrate, int hardwareantialiasingcount, bool windowedmode);
	Renderer(vector<string> renderData);
	~Renderer();
};
