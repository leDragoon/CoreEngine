#include "Material.h"

void Material::loadMaterial(string path, ID3D11Device **dev)
{
	MaterialFile mFile;
	mFile.loadMaterial(path);
	textures = mFile.getTextureNames();
	textureUsages = mFile.getTextureUsages();
	vertexShaders = mFile.getVertexShaderNames();
	pixelShaders = mFile.getPixelShaderNames();
}

void Material::setName(string toSet)
{
	name = toSet;
}

void Material::setAlbedoTextureCode(int toSet)
{
	albedoTexture = toSet;
}

void Material::setRoughnessTextureCode(int toSet)
{
	roughnessTexture = toSet;
}

void Material::setMetalnessTextureCode(int toSet)
{
	metalnessTexture = toSet;
}

void Material::setNormalTextureCode(int toSet)
{
	normalTexture = toSet;
}

void Material::setRadianceTextureCode(int toSet)
{
	radianceTexture = toSet;
}

void Material::setIrradianceTextureCode(int toSet)
{
	irradianceTexture = toSet;
}

int Material::getAlbedoTextureCode()
{
	return albedoTexture;
}

vector<string> Material::getTextureNames()
{
	return textures;
}

vector<string> Material::getVertexShaderNames()
{
	return vertexShaders;
}

vector<string> Material::getPixelShaderNames()
{
	return pixelShaders;
}

string Material::getName()
{
	return name;
}

void Material::close()
{

}

Material::Material()
{

}

int Material::getRoughnessTextureCode()
{
	return roughnessTexture;
}

int Material::getMetalnessTextureCode()
{
	return metalnessTexture;
}

int Material::getNormalTextureCode()
{
	return normalTexture;
}

int Material::getRadianceTextureCode()
{
	return radianceTexture;
}

int Material::getIrradianceTextureCode()
{
	return irradianceTexture;
}

vector<int> Material::getTextureUsages()
{
	return textureUsages;
}
