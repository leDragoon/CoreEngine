#pragma once
#include<DirectXMath.h>
#include<string>
#include<vector>

#define CORE_DRAWABLETYPE_MODEL 0

using std::string;
using std::vector;
using namespace DirectX;

class Drawable
{
private:
	int type;
	string name;
	int identifier;
protected:
	DirectX::XMFLOAT3 worldHeading = DirectX::XMFLOAT3(0.0f, 0.0f, 1.0f);
	DirectX::XMFLOAT3 worldPosition = DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f);
	DirectX::XMFLOAT3 worldRotation = DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f);;
	DirectX::XMFLOAT3 worldScale = DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f);;
	DirectX::XMFLOAT4X4 worldMatrix;
	int vertexShaderCode = 0;
	int pixelShaderCode = 0;
	int materialCode = 0;
	bool needsToBeInitialized = true;
	void setDrawableType(int toSet);
	string vertexShaderName = "mainVertexShader";
	string pixelShaderName = "mainPixelShader";
	bool shaderCodeShouldBeSet = true;
	void calculateWorldMatrix();
	void calculateHeadingVector();
	vector<string> scripts;
public:
	int getDrawableType();
	void setIsInitialized(bool toSet);
	bool getIsInitialized();
	void setVertexShader(string shaderName);
	void setVertexShader(int shaderCode);
	void setMaterialCode(int toSet);
	int getMaterialCode();
	int getVertexShaderCode();
	string getVertexShaderName();
	void setPixelShader(string shaderName);
	void setPixelShader(int shaderCode);
	int getPixelShaderCode();
	string getPixelShaderName();
	void setPosition(DirectX::XMFLOAT3 position);
	void setRotation(DirectX::XMFLOAT3 rotation);
	void setScale(DirectX::XMFLOAT3 scale);
	void translate(DirectX::XMFLOAT3 toTranslate);
	void localTranslate(DirectX::XMFLOAT3 toTranslate);
	void rotate(DirectX::XMFLOAT3 toRotate);
	void scale(DirectX::XMFLOAT3 toScale);
	void setName(string toSet);
	string getName();
	void setIdentifier(int toSet);
	int getIdentifier();
	void setScripts(vector<string> toSet);
	void addScript(string toAdd);
	vector<string> getScripts();
	DirectX::XMFLOAT4X4 getWorldMatrix();
	DirectX::XMFLOAT3 getPosition();
	DirectX::XMFLOAT3 getRotation();
	DirectX::XMFLOAT3 getScale();
};