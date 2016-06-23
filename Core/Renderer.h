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
#include<DirectXTex.h>
#include<string>
#include<Input.h>
#include<ctime>
#include<UserInterface.h>

using namespace DirectX;

class Renderer
{
private:
	HWND hWnd = NULL;
	ID3D11Device *dev = NULL;
	ID3D11DeviceContext *devCon = NULL;
	IDXGISwapChain *swap = NULL;
	ID3D11RenderTargetView *backBuffer = NULL;
	ID3D11RenderTargetView *renderBuffer = NULL;
	ID3D11DepthStencilView *depthStencilView = NULL;
	ID3D11Buffer *perObjectVertexDataConstantBuffer = NULL;
	ID3D11Buffer *perObjectPixelDataConstantBuffer = NULL;
	ID3D11Buffer *perLightDataConstantBuffer = NULL;
	ID3D11DepthStencilState *depthDisabledState = NULL;
	ID3D11DepthStencilState *normalDepthState = NULL;
	ID3D11Texture2D *presentTexture = NULL;
	ID3D11Texture2D *backBufferTex = NULL;
	ID3D11ShaderResourceView *renderTexture = NULL;
	float deltaTime = 0.0f;
	float timeOld = 0.0f;
	int outputWidth = 1;
	int outputHeight = 1;
	int refreshRate = 60;
	int hardwareAntiAliasingCount = 0;
	int backgroundTexture = 0;
	BOOL fullScreenMode = false;
	bool canBeInitialized = false;
	vector<Model*> models;
	void resize();
	vector<VertexShader> vertexShaders;
	vector<PixelShader> pixelShaders;
	int currentVertexShader = -1;
	int currentPixelShader = -1;
	vector<Camera*> cameras;
	vector<Light> lights;
	vector<VertexShader> getVertexShaders();
	vector<PixelShader> getPixelShaders();
	vector<Texture> textures;
	vector<Material> materials;
	vector<Model*> getModels();
	GuiManager guiManager;
	GuiElement mouseCursor;

	struct perObjectVertexData
	{
		XMMATRIX world;
		XMMATRIX view;
		XMMATRIX WorldViewProjection;	
	}perObjectVertexDataToBeSent;

	struct perObjectPixelData
	{
		XMMATRIX view;
		XMVECTOR cameraPosition;
		XMVECTOR viewDirection;
	}perObjectPixelDataToBeSent;

	struct perLightData
	{
		XMVECTOR lightPosition;
		XMVECTOR lightDirection;
		XMVECTOR lightColor;
		int lightType;
	}perLightDataToBeSent;

	wstring stringtowstring(const string &str);
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
	BOOL getWindowedMode();
	void setBackGroundCubeMap(string textureName);
	string getBackGroundCubeMap();
	void readyToInitialize();
	void close();
	void loadAllModels();
	void loadAllShaders();
	void loadAllMaterials();
	void captureLightProbe(int resolution, XMFLOAT3 position, string pathToSave);
	void convolveLightProbe(string path);
	ID3D11Device **getDevice();
	Model *quadModel;
	void setVertexShaders(vector<VertexShader> toSet);
	float getDeltaTime();
	Model* getObject(string name);
	void setQuadModel(Model* toSet);
	GuiManager *getGuiManager();
	void updateGuiTextures();

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
