#include "Shader.h"

void Shader::setName(string name)
{
	shaderName = name;
}

string Shader::getName()
{
	return shaderName;
}

void Shader::setFilePath(string filePath)
{
	shaderFilePath = filePath;
}

string Shader::getFilePath()
{
	return shaderFilePath;
}

void Shader::setInitialized(bool IsInitialized)
{
	isInitialized = IsInitialized;
}

bool Shader::getIsInitialized()
{
	return isInitialized;
}

Shader::Shader()
{

}

void VertexShader::setVertexShader(ID3D11VertexShader* shader)
{
	d3dShader = shader;
}

void VertexShader::setInputLayout(ID3D11InputLayout * layout)
{
	vertexLayout = layout;
}

ID3D11VertexShader** VertexShader::getVertexShader()
{
	return &d3dShader;
}

ID3D11InputLayout** VertexShader::getInputLayout()
{
	return &vertexLayout;
}

void VertexShader::close()
{
	if (d3dShader)
	{
		d3dShader->Release();
		vertexLayout->Release();
	}
}

void PixelShader::setPixelShader(ID3D11PixelShader* shader)
{
	d3dShader = shader;
}

ID3D11PixelShader ** PixelShader::getPixelShader()
{
	return &d3dShader;
}

void PixelShader::close()
{
	if (d3dShader)
	{
		d3dShader->Release();
	}
}
