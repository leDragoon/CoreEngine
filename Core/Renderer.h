#pragma once
#include<Windows.h>
#include<WindowManager.h>
#include<d3d11.h>
#include<DirectXColors.h>
#include<Model.h>
#include<Shader.h>
#include<d3dcompiler.h>

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
	vector<Model*> models;
	void resize();
	vector<VertexShader> vertexShaders;
	vector<PixelShader> pixelShaders;
	int currentVertexShader;
	int currentPixelShader;
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
	void loadAllModels();
	void loadAllShaders();
	vector<VertexShader> getVertexShaders();
	vector<PixelShader> getPixelShaders();
	vector<Model*> getModels();
	void setVertexShaders(vector<VertexShader> toSet);

	void add(Model* toAdd);
	void add(VertexShader toAdd);
	void add(PixelShader toAdd);

	Renderer();
	Renderer(HWND handle);
	Renderer(CoreWindow window);
	Renderer(CoreWindow window, int refreshrate, int hardwareantialiasingcount);
	Renderer(HWND handle, int width, int height, int refreshrate, int hardwareantialiasingcount, bool windowedmode);
	Renderer(vector<string> renderData);
	~Renderer();
};
