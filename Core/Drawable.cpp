#include "Drawable.h"

int Drawable::getDrawableType()
{
	return type;
}

void Drawable::setDrawableType(int toSet)
{
	type = toSet;
}

void Drawable::setIsInitialized(bool toSet)
{
	needsToBeInitialized = !toSet;
}

bool Drawable::getIsInitialized()
{
	return !needsToBeInitialized;
}

void Drawable::setVertexShader(string shaderName)
{
	vertexShaderName = shaderName;
	shaderCodeShouldBeSet = true;
}

void Drawable::setVertexShader(int shaderCode)
{
	vertexShaderCode = shaderCode;
}

int Drawable::getVertexShaderCode()
{
	return vertexShaderCode;
}

string Drawable::getVertexShaderName()
{
	return vertexShaderName;
}

void Drawable::setPixelShader(string shaderName)
{
	pixelShaderName = shaderName;
	shaderCodeShouldBeSet = true;
}

void Drawable::setPixelShader(int shaderCode)
{
	pixelShaderCode = shaderCode;
}

int Drawable::getPixelShaderCode()
{
	return pixelShaderCode;
}

string Drawable::getPixelShaderName()
{
	return pixelShaderName;
}

void Drawable::setPosition(DirectX::XMFLOAT3 position)
{
	worldPosition = position;
}

void Drawable::setRotation(DirectX::XMFLOAT3 rotation)
{
	worldRotation = rotation;
}

void Drawable::setScale(DirectX::XMFLOAT3 scale)
{
	worldScale = scale;
}

void Drawable::setName(string toSet)
{
	name = toSet;
}

string Drawable::getName()
{
	return name;
}

void Drawable::setIdentifier(int toSet)
{
	identifier = toSet;
}

int Drawable::getIdentifier()
{
	return identifier;
}

DirectX::XMFLOAT3 Drawable::getPosition()
{
	return worldPosition;
}

DirectX::XMFLOAT3 Drawable::getRotation()
{
	return worldRotation;
}

DirectX::XMFLOAT3 Drawable::getScale()
{
	return worldScale;
}
