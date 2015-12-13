#pragma once
#include<Windows.h>
#include<WindowManager.h>
#include<d3d11.h>
#include<DirectXColors.h>
#include<Model.h>
#include<Shader.h>
#include<d3dcompiler.h>
#include<Camera.h>
#include<Light.h>
#include<Material.h>

using namespace DirectX;

class Renderer
{
private:
	HWND hWnd;
	ID3D11Device *dev;
	ID3D11DeviceContext *devCon;
	IDXGISwapChain *swap;
	ID3D11RenderTargetView *backBuffer;
	ID3D11DepthStencilView *depthStencilView;
	ID3D11Texture2D *depthStencilBuffer;
	ID3D11Buffer *perObjectVertexDataConstantBuffer;
	ID3D11Buffer *perObjectPixelDataConstantBuffer;
	ID3D11Buffer *perLightDataConstantBuffer;
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
	vector<Camera> cameras;
	vector<Light> lights;

	struct perObjectVertexData
	{
		XMMATRIX world;
		XMMATRIX view;
		XMMATRIX WorldViewProjection;	
	}perObjectVertexDataToBeSent;

	struct perObjectPixelData
	{
		XMMATRIX view;
	}perObjectPixelDataToBeSent;

	struct perLightData
	{
		XMVECTOR lightPosition;
		XMVECTOR lightDirection;
		XMVECTOR lightColor;
		int lightType;
	}perLightDataToBeSent;

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
	void loadAllMaterials();
	ID3D11Device **getDevice();

	vector<VertexShader> getVertexShaders();
	vector<PixelShader> getPixelShaders();
	vector<Texture> textures;
	vector<Material> materials;
	vector<Model*> getModels();
	void setVertexShaders(vector<VertexShader> toSet);

	void add(Model* toAdd);
	void add(VertexShader toAdd);
	void add(PixelShader toAdd);
	void add(Camera *toAdd);
	void add(Light toAdd);
	void add(Texture toAdd);
	void add(Material toAdd);

	Renderer();
	Renderer(HWND handle);
	Renderer(CoreWindow window);
	Renderer(CoreWindow window, int refreshrate, int hardwareantialiasingcount);
	Renderer(HWND handle, int width, int height, int refreshrate, int hardwareantialiasingcount, bool windowedmode);
	Renderer(vector<string> renderData);
	~Renderer();
};
