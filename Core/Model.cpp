#include "Model.h"

void Model::loadVertices(string modelFilePath)
{
	filePath = modelFilePath;
	ModelFile mFile;
	vertices = mFile.loadFile(modelFilePath);
	setDrawableType(CORE_DRAWABLETYPE_MODEL);
}

void Model::loadVertices(vector<Vertex> Vertices)
{
	vertices = Vertices;
	setDrawableType(CORE_DRAWABLETYPE_MODEL);
}

void Model::loadVertices(ID3D11Buffer * VertexBuffer)
{
	vertexBuffer = VertexBuffer;
	needsToBeInitialized = false;
	setDrawableType(CORE_DRAWABLETYPE_MODEL);
}

void Model::loadVertices(vector<DirectX::XMFLOAT3> vertexPositions, vector<DirectX::XMFLOAT3> vertexNormals, vector<DirectX::XMFLOAT2> vertexUVs)
{
	for (unsigned int i = 0; i < vertexPositions.size(); i++)
	{
		Vertex v;
		v.position = vertexPositions[i];
		v.normal = vertexNormals[i];
		v.uv = vertexUVs[i];
		vertices.push_back(v);
	}

	setDrawableType(CORE_DRAWABLETYPE_MODEL);
}

void Model::setVertexBuffer(ID3D11Buffer * VertexBuffer)
{
	loadVertices(vertexBuffer);
	setDrawableType(CORE_DRAWABLETYPE_MODEL);
}

void Model::setFilePath(string path)
{
	filePath = path;
}


string Model::getFilePath()
{
	return filePath;
}

vector<Vertex>* Model::getVertices()
{
	return &vertices;
}

ID3D11Buffer** Model::getVertexBuffer()
{
	return &vertexBuffer;
}

void Model::draw()
{

}

void Model::close()
{
	if (vertexBuffer)
	{
		vertexBuffer->Release();
	}
}

Model::Model()
{
	setDrawableType(CORE_DRAWABLETYPE_MODEL);
}
