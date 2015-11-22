#pragma once
#include<FileManager.h>
#include<d3d11.h>

using std::string;

class Shader
{
private:
	string shaderName;
	string shaderFilePath;
	bool isInitialized = false;
public:
	void setName(string name);
	string getName();
	void setFilePath(string filePath);
	string getFilePath();
	void setInitialized(bool IsInitialized);
	bool getIsInitialized();

	Shader();
};

class VertexShader : public Shader
{
private:
	ID3D11VertexShader *d3dShader;
	ID3D11InputLayout *vertexLayout;
public:
	void setVertexShader(ID3D11VertexShader *shader);
	void setInputLayout(ID3D11InputLayout *layout);
	ID3D11VertexShader** getVertexShader();
	ID3D11InputLayout** getInputLayout();
	void close();
};

class PixelShader : public Shader
{
private:
	ID3D11PixelShader *d3dShader;
public:
	void setPixelShader(ID3D11PixelShader *shader);
	ID3D11PixelShader** getPixelShader();
	void close();
};
