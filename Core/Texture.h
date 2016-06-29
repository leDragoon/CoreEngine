#pragma once
#include<TextureFile.h>

#define CORE_TEXTUREUSAGE_ALBEDO 1
#define CORE_TEXTUREUSAGE_NORMAL 2
#define CORE_TEXTUREUSAGE_METALIC 3
#define CORE_TEXTUREUSAGE_ROUGHNESS 4
#define CORE_TEXTUREUSAGE_AMBIENTOCCLUSION 5
#define CORE_TEXTUREUSAGE_EMMISSION 6

class Texture
{
private:
	string name;
	ID3D11ShaderResourceView *d3dTex;
	int textureType = 1;
	int textureUsage = 0;
	bool isLoaded = false;
public:
	void loadFromFile(string path, ID3D11Device **dev);
	ID3D11ShaderResourceView *getResource();
	void setName(string toSet);
	string getName();
	void setTextureType(int toSet);
	int getTextureType();
	void close();
	void setIsLoaded(bool toSet);
	bool getIsLoaded();
	void setUsage(int toSet);
	int getUsage();
	void setResource(ID3D11ShaderResourceView *toSet);
	Texture();
	Texture(string toLoadFilePath, ID3D11Device **dev);
};