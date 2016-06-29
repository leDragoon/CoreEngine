#include "Renderer.h"

wstring Renderer::stringtowstring(const string &str)
{
	int size_needed = MultiByteToWideChar(CP_UTF8, 0, &str[0], (int)str.size(), NULL, 0);
	wstring toReturn(size_needed, 0);
	MultiByteToWideChar(CP_UTF8, 0, &str[0], (int)str.size(), &toReturn[0], size_needed);
	return toReturn;
}

void Renderer::init()
{
	if (canBeInitialized)
	{
		DXGI_SWAP_CHAIN_DESC swapDesc;

		DXGI_RATIONAL rRate = { (UINT)refreshRate, (UINT)1 };

		ZeroMemory(&swapDesc, sizeof(DXGI_SWAP_CHAIN_DESC));
		swapDesc.BufferCount = 1;
		swapDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM_SRGB;
		swapDesc.BufferDesc.Width = outputWidth - 20;
		swapDesc.BufferDesc.Height = outputHeight;
		swapDesc.BufferDesc.RefreshRate = rRate;
		swapDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		swapDesc.OutputWindow = hWnd;
		swapDesc.SampleDesc.Count = hardwareAntiAliasingCount;
		swapDesc.SampleDesc.Quality = 0;

		if (fullScreenMode == TRUE)
		{
			swapDesc.Windowed = FALSE;
		}
		else
		{
			swapDesc.Windowed = TRUE;
		}
		
		if(D3D11CreateDeviceAndSwapChain(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, NULL, NULL, NULL, D3D11_SDK_VERSION, &swapDesc, &swap, &dev, NULL, &devCon) != S_OK)
		{
			MessageBox(NULL, "Renderer could not be initialized - D3D11CreateDeviceAndSwapChain failed", "Render Init Error", MB_OK | MB_ICONERROR);
			exit(0);
		}

		ID3D11Texture2D *depthStencilBuffer = NULL;

		D3D11_TEXTURE2D_DESC depthStencilDesc;
		ZeroMemory(&depthStencilDesc, sizeof(D3D11_TEXTURE2D_DESC));
		depthStencilDesc.Width = outputWidth;
		depthStencilDesc.Height = outputHeight;
		depthStencilDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
		depthStencilDesc.MipLevels = 1;
		depthStencilDesc.ArraySize = 1;
		depthStencilDesc.SampleDesc.Count = 1;
		depthStencilDesc.SampleDesc.Quality = 0;
		depthStencilDesc.Usage = D3D11_USAGE_DEFAULT;
		depthStencilDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;

		dev->CreateTexture2D(&depthStencilDesc, NULL, &depthStencilBuffer);
		dev->CreateDepthStencilView(depthStencilBuffer, NULL, &depthStencilView);
		depthStencilBuffer->Release();

		D3D11_BUFFER_DESC perObjectVertexDataBufferDesc;
		ZeroMemory(&perObjectVertexDataBufferDesc, sizeof(D3D11_BUFFER_DESC));
		perObjectVertexDataBufferDesc.Usage = D3D11_USAGE_DEFAULT;
		perObjectVertexDataBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		perObjectVertexDataBufferDesc.ByteWidth = sizeof(perObjectVertexData);

		if (dev->CreateBuffer(&perObjectVertexDataBufferDesc, NULL, &perObjectVertexDataConstantBuffer) != S_OK)
		{
			MessageBox(NULL, "Could not create per object vertex data constant buffer", "Buffer creation error", MB_ICONERROR | MB_OK);
			exit(0);
		}

		D3D11_BUFFER_DESC perObjectPixelDataBufferDesc;
		ZeroMemory(&perObjectPixelDataBufferDesc, sizeof(D3D11_BUFFER_DESC));
		perObjectPixelDataBufferDesc.Usage = D3D11_USAGE_DEFAULT;
		perObjectPixelDataBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		perObjectPixelDataBufferDesc.ByteWidth = sizeof(perObjectPixelData);

		if (dev->CreateBuffer(&perObjectPixelDataBufferDesc, NULL, &perObjectPixelDataConstantBuffer) != S_OK)
		{
			MessageBox(NULL, "Could not create per object pixel data constant buffer", "Buffer creation error", MB_ICONERROR | MB_OK);
			exit(0);
		}

		D3D11_BUFFER_DESC perLightBufferDesc;
		ZeroMemory(&perLightBufferDesc, sizeof(D3D11_BUFFER_DESC));
		perLightBufferDesc.Usage = D3D11_USAGE_DEFAULT;
		perLightBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		perLightBufferDesc.ByteWidth = sizeof(perLightData);

		if (dev->CreateBuffer(&perLightBufferDesc, NULL, &perLightDataConstantBuffer) != S_OK)
		{
			MessageBox(NULL, "Could not create per light data constant buffer", "Buffer creation error", MB_ICONERROR | MB_OK);
			exit(0);
		}

		D3D11_BUFFER_DESC textBufferDesc;
		ZeroMemory(&textBufferDesc, sizeof(D3D11_BUFFER_DESC));
		textBufferDesc.Usage = D3D11_USAGE_DEFAULT;
		textBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		textBufferDesc.ByteWidth = sizeof(textData);

		if (dev->CreateBuffer(&textBufferDesc, NULL, &perTextDataConstantBuffer) != S_OK)
		{
			MessageBox(NULL, "Could not create text data constant buffer", "Buffer creation error", MB_ICONERROR | MB_OK);
			exit(0);
		}

		D3D11_DEPTH_STENCIL_DESC normalDesc;
		ZeroMemory(&normalDesc, sizeof(D3D11_DEPTH_STENCIL_DESC));

		if (dev->CreateDepthStencilState(&normalDesc, &normalDepthState) != S_OK)
		{
			MessageBox(NULL, "Could not create depth stencil state", "Initialization Error", MB_ICONERROR | MB_OK);
			exit(0);
		}

		D3D11_DEPTH_STENCIL_DESC depthDisabledDesc;
		ZeroMemory(&depthDisabledDesc, sizeof(D3D11_DEPTH_STENCIL_DESC));
		depthDisabledDesc.DepthEnable = false;

		if (dev->CreateDepthStencilState(&depthDisabledDesc, &depthDisabledState) != S_OK)
		{
			MessageBox(NULL, "Could not create depth stencil state", "Initialization Error", MB_ICONERROR | MB_OK);
			exit(0);
		}

		swap->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&backBufferTex);
		dev->CreateRenderTargetView(backBufferTex, NULL, &backBuffer);
	
		D3D11_TEXTURE2D_DESC td;
		ZeroMemory(&td, sizeof(D3D11_TEXTURE2D_DESC));
		backBufferTex->GetDesc(&td);
		td.BindFlags = D3D11_BIND_SHADER_RESOURCE | D3D11_BIND_RENDER_TARGET;
		
		if (dev->CreateTexture2D(&td, NULL, &presentTexture) != S_OK)
		{
			MessageBox(NULL, "Could not create staging texture for rendering", "Renderer Init Error", MB_ICONERROR | MB_OK);
			exit(0);
		}

		if (dev->CreateShaderResourceView(presentTexture, NULL, &renderTexture) != S_OK)
		{
			MessageBox(NULL, "Could not create staging shader resource for rendering", "Renderer Init Error", MB_ICONERROR | MB_OK);
			exit(0);
		}

		if (dev->CreateRenderTargetView(presentTexture, NULL, &renderBuffer) != S_OK)
		{
			MessageBox(NULL, "Could not create staging render target for rendering", "Renderer Init Error", MB_ICONERROR | MB_OK);
			exit(0);
		}

		devCon->OMSetRenderTargets(1, &backBuffer, depthStencilView);
		devCon->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

		devCon->VSSetConstantBuffers(0, 1, &perObjectVertexDataConstantBuffer);
		devCon->PSSetConstantBuffers(1, 1, &perObjectPixelDataConstantBuffer);


		backBufferTex->Release();
		resize();
		int i = 0;
		isInitialized = true;
	}

	else
	{
		MessageBox(NULL, "Insufficient data for renderer initialization", "Render Init Error", MB_ICONERROR | MB_OK);
		exit(0);
	}
}

void Renderer::render()
{
	time_t time = clock();
	deltaTime = (time - timeOld) / 1000;
	timeOld = time;

	devCon->OMSetRenderTargets(1, &renderBuffer, depthStencilView);

	for (unsigned int i = 0; i < cameras.size(); i++)
	{
		devCon->ClearDepthStencilView(depthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0, 0);
		devCon->OMSetDepthStencilState(depthDisabledState, NULL);

		for (unsigned int j = 0; j < models.size(); j++)
		{
			perObjectVertexDataToBeSent.WorldViewProjection = XMMatrixTranspose(XMLoadFloat4x4(&cameras[i]->getProjectionMatrix()));
			perObjectVertexDataToBeSent.view = XMMatrixTranspose(XMLoadFloat4x4(&cameras[i]->getViewMatrix()));
			perObjectVertexDataToBeSent.world = XMMatrixTranspose(XMLoadFloat4x4(&models[j]->getWorldMatrix()));
			perObjectPixelDataToBeSent.view = XMMatrixTranspose(XMLoadFloat4x4(&cameras[i]->getViewMatrix()));
			perObjectPixelDataToBeSent.cameraPosition = XMVectorSet(cameras[i]->getPosition().x, cameras[i]->getPosition().y, cameras[i]->getPosition().z, 1.0f);
			devCon->UpdateSubresource(perObjectVertexDataConstantBuffer, NULL, NULL, &perObjectVertexDataToBeSent, NULL, NULL);
			devCon->UpdateSubresource(perObjectPixelDataConstantBuffer, NULL, NULL, &perObjectPixelDataToBeSent, NULL, NULL);

			int mCode = models[j]->getMaterialCode();
			
			if (materials[mCode].getAlbedoTextureCode() >= 0)
			{
				ID3D11ShaderResourceView* const v = textures[materials[mCode].getAlbedoTextureCode()].getResource();
				devCon->PSSetShaderResources(0, 1, &v);
			}

			if (materials[mCode].getRoughnessTextureCode() >= 0)
			{
				ID3D11ShaderResourceView* const v = textures[materials[mCode].getRoughnessTextureCode()].getResource();
				devCon->PSSetShaderResources(1, 1, &v);
			}

			if (materials[mCode].getMetalnessTextureCode() >= 0)
			{
				ID3D11ShaderResourceView* const v = textures[materials[mCode].getMetalnessTextureCode()].getResource();
				devCon->PSSetShaderResources(2, 1, &v);
			}

			if (materials[mCode].getNormalTextureCode() >= 0)
			{
				ID3D11ShaderResourceView* const v = textures[materials[mCode].getNormalTextureCode()].getResource();
				devCon->PSSetShaderResources(3, 1, &v);
			}

			ID3D11ShaderResourceView* const v = textures[backgroundTexture].getResource();
			devCon->PSSetShaderResources(4, 1, &v);

			unsigned int vSize = sizeof(Vertex);
			unsigned int offset = 0;
			devCon->IASetVertexBuffers(0, 1, models[j]->getVertexBuffer(), &vSize, &offset);
			devCon->IASetIndexBuffer(*models[j]->getIndexBuffer(), DXGI_FORMAT_R32_UINT, 0);

			if (models[j]->getVertexShaderCode() != currentVertexShader)
			{
				devCon->VSSetShader(*vertexShaders[models[j]->getVertexShaderCode()].getVertexShader(), NULL, NULL);
				devCon->IASetInputLayout(*vertexShaders[models[j]->getVertexShaderCode()].getInputLayout());
				currentVertexShader = models[j]->getVertexShaderCode();
			}

			if (models[j]->getPixelShaderCode() != currentPixelShader)
			{
				devCon->PSSetShader(*pixelShaders[models[j]->getPixelShaderCode()].getPixelShader(), NULL, NULL);
				currentPixelShader = models[j]->getPixelShaderCode();
			}

			for (unsigned int k = 0; k < lights.size(); k++)
			{
				perLightDataToBeSent.lightPosition = XMVectorSet(lights[k].getLightPosition().x, lights[k].getLightPosition().y, lights[k].getLightPosition().z, 1.0);
				perLightDataToBeSent.lightDirection = XMVectorSet(lights[k].getLightDirection().x, lights[k].getLightDirection().y, lights[k].getLightDirection().z, 1.0);
				perLightDataToBeSent.lightColor = XMVectorSet(lights[k].getLightColor().x, lights[k].getLightColor().y, lights[k].getLightColor().z, 1.0);
				perLightDataToBeSent.lightType = lights[k].getLightType();
				devCon->UpdateSubresource(perLightDataConstantBuffer, NULL, NULL, &perLightDataToBeSent, NULL, NULL);
				devCon->PSSetConstantBuffers(2, 1, &perLightDataConstantBuffer);

				devCon->DrawIndexed(models[j]->getNumberOfIndices(), 0, 0);
			}

			if (j == 0)
			{
				devCon->OMSetDepthStencilState(normalDepthState, NULL);
			}
		}
	}

	quadModel->setRotation(XMFLOAT3(0.0f, 0.0f, 0.0f));

	devCon->OMSetRenderTargets(1, &backBuffer, depthStencilView);
	devCon->OMSetDepthStencilState(depthDisabledState, NULL);
	devCon->VSSetShader(*vertexShaders[quadModel->getVertexShaderCode()].getVertexShader(), NULL, NULL);
	devCon->IASetInputLayout(*vertexShaders[quadModel->getVertexShaderCode()].getInputLayout());
	currentVertexShader = quadModel->getVertexShaderCode();
	devCon->PSSetShader(*pixelShaders[postFXShader].getPixelShader(), NULL, NULL);
	currentPixelShader = postFXShader;
	unsigned int vSize = sizeof(Vertex);
	unsigned int offset = 0;
	devCon->IASetVertexBuffers(0, 1, quadModel->getVertexBuffer(), &vSize, &offset);
	devCon->IASetIndexBuffer(*quadModel->getIndexBuffer(), DXGI_FORMAT_R32_UINT, 0);

	for (unsigned int i = 0; i < guiManager.getCurrentGuiLayout()->windows.size(); i++)
	{
		GuiWindow window = guiManager.getCurrentGuiLayout()->windows[i];

		if (window.getIsVisible())
		{
			if (window.getCurrentTexture()->getResource() == NULL)
			{
				ID3D11ShaderResourceView* const v = renderTexture;
				devCon->PSSetShaderResources(0, 1, &v);
			}

			else
			{
				ID3D11ShaderResourceView* const v = window.getCurrentTexture()->getResource();
				devCon->PSSetShaderResources(0, 1, &v);
			}

			XMFLOAT2 pos = window.getPosition();
			XMFLOAT2 scl = window.getScale();
			quadModel->setPosition(XMFLOAT3(pos.x, pos.y - scl.y, 1.0f));
			quadModel->setScale(XMFLOAT3(scl.x, scl.y, 1.0f));
			perObjectVertexDataToBeSent.world = XMMatrixTranspose(XMLoadFloat4x4(&quadModel->getWorldMatrix()));
			devCon->UpdateSubresource(perObjectVertexDataConstantBuffer, NULL, NULL, &perObjectVertexDataToBeSent, NULL, NULL);
			devCon->DrawIndexed(quadModel->getNumberOfIndices(), 0, 0);

			for (int j = 0; j < 4; j++)
			{
				quadModel->setRotation(XMFLOAT3(0.0f, 0.0f, 90.0f * j));
				
				if (j == 0)
				{
					ID3D11ShaderResourceView* const v = window.getWindowStyle()->verticalEdge.getResource();
					devCon->PSSetShaderResources(0, 1, &v);
					quadModel->setScale(XMFLOAT3(1.0f, 0.02f, 1.0f));
					quadModel->setPosition(XMFLOAT3(0.0f, 1.0f - 0.02f, 1.0f));
					perObjectVertexDataToBeSent.world = XMMatrixTranspose(XMLoadFloat4x4(&quadModel->getWorldMatrix()));
					devCon->UpdateSubresource(perObjectVertexDataConstantBuffer, NULL, NULL, &perObjectVertexDataToBeSent, NULL, NULL);
					devCon->DrawIndexed(quadModel->getNumberOfIndices(), 0, 0);
				}

				else if(j == 1)
				{
					ID3D11ShaderResourceView* const v = window.getWindowStyle()->verticalEdge.getResource();
					devCon->PSSetShaderResources(0, 1, &v);
					quadModel->setScale(XMFLOAT3(1.0f, 0.02f * ((float)outputHeight / outputWidth), 1.0f));
					quadModel->setPosition(XMFLOAT3(-1.0f + 0.01f, 0.0f, 1.0f));
					perObjectVertexDataToBeSent.world = XMMatrixTranspose(XMLoadFloat4x4(&quadModel->getWorldMatrix()));
					devCon->UpdateSubresource(perObjectVertexDataConstantBuffer, NULL, NULL, &perObjectVertexDataToBeSent, NULL, NULL);
					devCon->DrawIndexed(quadModel->getNumberOfIndices(), 0, 0);
				}

				else if(j == 2)
				{
					ID3D11ShaderResourceView* const v = window.getWindowStyle()->verticalEdge.getResource();
					devCon->PSSetShaderResources(0, 1, &v);
					quadModel->setScale(XMFLOAT3(1.0f, 0.02f, 1.0f));
					quadModel->setPosition(XMFLOAT3(0.0f, -1.0f + 0.02f, 1.0f));
					perObjectVertexDataToBeSent.world = XMMatrixTranspose(XMLoadFloat4x4(&quadModel->getWorldMatrix()));
					devCon->UpdateSubresource(perObjectVertexDataConstantBuffer, NULL, NULL, &perObjectVertexDataToBeSent, NULL, NULL);
					devCon->DrawIndexed(quadModel->getNumberOfIndices(), 0, 0);
				}

				else
				{
					ID3D11ShaderResourceView* const v = window.getWindowStyle()->verticalEdge.getResource();
					devCon->PSSetShaderResources(0, 1, &v);
					quadModel->setScale(XMFLOAT3(1.0f, 0.02f * ((float)outputHeight / outputWidth), 1.0f));
					quadModel->setPosition(XMFLOAT3(1.0f - 0.01f, 0.0f, 1.0f));
					perObjectVertexDataToBeSent.world = XMMatrixTranspose(XMLoadFloat4x4(&quadModel->getWorldMatrix()));
					devCon->UpdateSubresource(perObjectVertexDataConstantBuffer, NULL, NULL, &perObjectVertexDataToBeSent, NULL, NULL);
					devCon->DrawIndexed(quadModel->getNumberOfIndices(), 0, 0);
				}
			}

			quadModel->setRotation(XMFLOAT3(0.0f, 0.0f, 0.0f));

			for (unsigned int j = 0; j < window.getNumberOfHudElements(); j++)
			{
				if (window.getHudElement(j)->getIsVisible() == true)
				{
					ID3D11ShaderResourceView* const v = window.getHudElement(j)->getCurrentTexture()->getResource();
					devCon->PSSetShaderResources(0, 1, &v);
					XMFLOAT2 pos = window.getHudElement(j)->getPosition();
					XMFLOAT2 scl = window.getHudElement(j)->getScale();
					quadModel->setPosition(XMFLOAT3(pos.x, pos.y, 1.0f));
					quadModel->setScale(XMFLOAT3(scl.x, scl.y, 1.0f));
					perObjectVertexDataToBeSent.world = XMMatrixTranspose(XMLoadFloat4x4(&quadModel->getWorldMatrix()));
					devCon->UpdateSubresource(perObjectVertexDataConstantBuffer, NULL, NULL, &perObjectVertexDataToBeSent, NULL, NULL);
					devCon->DrawIndexed(quadModel->getNumberOfIndices(), 0, 0);
				}
			}

			devCon->PSSetShader(*pixelShaders[textShader].getPixelShader(), NULL, NULL);
			currentPixelShader = textShader;
			quadModel->setRotation(XMFLOAT3(0.0f, 0.0f, 90.0f));

			for (unsigned int j = 0; j < window.getNumberOfTextElements(); j++)
			{
				int currentFontSheet = 0;
				ID3D11ShaderResourceView* const v = window.getTextElement(j)->getFont()->getFontSheet(currentFontSheet)->getResource();
				devCon->PSSetShaderResources(0, 1, &v);

				float sumOfPositions = 0;
				for (unsigned int k = 0; k < window.getTextElement(j)->getText().size(); k++)
				{
					GuiTextCharacter character = window.getTextElement(j)->getFont()->getCharacter(window.getTextElement(j)->getText()[k]);
					quadModel->setScale(XMFLOAT3(window.getTextElement(j)->getScale().x * ((float)character.height / 256), window.getTextElement(j)->getScale().y * ((float)outputHeight / outputWidth) * ((float)character.width / 256), 1.0f));

					if (character.fontSheet != currentFontSheet)
					{
						currentFontSheet = character.fontSheet;
						ID3D11ShaderResourceView* const v = window.getTextElement(j)->getFont()->getFontSheet(currentFontSheet)->getResource();
						devCon->PSSetShaderResources(0, 1, &v);
					}

					
					quadModel->setPosition(XMFLOAT3(((window.getTextElement(j)->getPosition().x + sumOfPositions + ((float)character.width / outputWidth)) * (outputWidth / outputHeight)) - 1.0f, window.getTextElement(j)->getPosition().y, 1.0f));
					perObjectVertexDataToBeSent.world = XMMatrixTranspose(XMLoadFloat4x4(&quadModel->getWorldMatrix()));
					devCon->UpdateSubresource(perObjectVertexDataConstantBuffer, NULL, NULL, &perObjectVertexDataToBeSent, NULL, NULL);

					XMFLOAT4 toSend = XMFLOAT4((float)character.xPos, (float)character.yPos, (float)character.width, (float)character.height);
					textDataToBeSent.positionScale = XMLoadFloat4(&toSend);
					devCon->UpdateSubresource(perTextDataConstantBuffer, NULL, NULL, &textDataToBeSent, NULL, NULL);
					devCon->VSSetConstantBuffers(3, 1, &perTextDataConstantBuffer);
					devCon->DrawIndexed(quadModel->getNumberOfIndices(), 0, 0);
					sumOfPositions += ((float)character.width / outputWidth) * ((float)outputWidth / outputHeight);
				}
			}
		}
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
	devCon->OMSetRenderTargets(0, 0, 0);

	if (swap)
	{
		swap->GetFullscreenState(&fullScreenMode, NULL);
		swap->Release();
	}

	if (backBuffer)
	{
		backBuffer->Release();
	}

	if (renderBuffer)
	{
		renderBuffer->Release();
	}

	if (depthStencilView)
	{
		depthStencilView->Release();
	}


	DXGI_SWAP_CHAIN_DESC swapDesc;

	DXGI_RATIONAL rRate = { (UINT)refreshRate, (UINT)1 };

	ZeroMemory(&swapDesc, sizeof(DXGI_SWAP_CHAIN_DESC));
	swapDesc.BufferCount = 1;
	swapDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM_SRGB;
	swapDesc.BufferDesc.Width = outputWidth;
	swapDesc.BufferDesc.Height = outputHeight;
	swapDesc.BufferDesc.RefreshRate = rRate;
	swapDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapDesc.OutputWindow = hWnd;
	swapDesc.SampleDesc.Count = hardwareAntiAliasingCount;
	swapDesc.SampleDesc.Quality = 0;
	if (fullScreenMode == TRUE)
	{
		swapDesc.Windowed = FALSE;
	}
	else
	{
		swapDesc.Windowed = TRUE;
	}
	swapDesc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

	HRESULT hr;

	IDXGIDevice *ddev = nullptr;
	hr = dev->QueryInterface(__uuidof(IDXGIDevice), (void**)&ddev);
	if (hr != S_OK)
	{
		MessageBox(NULL, "Could not resize display area", "Resize error 1", MB_ICONERROR | MB_OK);
		exit(0);
	}
	IDXGIAdapter *ad = nullptr;
	hr = ddev->GetAdapter(&ad);
	if (hr != S_OK)
	{
		MessageBox(NULL, "Could not resize display area", "Resize error 2", MB_ICONERROR | MB_OK);
		exit(0);
	}
	IDXGIFactory *fac = nullptr;
	hr = ad->GetParent(__uuidof(IDXGIFactory), (void**)&fac);
	if (hr != S_OK)
	{
		MessageBox(NULL, "Could not resize display area", "Resize error 3", MB_ICONERROR | MB_OK);
		exit(0);
	}

	hr = fac->CreateSwapChain(dev, &swapDesc, &swap);

	if (hr == DXGI_ERROR_INVALID_CALL)
	{
		MessageBox(NULL, "Could not resize display area2", "Resize error 4", MB_ICONERROR | MB_OK);
		exit(0);
	}

	if (hr != S_OK)
	{
		MessageBox(NULL, "Could not resize display area", "Resize error 4", MB_ICONERROR | MB_OK);
		exit(0);
	}

	ID3D11Texture2D *buffer;

	if (swap->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&buffer) != S_OK)
	{
		MessageBox(NULL, "Could not get back buffer for resizing the display area", "Resize error", MB_ICONERROR | MB_OK);
		exit(0);
	}

	D3D11_TEXTURE2D_DESC td;
	ZeroMemory(&td, sizeof(D3D11_TEXTURE2D_DESC));
	buffer->GetDesc(&td);
	td.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;

	if (dev->CreateRenderTargetView(buffer, NULL, &backBuffer) != S_OK)
	{
		MessageBox(NULL, "Could not create new render target for resizing the display area", "Resize error", MB_ICONERROR | MB_OK);
		exit(0);
	}

	if (dev->CreateTexture2D(&td, NULL, &presentTexture) != S_OK)
	{
		MessageBox(NULL, "Could not create staging texture for rendering", "Renderer Init Error", MB_ICONERROR | MB_OK);
		exit(0);
	}

	if (dev->CreateShaderResourceView(presentTexture, NULL, &renderTexture) != S_OK)
	{
		MessageBox(NULL, "Could not create staging shader resource for rendering", "Renderer Init Error", MB_ICONERROR | MB_OK);
		exit(0);
	}

	if (dev->CreateRenderTargetView(presentTexture, NULL, &renderBuffer) != S_OK)
	{
		MessageBox(NULL, "Could not create staging render target for rendering", "Renderer Init Error", MB_ICONERROR | MB_OK);
		exit(0);
	}

	buffer->Release();

	ID3D11Texture2D *depthStencilBuffer = NULL;
	D3D11_TEXTURE2D_DESC depthStencilDesc;
	ZeroMemory(&depthStencilDesc, sizeof(D3D11_TEXTURE2D_DESC));
	depthStencilDesc.Width = outputWidth;
	depthStencilDesc.Height = outputHeight;
	depthStencilDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	depthStencilDesc.MipLevels = 1;
	depthStencilDesc.ArraySize = 1;
	depthStencilDesc.SampleDesc.Count = 1;
	depthStencilDesc.SampleDesc.Quality = 0;
	depthStencilDesc.Usage = D3D11_USAGE_DEFAULT;
	depthStencilDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;

	dev->CreateTexture2D(&depthStencilDesc, NULL, &depthStencilBuffer);
	dev->CreateDepthStencilView(depthStencilBuffer, NULL, &depthStencilView);

	if (depthStencilBuffer)
	{
		depthStencilBuffer->Release();
	}
	
	devCon->OMSetRenderTargets(1, &backBuffer, depthStencilView);
	
	for (unsigned int i = 0; i < cameras.size(); i++)
	{
		cameras[i]->setRenderDims(outputWidth, outputHeight);
	}
	
	D3D11_VIEWPORT viewPort;
	ZeroMemory(&viewPort, sizeof(D3D11_VIEWPORT));
	viewPort.TopLeftX = 0;
	viewPort.TopLeftY = 0;
	viewPort.Width = (FLOAT)outputWidth;
	viewPort.Height = (FLOAT)outputHeight;
	viewPort.MinDepth = 0.0;
	viewPort.MaxDepth = 1.0;

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
	if (windowedmode == true)
	{
		fullScreenMode = false;
	}
	
	else
	{
		fullScreenMode = true;
	}
}

BOOL Renderer::getWindowedMode()
{
	if (fullScreenMode == false)
	{
		return true;
	}

	else
	{
		return false;
	}
}

void Renderer::setBackGroundCubeMap(string textureName)
{
	for (unsigned int i = 0; i < textures.size(); i++)
	{
		if (textures[i].getName() == textureName)
		{
			backgroundTexture = i;
		}
	}
}

string Renderer::getBackGroundCubeMap()
{
	return textures[backgroundTexture].getName();
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
	renderBuffer->Release();
	depthStencilView->Release();
	perObjectVertexDataConstantBuffer->Release();
	perObjectPixelDataConstantBuffer->Release();
	perLightDataConstantBuffer->Release();
	depthDisabledState->Release();
	normalDepthState->Release();
	presentTexture->Release();
	renderTexture->Release();

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
			D3D11_BUFFER_DESC vbDesc;
			ZeroMemory(&vbDesc, sizeof(D3D11_BUFFER_DESC));
			vbDesc.Usage = D3D11_USAGE_DEFAULT;
			vbDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
			vbDesc.ByteWidth = sizeof(Vertex) * models[i]->getVertices()->size();

			D3D11_BUFFER_DESC ibDesc;
			ZeroMemory(&ibDesc, sizeof(D3D11_BUFFER_DESC));
			ibDesc.Usage = D3D11_USAGE_DEFAULT;
			ibDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
			ibDesc.ByteWidth = sizeof(DWORD) * models[i]->getNumberOfIndices();

			D3D11_SUBRESOURCE_DATA vBufferData;
			ZeroMemory(&vBufferData, sizeof(D3D11_SUBRESOURCE_DATA));
			vBufferData.pSysMem = models[i]->getVertices()->data();

			D3D11_SUBRESOURCE_DATA iBufferData;
			ZeroMemory(&iBufferData, sizeof(D3D11_SUBRESOURCE_DATA));
			iBufferData.pSysMem = models[i]->getIndices()->data();

			if (dev->CreateBuffer(&vbDesc, &vBufferData, models[i]->getVertexBuffer()) != S_OK)
			{
				MessageBox(NULL, ("Could not create model: " + models[i]->getFilePath()).c_str(), "Model Creation Error", MB_ICONERROR | MB_OK);
				exit(0);
			}

			if (dev->CreateBuffer(&ibDesc, &iBufferData, models[i]->getIndexBuffer()) != S_OK)
			{
				MessageBox(NULL, ("Could not create model: " + models[i]->getFilePath()).c_str(), "Model Creation Error", MB_ICONERROR | MB_OK);
				exit(0);
			}

			models[i]->setIsInitialized(true);
			models[i]->getVertices()->erase(models[i]->getVertices()->begin(), models[i]->getVertices()->end());
			models[i]->getIndices()->erase(models[i]->getIndices()->begin(), models[i]->getIndices()->end());
		}
	}

	if (!quadModel->getIsInitialized())
	{
		D3D11_BUFFER_DESC vbDesc;
		ZeroMemory(&vbDesc, sizeof(D3D11_BUFFER_DESC));
		vbDesc.Usage = D3D11_USAGE_DEFAULT;
		vbDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		vbDesc.ByteWidth = sizeof(Vertex) * quadModel->getVertices()->size();

		D3D11_BUFFER_DESC ibDesc;
		ZeroMemory(&ibDesc, sizeof(D3D11_BUFFER_DESC));
		ibDesc.Usage = D3D11_USAGE_DEFAULT;
		ibDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
		ibDesc.ByteWidth = sizeof(DWORD) * quadModel->getNumberOfIndices();

		D3D11_SUBRESOURCE_DATA vBufferData;
		ZeroMemory(&vBufferData, sizeof(D3D11_SUBRESOURCE_DATA));
		vBufferData.pSysMem = quadModel->getVertices()->data();

		D3D11_SUBRESOURCE_DATA iBufferData;
		ZeroMemory(&iBufferData, sizeof(D3D11_SUBRESOURCE_DATA));
		iBufferData.pSysMem = quadModel->getIndices()->data();

		if (dev->CreateBuffer(&vbDesc, &vBufferData, quadModel->getVertexBuffer()) != S_OK)
		{
			MessageBox(NULL, ("Could not create model: " + quadModel->getFilePath()).c_str(), "Model Creation Error", MB_ICONERROR | MB_OK);
			exit(0);
		}

		if (dev->CreateBuffer(&ibDesc, &iBufferData, quadModel->getIndexBuffer()) != S_OK)
		{
			MessageBox(NULL, ("Could not create model: " + quadModel->getFilePath()).c_str(), "Model Creation Error", MB_ICONERROR | MB_OK);
			exit(0);
		}

		quadModel->setIsInitialized(true);
		quadModel->getVertices()->erase(quadModel->getVertices()->begin(), quadModel->getVertices()->end());
		quadModel->getIndices()->erase(quadModel->getIndices()->begin(), quadModel->getIndices()->end());
	}
}

void Renderer::loadAllShaders()
{
	D3D11_INPUT_ELEMENT_DESC vertexLayoutDesc[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TANGENT", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 }
	};

	for (unsigned int i = 0; i < vertexShaders.size(); i++)
	{
		if (!vertexShaders[i].getIsInitialized())
		{
			ID3DBlob *shaderCode;
			ID3DBlob *shaderCompilationErrors;

			string fpath = vertexShaders[i].getFilePath();
			std::wstring path;
			path.assign(fpath.begin(), fpath.end());

			D3DCompileFromFile(path.c_str(), NULL, NULL, "main", "vs_5_0", NULL, NULL, &shaderCode, &shaderCompilationErrors);

			if (shaderCompilationErrors)
			{
				MessageBox(NULL, ("Error compiling shader from file: " + vertexShaders[i].getFilePath()).c_str(), "Shader Compilation Errors", MB_ICONERROR | MB_OK);
				shaderCompilationErrors->Release();
				exit(0);
			}

			if (dev->CreateVertexShader(shaderCode->GetBufferPointer(), shaderCode->GetBufferSize(), NULL, vertexShaders[i].getVertexShader()) != S_OK)
			{
				MessageBox(NULL, ("Error creating shader: " + vertexShaders[i].getFilePath()).c_str(), "Shader Creation Error", MB_ICONERROR | MB_OK);
				exit(0);
			}

			if (dev->CreateInputLayout(vertexLayoutDesc, ARRAYSIZE(vertexLayoutDesc), shaderCode->GetBufferPointer(), shaderCode->GetBufferSize(), vertexShaders[i].getInputLayout()) != S_OK)
			{
				MessageBox(NULL, ("Error creating vertex input layout for shader: " + vertexShaders[i].getFilePath()).c_str(), "Shader Creation Error", MB_ICONERROR | MB_OK);
				exit(0);
			}

			shaderCode->Release();
			vertexShaders[i].setInitialized(true);
		}
	}

	for (unsigned int i = 0; i < pixelShaders.size(); i++)
	{
		if (!pixelShaders[i].getIsInitialized())
		{
			ID3DBlob *shaderCode;
			ID3DBlob *shaderCompilationErrors;

			string fpath = pixelShaders[i].getFilePath();
			std::wstring path;
			path.assign(fpath.begin(), fpath.end());

			if (D3DCompileFromFile(path.c_str(), NULL, NULL, "main", "ps_5_0", NULL, NULL, &shaderCode, &shaderCompilationErrors) != S_OK)
			{
				MessageBox(NULL, ("Error compiling shader from file: " + pixelShaders[i].getFilePath()).c_str(), "Shader Compilation Errors", MB_ICONERROR | MB_OK);
				MessageBox(NULL, (char*)shaderCompilationErrors->GetBufferPointer(), "Error", MB_ICONERROR | MB_OK);
				exit(0);
			}

			if (shaderCompilationErrors)
			{
				shaderCompilationErrors->Release();
			}

			if (dev->CreatePixelShader(shaderCode->GetBufferPointer(), shaderCode->GetBufferSize(), NULL, pixelShaders[i].getPixelShader()) != S_OK)
			{
				MessageBox(NULL, ("Error creating shader: " + pixelShaders[i].getFilePath()).c_str(), "Shader Creation Error", MB_ICONERROR | MB_OK);
				exit(0);
			}

			shaderCode->Release();
			pixelShaders[i].setInitialized(true);
		}

		if (pixelShaders[i].getName() == "postFXPixelShader")
		{
			postFXShader = i;
		}

		else if (pixelShaders[i].getName() == "textShader")
		{
			textShader = i;
		}
	}
}

void Renderer::loadAllMaterials()
{
	for (unsigned int i = 0; i < materials.size(); i++)
	{
		for (unsigned int j = 0; j < materials[i].getTextureNames().size(); j++)
		{
			for (unsigned int k = 0; k < textures.size(); k++)
			{
				if (materials[i].getTextureNames()[j] == textures[k].getName())
				{
					if (materials[i].getTextureUsages()[j] == CORE_TEXTUREUSAGE_ALBEDO)
					{
						materials[i].setAlbedoTextureCode(k);
					}

					else if(materials[i].getTextureUsages()[j] == CORE_TEXTUREUSAGE_ROUGHNESS)
					{
						materials[i].setRoughnessTextureCode(k);
					}

					else if (materials[i].getTextureUsages()[j] == CORE_TEXTUREUSAGE_METALIC)
					{
						materials[i].setMetalnessTextureCode(k);
					}

					else if (materials[i].getTextureUsages()[j] == CORE_TEXTUREUSAGE_NORMAL)
					{
						materials[i].setNormalTextureCode(k);
					}
				}
			}
		}
	}
}

void Renderer::captureLightProbe(int resolution, XMFLOAT3 position, string pathToSave)
{
	int outwo = outputWidth;
	int outho = outputHeight;

	outputWidth = resolution;
	outputHeight = resolution;
	resize();

	size_t slicepitch = 0;
	size_t rowpitch = 0;

	ComputePitch(DXGI_FORMAT_R8G8B8A8_UNORM_SRGB, resolution, resolution, rowpitch, slicepitch);

	uint8_t *imagedata1 = new uint8_t[slicepitch];
	ZeroMemory(imagedata1, slicepitch);
	uint8_t *imagedata2 = new uint8_t[slicepitch];
	ZeroMemory(imagedata2, slicepitch);
	uint8_t *imagedata3 = new uint8_t[slicepitch];
	ZeroMemory(imagedata3, slicepitch);
	uint8_t *imagedata4 = new uint8_t[slicepitch];
	ZeroMemory(imagedata4, slicepitch);
	uint8_t *imagedata5 = new uint8_t[slicepitch];
	ZeroMemory(imagedata5, slicepitch);
	uint8_t *imagedata6 = new uint8_t[slicepitch];
	ZeroMemory(imagedata6, slicepitch);

	ID3D11Texture2D *face1t;
	ID3D11Texture2D *face2t;
	ID3D11Texture2D *face3t;
	ID3D11Texture2D *face4t;
	ID3D11Texture2D *face5t;
	ID3D11Texture2D *face6t;
	ID3D11Texture2D *face1tb;
	ID3D11Texture2D *face2tb;
	ID3D11Texture2D *face3tb;
	ID3D11Texture2D *face4tb;
	ID3D11Texture2D *face5tb;
	ID3D11Texture2D *face6tb;

	D3D11_TEXTURE2D_DESC td;
	ZeroMemory(&td, sizeof(D3D11_TEXTURE2D_DESC));
	td.ArraySize = 1;
	td.MipLevels = 1;
	td.Width = resolution;
	td.Height = resolution;
	td.Format = DXGI_FORMAT_R8G8B8A8_UNORM_SRGB;
	td.SampleDesc.Count = 1;
	td.Usage = D3D11_USAGE_STAGING;
	td.CPUAccessFlags = D3D11_CPU_ACCESS_READ;
	td.MiscFlags = 0;
	td.BindFlags = NULL;

	if (dev->CreateTexture2D(&td, NULL, &face1t) != S_OK)
	{
		MessageBox(NULL, "Could not create staging texture for light probe capture", "Light probe capture error", MB_ICONERROR | MB_OK);
		exit(0);
	}

	if (dev->CreateTexture2D(&td, NULL, &face2t) != S_OK)
	{
		MessageBox(NULL, "Could not create staging texture for light probe capture", "Light probe capture error", MB_ICONERROR | MB_OK);
		exit(0);
	}

	if (dev->CreateTexture2D(&td, NULL, &face3t) != S_OK)
	{
		MessageBox(NULL, "Could not create staging texture for light probe capture", "Light probe capture error", MB_ICONERROR | MB_OK);
		exit(0);
	}

	if (dev->CreateTexture2D(&td, NULL, &face4t) != S_OK)
	{
		MessageBox(NULL, "Could not create staging texture for light probe capture", "Light probe capture error", MB_ICONERROR | MB_OK);
		exit(0);
	}

	if (dev->CreateTexture2D(&td, NULL, &face5t) != S_OK)
	{
		MessageBox(NULL, "Could not create staging texture for light probe capture", "Light probe capture error", MB_ICONERROR | MB_OK);
		exit(0);
	}

	if (dev->CreateTexture2D(&td, NULL, &face6t) != S_OK)
	{
		MessageBox(NULL, "Could not create staging texture for light probe capture", "Light probe capture error", MB_ICONERROR | MB_OK);
		exit(0);
	}


	XMFLOAT3 camposold = cameras[0]->getPosition();
	XMFLOAT3 camrotold = cameras[0]->getRotation();
	float camfovold = cameras[0]->getFieldOfView();
	cameras[0]->setFieldOfView(90.0f);
	cameras[0]->setPosition(position);
	cameras[0]->setRotation(XMFLOAT3(0.0f, 0.0f, 0.0f));
	render();
	if (swap->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**> (&face1tb)) != S_OK)
	{
		MessageBox(NULL, "Could not get texture data from camera for lightprobe capture", "Light probe capture error", MB_ICONERROR | MB_OK);
		exit(0);
	}
	devCon->CopyResource(face1t, face1tb);
	cameras[0]->setRotation(XMFLOAT3(0.0f, 90.0f, 0.0f));
	render();
	if (swap->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**> (&face2tb)) != S_OK)
	{
		MessageBox(NULL, "Could not get texture data from camera for lightprobe capture", "Light probe capture error", MB_ICONERROR | MB_OK);
		exit(0);
	}
	devCon->CopyResource(face2t, face2tb);
	cameras[0]->setRotation(XMFLOAT3(0.0f, 180.0f, 0.0f));
	render();
	if (swap->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**> (&face3tb)) != S_OK)
	{
		MessageBox(NULL, "Could not get texture data from camera for lightprobe capture", "Light probe capture error", MB_ICONERROR | MB_OK);
		exit(0);
	}
	devCon->CopyResource(face3t, face3tb);
	cameras[0]->setRotation(XMFLOAT3(0.0f, 270.0f, 0.0f));
	render();
	if (swap->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**> (&face4tb)) != S_OK)
	{
		MessageBox(NULL, "Could not get texture data from camera for lightprobe capture", "Light probe capture error", MB_ICONERROR | MB_OK);
		exit(0);
	}
	devCon->CopyResource(face4t, face4tb);
	cameras[0]->setRotation(XMFLOAT3(270.0f, 180.0f, 0.0f));
	render();
	if (swap->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**> (&face5tb)) != S_OK)
	{
		MessageBox(NULL, "Could not get texture data from camera for lightprobe capture", "Light probe capture error", MB_ICONERROR | MB_OK);
		exit(0);
	}
	devCon->CopyResource(face5t, face5tb);
	cameras[0]->setRotation(XMFLOAT3(-270.0f, 180.0f, 0.0f));
	render();
	if (swap->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**> (&face6tb)) != S_OK)
	{
		MessageBox(NULL, "Could not get texture data from camera for lightprobe capture", "Light probe capture error", MB_ICONERROR | MB_OK);
		exit(0);
	}

	devCon->CopyResource(face6t, face6tb);
	cameras[0]->setRotation(camrotold);
	cameras[0]->setPosition(camposold);
	cameras[0]->setFieldOfView(camfovold);
	outputWidth = outwo;
	outputHeight = outho;
	resize();
	render();

	D3D11_MAPPED_SUBRESOURCE ms1;
	if (devCon->Map(face1t, 0, D3D11_MAP_READ, NULL, &ms1) != S_OK)
	{
		MessageBox(NULL, "Could not map light probe data for light probe capture", "Light probe capture error", MB_ICONERROR | MB_OK);
		exit(0);
	}
	memcpy(imagedata1, ms1.pData, slicepitch);
	devCon->Unmap(face1t, 0);
	D3D11_MAPPED_SUBRESOURCE ms2;
	if (devCon->Map(face2t, 0, D3D11_MAP_READ, NULL, &ms2) != S_OK)
	{
		MessageBox(NULL, "Could not map light probe data for light probe capture", "Light probe capture error", MB_ICONERROR | MB_OK);
		exit(0);
	}
	memcpy(imagedata2, ms2.pData, slicepitch);
	devCon->Unmap(face2t, 0);
	D3D11_MAPPED_SUBRESOURCE ms3;
	if (devCon->Map(face3t, 0, D3D11_MAP_READ, NULL, &ms3) != S_OK)
	{
		MessageBox(NULL, "Could not map light probe data for light probe capture", "Light probe capture error", MB_ICONERROR | MB_OK);
		exit(0);
	}
	memcpy(imagedata3, ms3.pData, slicepitch);
	devCon->Unmap(face3t, 0);
	D3D11_MAPPED_SUBRESOURCE ms4;
	if (devCon->Map(face4t, 0, D3D11_MAP_READ, NULL, &ms4) != S_OK)
	{
		MessageBox(NULL, "Could not map light probe data for light probe capture", "Light probe capture error", MB_ICONERROR | MB_OK);
		exit(0);
	}
	memcpy(imagedata4, ms4.pData, slicepitch);
	devCon->Unmap(face4t, 0);
	D3D11_MAPPED_SUBRESOURCE ms5;
	if (devCon->Map(face5t, 0, D3D11_MAP_READ, NULL, &ms5) != S_OK)
	{
		MessageBox(NULL, "Could not map light probe data for light probe capture", "Light probe capture error", MB_ICONERROR | MB_OK);
		exit(0);
	}
	memcpy(imagedata5, ms5.pData, slicepitch);
	devCon->Unmap(face5t, 0);
	D3D11_MAPPED_SUBRESOURCE ms6;
	if (devCon->Map(face6t, 0, D3D11_MAP_READ, NULL, &ms6) != S_OK)
	{
		MessageBox(NULL, "Could not map light probe data for light probe capture", "Light probe capture error", MB_ICONERROR | MB_OK);
		exit(0);
	}
	memcpy(imagedata6, ms6.pData, slicepitch);
	devCon->Unmap(face6t, 0);
	
	DirectX::Image img1;
	img1.format = DXGI_FORMAT_R8G8B8A8_UNORM_SRGB;
	img1.height = resolution;
	img1.width = resolution;
	img1.rowPitch = rowpitch;
	img1.slicePitch = slicepitch;
	img1.pixels = imagedata1;

	DirectX::Image img2;
	img2.format = DXGI_FORMAT_R8G8B8A8_UNORM_SRGB;
	img2.height = resolution;
	img2.width = resolution;
	img2.rowPitch = rowpitch;
	img2.slicePitch = slicepitch;
	img2.pixels = imagedata2;

	DirectX::Image img3;
	img3.format = DXGI_FORMAT_R8G8B8A8_UNORM_SRGB;
	img3.height = resolution;
	img3.width = resolution;
	img3.rowPitch = rowpitch;
	img3.slicePitch = slicepitch;
	img3.pixels = imagedata3;

	DirectX::Image img4;
	img4.format = DXGI_FORMAT_R8G8B8A8_UNORM_SRGB;
	img4.height = resolution;
	img4.width = resolution;
	img4.rowPitch = rowpitch;
	img4.slicePitch = slicepitch;
	img4.pixels = imagedata4;

	DirectX::Image img5;
	img5.format = DXGI_FORMAT_R8G8B8A8_UNORM_SRGB;
	img5.height = resolution;
	img5.width = resolution;
	img5.rowPitch = rowpitch;
	img5.slicePitch = slicepitch;
	img5.pixels = imagedata5;

	DirectX::Image img6;
	img6.format = DXGI_FORMAT_R8G8B8A8_UNORM_SRGB;
	img6.height = resolution;
	img6.width = resolution;
	img6.rowPitch = rowpitch;
	img6.slicePitch = slicepitch;
	img6.pixels = imagedata6;

	string pathWithoutExtension = pathToSave;
	pathWithoutExtension.erase(pathWithoutExtension.end() - 4, pathWithoutExtension.end());
	wstring path1 = stringtowstring(pathWithoutExtension + "_1.DDS");
	wstring path2 = stringtowstring(pathWithoutExtension + "_2.DDS");
	wstring path3 = stringtowstring(pathWithoutExtension + "_3.DDS");
	wstring path4 = stringtowstring(pathWithoutExtension + "_4.DDS");
	wstring path5 = stringtowstring(pathWithoutExtension + "_5.DDS");
	wstring path6 = stringtowstring(pathWithoutExtension + "_6.DDS");
	string path0s = pathWithoutExtension + ".DDS";
	string path1s = pathWithoutExtension + "_1.DDS";
	string path2s = pathWithoutExtension + "_2.DDS";
	string path3s = pathWithoutExtension + "_3.DDS";
	string path4s = pathWithoutExtension + "_4.DDS";
	string path5s = pathWithoutExtension + "_5.DDS";
	string path6s = pathWithoutExtension + "_6.DDS";
	string pathIrradiances = pathWithoutExtension + "Irradiance.DDS";

	string fname1;
	string fname2;
	string fname3;
	string fname4;
	string fname5;
	string fname6;

	int i;
	for (unsigned int o = 0; o < pathWithoutExtension.size(); o++)
	{
		if (pathWithoutExtension[o] == '/')
		{
			i = o;
		}
	}

	i += 1;

	fname1 = pathWithoutExtension;
	fname1.erase(fname1.begin(), fname1.begin() + i);
	fname2 = fname1 + "_2.DDS";
	fname3 = fname1 + "_3.DDS";
	fname4 = fname1 + "_4.DDS";
	fname5 = fname1 + "_5.DDS";
	fname6 = fname1 + "_6.DDS";
	fname1 += "_1.DDS";

	SaveToDDSFile(img1, DDS_FLAGS_FORCE_DX10_EXT, path1.c_str());
	SaveToDDSFile(img2, DDS_FLAGS_FORCE_DX10_EXT, path2.c_str());
	SaveToDDSFile(img3, DDS_FLAGS_FORCE_DX10_EXT, path3.c_str());
	SaveToDDSFile(img4, DDS_FLAGS_FORCE_DX10_EXT, path4.c_str());
	SaveToDDSFile(img5, DDS_FLAGS_FORCE_DX10_EXT, path5.c_str());
	SaveToDDSFile(img6, DDS_FLAGS_FORCE_DX10_EXT, path6.c_str());
	face1t->Release();
	face2t->Release();
	face3t->Release();
	face4t->Release();
	face5t->Release();
	face6t->Release();
	face1tb->Release();
	face2tb->Release();
	face3tb->Release();
	face4tb->Release();
	face5tb->Release();
	face6tb->Release();

	DWORD currentDirBufferSize = GetCurrentDirectoryA(0, NULL);
	LPSTR workingDirectory = new CHAR[currentDirBufferSize];

	if (GetCurrentDirectoryA(currentDirBufferSize, workingDirectory) == 0)
	{
		MessageBox(NULL, "Could not get working directory of program", "Light probe capture error", MB_ICONERROR | MB_OK);
		exit(0);
	}

	system(("texconv.exe -vflip -m 1 " + path1s).c_str());
	system(("texconv.exe -vflip -m 1 " + path2s).c_str());
	system(("texconv.exe -vflip -m 1 " + path3s).c_str());
	system(("texconv.exe -vflip -m 1 " + path4s).c_str());
	system(("texconv.exe -hflip -m 1 " + path5s).c_str());
	system(("texconv.exe -hflip -m 1 " + path6s).c_str());
	system(("texassemble.exe -cube -o " + path0s + " " + path4s + " " + path2s + " " + path6s + " " + path5s + " " + path3s + " " + path1s).c_str());
	system(("texconv.exe -f BC1_UNORM -nologo " + path0s + " & pause").c_str());
	system(("cmft.exe --input " + path0s + " --filter irradiance --outputNum 1 --output0 " + pathIrradiances + " --output0params dds,bgra8,cubemap & pause").c_str());
	system(("cd " + string(workingDirectory) + "//Data//Textures// & del " + fname1 + " " + fname2 + " " + fname3 + " " + fname4 + " " + fname5 + " " + fname6).c_str());


	delete[] workingDirectory;
}

void Renderer::convolveLightProbe(string path)
{
	Texture cubeMapToFilter;
	cubeMapToFilter.loadFromFile(path, &dev);
	ID3D11ShaderResourceView *rv = cubeMapToFilter.getResource();

	ID3D11ComputeShader *cs;
	ID3DBlob *shaderCode;
	ID3DBlob *shaderCompilationErrors;

	string shaderPath = "Data//Shaders//ProcessLightProbe.hlsl";

	if (D3DCompileFromFile(stringtowstring(shaderPath.c_str()).c_str(), NULL, NULL, "main", "cs_5_0", NULL, NULL, &shaderCode, &shaderCompilationErrors) != S_OK)
	{
		MessageBox(NULL, ("Error compiling shader from file: " + shaderPath).c_str(), "Shader Compilation Errors", MB_ICONERROR | MB_OK);
		MessageBox(NULL, (char*)shaderCompilationErrors->GetBufferPointer(), "Error", MB_ICONERROR | MB_OK);
		exit(0);
	}

	if (shaderCompilationErrors)
	{
		shaderCompilationErrors->Release();
	}

	if (dev->CreateComputeShader(shaderCode->GetBufferPointer(), shaderCode->GetBufferSize(), NULL, &cs) != S_OK)
	{
		MessageBox(NULL, ("Error creating shader: " + shaderPath).c_str(), "Shader Creation Error", MB_ICONERROR | MB_OK);
		exit(0);
	}

	shaderCode->Release();

	D3D11_BUFFER_DESC outputDesc;
	ZeroMemory(&outputDesc, sizeof(D3D11_BUFFER_DESC));
	outputDesc.BindFlags = D3D11_BIND_UNORDERED_ACCESS | D3D11_BIND_SHADER_RESOURCE;
	outputDesc.ByteWidth = sizeof(*rv);

	
	devCon->CSSetShader(cs, NULL, NULL);
	devCon->CSSetShaderResources(0, 1, &rv);
}

ID3D11Device  **Renderer::getDevice()
{
	return &dev;
}

vector<VertexShader> Renderer::getVertexShaders()
{
	return vertexShaders;
}

vector<PixelShader> Renderer::getPixelShaders()
{
	return pixelShaders;
}

vector<Model*> Renderer::getModels()
{
	return models;
}

void Renderer::setVertexShaders(vector<VertexShader> toSet)
{
	vertexShaders = toSet;
}

time_t Renderer::getDeltaTime()
{
	return deltaTime;
}

Model *Renderer::getObject(string name)
{
	for (unsigned int i = 0; i < models.size(); i++)
	{
		if (models[i]->getName() == name)
		{
			return models[i];
		}
	}

	return models[0];
}

void Renderer::setQuadModel(Model* toSet)
{
	for (unsigned int i = 0; i < vertexShaders.size(); i++)
	{
		if (toSet->getVertexShaderName() == vertexShaders[i].getName())
		{
			toSet->setVertexShader(i);
		}
	}

	for (unsigned int i = 0; i < pixelShaders.size(); i++)
	{
		if (toSet->getPixelShaderName() == pixelShaders[i].getName())
		{
			toSet->setPixelShader(i);
		}
	}

	quadModel = toSet;
}

GuiManager *Renderer::getGuiManager()
{
	return &guiManager;
}

void Renderer::updateGuiTextures()
{
	for (unsigned int i = 0; i < guiManager.getCurrentGuiLayout()->windows.size(); i++)
	{
		GuiWindow window = guiManager.getCurrentGuiLayout()->windows[i];

		for (unsigned int j = 0; j < window.getNumberOfHudElements(); j++)
		{
			if (window.getHudElement(j)->getNeedsToBeLoaded() == true)
			{
				for (unsigned int k = 0; k < textures.size(); k++)
				{
					for (unsigned int l = 0; l < window.getHudElement(j)->getNumberOfTexturesToBeLoaded(); l++)
					{
						if (window.getHudElement(j)->getTexturesToBeLoaded()[l] == textures[k].getName())
						{
							window.getHudElement(j)->addTexture(&textures[j]);
						}
					}
				}

				if (window.getHudElement(j)->getNumberOfTexturesToBeLoaded() > window.getHudElement(j)->getNumberOfTextures())
				{
					MessageBoxA(NULL, ("Could not find texture for UI element: " + window.getHudElement(j)->getName()).c_str(), "GUI display error", MB_ICONERROR | MB_OK);
					exit(0);
				}

				window.getHudElement(j)->setNeedToBeLoaded(false);
			}
		}
	}

	for (unsigned int i = 0; i < guiManager.getCurrentGuiLayout()->fonts.size(); i++)
	{
		for (unsigned int j = 0; j < textures.size(); j++)
		{
			for (unsigned int k = 0; k < guiManager.getCurrentGuiLayout()->fonts[i].getFontSheetsToLoad().size(); k++)
			{
				if (guiManager.getCurrentGuiLayout()->fonts[i].getFontSheetsToLoad()[k] == textures[j].getName())
				{
					guiManager.getCurrentGuiLayout()->fonts[i].addFontSheet(textures[j]);
				}
			}	
		}

		for (unsigned int k = 0; k < guiManager.getCurrentGuiLayout()->windows.size(); k++)
		{
			for (unsigned int m = 0; m < guiManager.getCurrentGuiLayout()->windows[k].getNumberOfTextElements(); m++)
			{
				if (guiManager.getCurrentGuiLayout()->windows[k].getTextElement(m)->getFont()->getName() == guiManager.getCurrentGuiLayout()->fonts[i].getName())
				{
					guiManager.getCurrentGuiLayout()->windows[k].getTextElement(m)->setFont(guiManager.getCurrentGuiLayout()->fonts[i]);
				}
			}
		}
	}
}

bool Renderer::getIsInitialized()
{
	return isInitialized;
}

ID3D11ShaderResourceView *Renderer::getBackBuffer()
{
	return renderTexture;
}

Texture *Renderer::getTexture(string toGet)
{
	for (unsigned int i = 0; i < textures.size(); i++)
	{
		if (textures[i].getName() == toGet)
		{
			return &textures[i];
		}
	}

	return nullptr;
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

void Renderer::add(Camera *toAdd)
{
	cameras.push_back(toAdd);
}

void Renderer::add(Light toAdd)
{
	lights.push_back(toAdd);
}

void Renderer::add(Texture toAdd)
{
	textures.push_back(toAdd);
}

void Renderer::add(Material toAdd)
{
	materials.push_back(toAdd);
}

Renderer::Renderer()
{
	hWnd = NULL;
	outputWidth = 640;
	outputHeight = 480;
	refreshRate = 60;
	hardwareAntiAliasingCount = 1;
	fullScreenMode = false;
	canBeInitialized = false;
}

Renderer::Renderer(HWND handle)
{
	hWnd = handle;
	outputWidth = 640;
	outputHeight = 480;
	refreshRate = 60;
	hardwareAntiAliasingCount = 1;
	fullScreenMode = false;
	canBeInitialized = true;
}

Renderer::Renderer(CoreWindow window)
{
	hWnd = window.getHandle();
	outputWidth = window.getWindowSize().x;
	outputHeight = window.getWindowSize().y;
	refreshRate = 60;
	hardwareAntiAliasingCount = 1;
	fullScreenMode = window.getWindowedMode();
	fullScreenMode = false;
	canBeInitialized = true;
}

Renderer::Renderer(CoreWindow window, int refreshrate, int hardwareantialiasingcount)
{
	hWnd = window.getHandle();
	outputWidth = window.getWindowSize().x;
	outputHeight = window.getWindowSize().y;
	refreshRate = 60;
	hardwareAntiAliasingCount = 1;
	fullScreenMode = window.getWindowedMode();
	fullScreenMode = false;
	canBeInitialized = true;
}

Renderer::Renderer(HWND handle, int width, int height, int refreshrate, int hardwareantialiasingcount, bool windowedmode)
{
	hWnd = handle;
	outputWidth = width;
	outputHeight = height;
	refreshRate = refreshrate;
	hardwareAntiAliasingCount = hardwareantialiasingcount;
	fullScreenMode = fullScreenMode;
	fullScreenMode = false;
	canBeInitialized = true;
}

Renderer::Renderer(vector<string> renderData)
{

}

Renderer::~Renderer()
{

}