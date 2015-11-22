#pragma once
#include<DirectXMath.h>
#include<string>

#define CORE_DRAWABLETYPE_MODEL 0

using std::string;

class Drawable
{
private:
	int type;
	string name;
	int identifier;
protected:
	DirectX::XMFLOAT3 worldPosition;
	DirectX::XMFLOAT3 worldRotation;
	DirectX::XMFLOAT3 worldScale;
	int vertexShaderCode;
	int pixelShaderCode;
	bool needsToBeInitialized = true;
	void setDrawableType(int toSet);
	string vertexShaderName;
	string pixelShaderName;
	bool shaderCodeShouldBeSet = true;
public:
	int getDrawableType();
	void setIsInitialized(bool toSet);
	bool getIsInitialized();
	void setVertexShader(string shaderName);
	void setVertexShader(int shaderCode);
	int getVertexShaderCode();
	string getVertexShaderName();
	void setPixelShader(string shaderName);
	void setPixelShader(int shaderCode);
	int getPixelShaderCode();
	string getPixelShaderName();
	void setPosition(DirectX::XMFLOAT3 position);
	void setRotation(DirectX::XMFLOAT3 rotation);
	void setScale(DirectX::XMFLOAT3 scale);
	void setName(string toSet);
	string getName();
	void setIdentifier(int toSet);
	int getIdentifier();
	DirectX::XMFLOAT3 getPosition();
	DirectX::XMFLOAT3 getRotation();
	DirectX::XMFLOAT3 getScale();
};