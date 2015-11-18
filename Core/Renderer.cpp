#include "Renderer.h"


void Renderer::init()
{
	if (canBeInitialized)
	{
		DXGI_SWAP_CHAIN_DESC swapDesc;

		DXGI_RATIONAL rRate = { (UINT)refreshRate, (UINT)1 };

		ZeroMemory(&swapDesc, sizeof(DXGI_SWAP_CHAIN_DESC));
		swapDesc.BufferCount = 1;
		swapDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		swapDesc.BufferDesc.Width = outputWidth;
		swapDesc.BufferDesc.Height = outputHeight;
		swapDesc.BufferDesc.RefreshRate = rRate;
		swapDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		swapDesc.OutputWindow = hWnd;
		swapDesc.SampleDesc.Count = hardwareAntiAliasingCount;
		swapDesc.Windowed = windowedMode;
		swapDesc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

		D3D11CreateDeviceAndSwapChain(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, NULL, NULL, NULL, D3D11_SDK_VERSION, &swapDesc, &swap, &dev, NULL, &devCon);

		if (!dev)
		{
			MessageBox(NULL, "Renderer could not be initialized - D3D11CreateDeviceAndSwapChain failed", "Render Init Error", MB_OK | MB_ICONERROR);
			exit(0);
		}

		ID3D11Texture2D *backBufferTex;
		swap->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&backBufferTex);
		dev->CreateRenderTargetView(backBufferTex, NULL, &backBuffer);
		backBufferTex->Release();
		devCon->OMSetRenderTargets(1, &backBuffer, NULL);
		resize();
	}

	else
	{
		MessageBox(NULL, "Insufficient data for renderer initialization", "Render Init Error", MB_ICONERROR | MB_OK);
		exit(0);
	}
}

void Renderer::render()
{
	devCon->ClearRenderTargetView(backBuffer, DirectX::Colors::Black);
	


	swap->Present(0, 0);
}


void Renderer::setWidth(int width)
{
	outputWidth = width;
	resize();
}

void Renderer::setHeight(int height)
{
	outputHeight = height;
	resize();
}

void Renderer::setSize(vector2i size)
{
	outputWidth = size.x;
	outputHeight = size.y;
	resize();
}

void Renderer::resize(int width, int height)
{
	outputWidth = width;
	outputHeight = height;
	resize();
}

void Renderer::resize()
{
	D3D11_VIEWPORT viewPort;
	ZeroMemory(&viewPort, sizeof(D3D11_VIEWPORT));
	viewPort.TopLeftX = 0;
	viewPort.TopLeftY = 0;
	viewPort.Width = (FLOAT)outputWidth;
	viewPort.Height = (FLOAT)outputHeight;

	if (devCon)
	{
		devCon->RSSetViewports(1, &viewPort);
	}
}


vector2i Renderer::getSize()
{
	return vector2i(outputWidth, outputHeight);
}

void Renderer::setRefreshRate(int refreshrate)
{
	refreshRate = refreshrate;
}

int Renderer::getRefreshRate()
{
	return refreshRate;
}

void Renderer::setHardwareAntiAliasingCount(int count)
{
	hardwareAntiAliasingCount = count;
}

int Renderer::getHardwareAntiAliasingCount()
{
	return hardwareAntiAliasingCount;
}

void Renderer::setWindowedMode(bool windowedmode)
{
	windowedMode = windowedmode;
}

bool Renderer::getWindowedMode()
{
	return windowedMode;
}

void Renderer::readyToInitialize()
{
	canBeInitialized = true;
}

void Renderer::close()
{
	swap->SetFullscreenState(FALSE, NULL);

	dev->Release();
	devCon->Release();
	swap->Release();
	backBuffer->Release();
}

Renderer::Renderer()
{
	hWnd = NULL;
	outputWidth = 640;
	outputHeight = 480;
	refreshRate = 60;
	hardwareAntiAliasingCount = 1;
	windowedMode = true;
	canBeInitialized = false;
}

Renderer::Renderer(HWND handle)
{
	hWnd = handle;
	outputWidth = 640;
	outputHeight = 480;
	refreshRate = 60;
	hardwareAntiAliasingCount = 1;
	windowedMode = true;
	canBeInitialized = true;
}

Renderer::Renderer(CoreWindow window)
{
	hWnd = window.getHandle();
	outputWidth = window.getWindowSize().x;
	outputHeight = window.getWindowSize().y;
	refreshRate = 60;
	hardwareAntiAliasingCount = 1;
	windowedMode = window.getWindowedMode();
	canBeInitialized = true;
}

Renderer::Renderer(CoreWindow window, int refreshrate, int hardwareantialiasingcount)
{
	hWnd = window.getHandle();
	outputWidth = window.getWindowSize().x;
	outputHeight = window.getWindowSize().y;
	refreshRate = 60;
	hardwareAntiAliasingCount = 1;
	windowedMode = window.getWindowedMode();
	canBeInitialized = true;
}

Renderer::Renderer(HWND handle, int width, int height, int refreshrate, int hardwareantialiasingcount, bool windowedmode)
{
	hWnd = handle;
	outputWidth = width;
	outputHeight = height;
	refreshRate = refreshrate;
	hardwareAntiAliasingCount = hardwareantialiasingcount;
	windowedMode = windowedMode;
	canBeInitialized = true;
}

Renderer::Renderer(vector<string> renderData)
{

}

Renderer::~Renderer()
{
	
}

