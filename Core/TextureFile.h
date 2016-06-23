#pragma once
#include<d3d11.h>
#include<FileManager.h>
#include<WICTextureLoader.h>
#include<DDSTextureLoader.h>
#include<string>

using std::wstring;

#define CORE_TEXTURETYPE_2D_BW 0
#define CORE_TEXTURETYPE_2D_COLOR 1
#define CORE_TEXTURETYPE_2D_NORMAL 2
#define CORE_TEXTURETYPE_3D 3
#define CORE_TEXTURETYPE_CUBE 4

class TextureFile
{
private:
	ID3D11ShaderResourceView *sv;
	bool loaded = false;
public:
	ID3D11ShaderResourceView *loadTexture(string path, ID3D11Device **dev, int textureType);
	ID3D11ShaderResourceView *getShaderResourceView();
	TextureFile();
	TextureFile(string path, ID3D11Device **dev, int textureType);
	~TextureFile();
};
