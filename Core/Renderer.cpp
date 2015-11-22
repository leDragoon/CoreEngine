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
		devCon->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
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
	
	for (unsigned int i = 0; i < models.size(); i++)
	{

		if (models[i]->getVertexShaderCode() != currentVertexShader)
		{
			devCon->VSSetShader(*vertexShaders[models[i]->getVertexShaderCode()].getVertexShader(), NULL, NULL);
		}

		if (models[i]->getPixelShaderCode() != currentPixelShader)
		{
			devCon->PSSetShader(*pixelShaders[models[i]->getPixelShaderCode()].getPixelShader(), NULL, NULL);
		}

		devCon->IASetInputLayout(*vertexShaders[models[i]->getVertexShaderCode()].getInputLayout());
		devCon->IASetVertexBuffers(0, 1, models[i]->getVertexBuffer(), (UINT*)sizeof(Vertex), 0);
		devCon->Draw(sizeof(models[i]->getVertexBuffer()) / sizeof(Vertex), 0);
	}

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

	for (unsigned int i = 0; i < vertexShaders.size(); i++)
	{
		vertexShaders[i].close();
	}

	for (unsigned int i = 0; i < pixelShaders.size(); i++)
	{
		pixelShaders[i].close();
	}

	for (unsigned int i = 0; i < models.size(); i++)
	{
		models[i]->close();
	}
}

void Renderer::loadAllModels()
{
	for (unsigned int i = 0; i < models.size(); i++)
	{
		if (!models[i]->getIsInitialized())
		{
			D3D11_BUFFER_DESC bDesc;
			bDesc.Usage = D3D11_USAGE_DEFAULT;
			bDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
			bDesc.ByteWidth = sizeof(Vertex) * models[i]->getVertices()->size();
			bDesc.CPUAccessFlags = NULL;
			bDesc.MiscFlags = NULL;
			bDesc.StructureByteStride = NULL;

			D3D11_SUBRESOURCE_DATA vBufferData;
			vBufferData.pSysMem = models[i]->getVertices()->data();
			vBufferData.SysMemPitch = NULL;
			vBufferData.SysMemSlicePitch = NULL;

			if (dev->CreateBuffer(&bDesc, &vBufferData, models[i]->getVertexBuffer()) != S_OK)
			{
				MessageBox(NULL, ("Could not create model: " + models[i]->getFilePath()).c_str(), "Model Creation Error", MB_ICONERROR | MB_OK);
				exit(0);
			}
		}
	}
}

void Renderer::loadAllShaders() 
{
	D3D11_INPUT_ELEMENT_DESC vertexLayoutDesc[] = { 
	{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "UV", 0, DXGI_FORMAT_R32G32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 } };

	for (unsigned int i = 0; i < vertexShaders.size(); i++)
	{
		if (!vertexShaders[i].getIsInitialized())
		{
			ID3D11VertexShader *vs;
			ID3DBlob *shaderCode;
			ID3DBlob *shaderCompilationErrors;
			
			string fpath = vertexShaders[i].getFilePath();
			std::wstring path;
			path.assign(fpath.begin(), fpath.end());

			D3DCompileFromFile(path.c_str(), NULL, NULL, "main", "vs_5_0", NULL, NULL, &shaderCode, &shaderCompilationErrors);

			if (shaderCompilationErrors)
			{
				MessageBox(NULL, ("Error compiling shader from file: " + vertexShaders[i].getFilePath()).c_str(), "Shader Compilation Errors", MB_ICONERROR | MB_OK);
				exit(0);
			}

			if (shaderCompilationErrors)
			{
				shaderCompilationErrors->Release();
			}

			if (dev->CreateVertexShader(shaderCode->GetBufferPointer(), shaderCode->GetBufferSize(), NULL, &vs) != S_OK)
			{
				MessageBox(NULL, ("Error creating shader: " + vertexShaders[i].getFilePath()).c_str(), "Shader Creation Error", MB_ICONERROR | MB_OK);
				exit(0);
			}

			if (dev->CreateInputLayout(vertexLayoutDesc, ARRAYSIZE(vertexLayoutDesc), shaderCode->GetBufferPointer(), shaderCode->GetBufferSize(), vertexShaders[i].getInputLayout()) != S_OK)
			{
				MessageBox(NULL, ("Error creating vertex input layout for shader: " + vertexShaders[i].getFilePath()).c_str(), "Shader Creation Error", MB_ICONERROR | MB_OK);
				exit(0);
			}

			vertexShaders[i].setInitialized(true);
			shaderCode->Release();
			vs->Release();
		}
	}

	for (unsigned int i = 0; i < pixelShaders.size(); i++)
	{
		if (!pixelShaders[i].getIsInitialized())
		{
			ID3D11PixelShader *ps;
			ID3DBlob *shaderCode;
			ID3DBlob *shaderCompilationErrors;

			string fpath = pixelShaders[i].getFilePath();
			std::wstring path;
			path.assign(fpath.begin(), fpath.end());

			if(D3DCompileFromFile(path.c_str(), NULL, NULL, "main", "ps_5_0", NULL, NULL, &shaderCode, &shaderCompilationErrors) != S_OK)
			{
				MessageBox(NULL, ("Error compiling shader from file: " + pixelShaders[i].getFilePath()).c_str(), "Shader Compilation Errors", MB_ICONERROR | MB_OK);
				MessageBox(NULL, (char*)shaderCompilationErrors->GetBufferPointer(), "Error", MB_ICONERROR | MB_OK);
				exit(0);
			}
		
			if (shaderCompilationErrors)
			{
				shaderCompilationErrors->Release();
			}

			if (dev->CreatePixelShader(shaderCode->GetBufferPointer(), shaderCode->GetBufferSize(), NULL, &ps) != S_OK)
			{
				MessageBox(NULL, ("Error creating shader: " + pixelShaders[i].getFilePath()).c_str(), "Shader Creation Error", MB_ICONERROR | MB_OK);
				exit(0);
			}

			pixelShaders[i].setInitialized(true);
			shaderCode->Release();
			ps->Release();
		}
	}
}

void Renderer::add(Model* toAdd)
{
	for (unsigned int i = 0; i < vertexShaders.size(); i++)
	{
		if (toAdd->getVertexShaderName() == vertexShaders[i].getName())
		{
			toAdd->setVertexShader(i);
		}
	}

	for (unsigned int i = 0; i < pixelShaders.size(); i++)
	{
		if (toAdd->getPixelShaderName() == pixelShaders[i].getName())
		{
			toAdd->setPixelShader(i);
		}
	}

	models.push_back(toAdd);
}

void Renderer::add(VertexShader toAdd)
{
	vertexShaders.push_back(toAdd);
}

void Renderer::add(PixelShader toAdd)
{
	pixelShaders.push_back(toAdd);
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

