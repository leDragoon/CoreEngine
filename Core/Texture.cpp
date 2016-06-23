#include "Texture.h"

void Texture::loadFromFile(string path, ID3D11Device **dev)
{
	TextureFile tFile;
	d3dTex = tFile.loadTexture(path, dev, textureType);
	isLoaded = true;
}

ID3D11ShaderResourceView *Texture::getResource()
{
	return d3dTex;
}

void Texture::setName(string toSet)
{
	name = toSet;
}

string Texture::getName()
{
	return name;
}

void Texture::setTextureType(int toSet)
{
	textureType = toSet;
}

int Texture::getTextureType()
{
	return textureType;
}

void Texture::close()
{
	if (isLoaded)
	{
		d3dTex->Release();
	}
}

void Texture::setIsLoaded(bool toSet)
{
	isLoaded = toSet;
}

bool Texture::getIsLoaded()
{
	return isLoaded;
}

void Texture::setUsage(int toSet)
{
	textureUsage = toSet;
}

int Texture::getUsage()
{
	return textureUsage;
}

Texture::Texture()
{

}

Texture::Texture(string toLoadFilePath, ID3D11Device ** dev)
{
	loadFromFile(toLoadFilePath, dev);
}
