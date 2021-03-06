#include "Drawable.h"

void Drawable::calculateWorldMatrix()
{
	DirectX::XMStoreFloat4x4(&worldMatrix, DirectX::XMMatrixIdentity());
	DirectX::XMMATRIX posMat;
	DirectX::XMMATRIX rotMat;
	DirectX::XMMATRIX sclMat;

	posMat = DirectX::XMMatrixTranslation(worldPosition.x, worldPosition.y, worldPosition.z);
	rotMat = DirectX::XMMatrixRotationX(XMConvertToRadians(worldRotation.x)) * DirectX::XMMatrixRotationY(XMConvertToRadians(worldRotation.y)) * DirectX::XMMatrixRotationZ(XMConvertToRadians(worldRotation.z));
	sclMat = DirectX::XMMatrixScaling(worldScale.x, worldScale.y, worldScale.z);
	DirectX::XMStoreFloat4x4(&worldMatrix, sclMat * rotMat * posMat);
}

void Drawable::calculateHeadingVector()
{
	worldHeading.x = cosf(DirectX::XMConvertToRadians(worldRotation.y));
	worldHeading.z = sinf(DirectX::XMConvertToRadians(worldRotation.y));
}

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
	shaderCodeShouldBeSet = false;
}

void Drawable::setMaterialCode(int toSet)
{
	materialCode = toSet;
}

int Drawable::getMaterialCode()
{
	return materialCode;
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
	shaderCodeShouldBeSet = false;
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
	calculateWorldMatrix();
}

void Drawable::setRotation(DirectX::XMFLOAT3 rotation)
{
	worldRotation = DirectX::XMFLOAT3(rotation.x, rotation.y, rotation.z);
	calculateWorldMatrix();
}

void Drawable::setScale(DirectX::XMFLOAT3 scale)
{
	worldScale = scale;
	calculateWorldMatrix();
}

void Drawable::translate(DirectX::XMFLOAT3 toTranslate)
{
	worldPosition.x += toTranslate.x;
	worldPosition.y += toTranslate.y;
	worldPosition.z += toTranslate.z;
	calculateWorldMatrix();
}

void Drawable::localTranslate(DirectX::XMFLOAT3 toTranslate)
{
	calculateHeadingVector();
	worldPosition.x += worldHeading.x * toTranslate.z * 0.5f;
	worldPosition.z += worldHeading.z * toTranslate.z * 0.5f;
	calculateWorldMatrix();
}

void Drawable::rotate(DirectX::XMFLOAT3 toRotate)
{
	worldRotation.x += toRotate.x;
	worldRotation.y += toRotate.y;
	worldRotation.z += toRotate.z;
	calculateWorldMatrix();
}

void Drawable::scale(DirectX::XMFLOAT3 toScale)
{
	worldScale.x += toScale.x;
	worldScale.y += toScale.y;
	worldScale.z += toScale.z;
	calculateWorldMatrix();
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

void Drawable::setScripts(vector<string> toSet)
{
	scripts = toSet;
}

void Drawable::addScript(string toAdd)
{
	scripts.push_back(toAdd);
}

vector<string> Drawable::getScripts()
{
	return scripts;
}

DirectX::XMFLOAT4X4 Drawable::getWorldMatrix()
{
	return worldMatrix;
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
