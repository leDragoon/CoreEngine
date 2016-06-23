#include "Model.h"

void Model::generateCollisionBox()
{
	float minX, maxX, minY, maxY, minZ, maxZ;
	minX = 1.0f;
	minY = 1.0f;
	minZ = 1.0f;
	maxX = 0.0f;
	maxY = 0.0f;
	maxZ = 0.0f;

	for (unsigned int i = 0; i < vertices.size(); i++)
	{
		if (vertices[i].position.x < minX)
		{
			minX = vertices[i].position.x;
		}
	}

	for (unsigned int i = 0; i < vertices.size(); i++)
	{
		if (vertices[i].position.y < minY)
		{
			minY = vertices[i].position.y;
		}
	}

	for (unsigned int i = 0; i < vertices.size(); i++)
	{
		if (vertices[i].position.z < minZ)
		{
			minZ = vertices[i].position.z;
		}
	}

	for (unsigned int i = 0; i < vertices.size(); i++)
	{
		if (vertices[i].position.x > maxX)
		{
			maxX = vertices[i].position.x;
		}
	}

	for (unsigned int i = 0; i < vertices.size(); i++)
	{
		if (vertices[i].position.y > maxY)
		{
			maxY = vertices[i].position.y;
		}
	}

	for (unsigned int i = 0; i < vertices.size(); i++)
	{
		if (vertices[i].position.z > maxZ)
		{
			maxZ = vertices[i].position.z;
		}
	}

	collisionBox.min = btVector3(minX, minY, minZ);
	collisionBox.max = btVector3(maxX, maxY, maxZ);
}

void Model::loadData(string modelFilePath)
{
	filePath = modelFilePath;
	ModelFile mFile;
	ModelData mData = mFile.loadFile(modelFilePath);
	vertices = mData.vertices;
	indices = mData.indices;
	numberOfVertices = mData.vertices.size();
	numberOfIndices = mData.indices.size();
	setDrawableType(CORE_DRAWABLETYPE_MODEL);
	generateCollisionBox();
}

void Model::loadVertices(vector<Vertex> Vertices)
{
	vertices = Vertices;
	numberOfVertices = Vertices.size();
	setDrawableType(CORE_DRAWABLETYPE_MODEL);
	generateCollisionBox();
}

void Model::loadIndices(vector<DWORD> Indices)
{
	indices = Indices;
	numberOfIndices = Indices.size();
	setDrawableType(CORE_DRAWABLETYPE_MODEL);
}

void Model::loadVertices(ID3D11Buffer *VertexBuffer)
{
	vertexBuffer = VertexBuffer;
	needsToBeInitialized = false;
	setDrawableType(CORE_DRAWABLETYPE_MODEL);
	generateCollisionBox();
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

	numberOfVertices = vertexPositions.size();
	setDrawableType(CORE_DRAWABLETYPE_MODEL);
	generateCollisionBox();
}

void Model::setVertexBuffer(ID3D11Buffer * VertexBuffer)
{
	loadVertices(vertexBuffer);
	setDrawableType(CORE_DRAWABLETYPE_MODEL);
}

void Model::setIndexBuffer(ID3D11Buffer * IndexBuffer)
{
	indexBuffer = IndexBuffer;
}

void Model::setFilePath(string path)
{
	filePath = path;
}

int Model::getNumberOfVertices()
{
	return numberOfVertices;
}

int Model::getNumberOfIndices()
{
	return numberOfIndices;
}

string Model::getFilePath()
{
	return filePath;
}

vector<Vertex>* Model::getVertices()
{
	return &vertices;
}

vector<DWORD>* Model::getIndices()
{
	return &indices;
}

ID3D11Buffer** Model::getVertexBuffer()
{
	return &vertexBuffer;
}

ID3D11Buffer ** Model::getIndexBuffer()
{
	return &indexBuffer;
}

void Model::draw()
{

}

void Model::close()
{
	if (vertexBuffer)
	{
		vertexBuffer->Release();
	//	indexBuffer->Release();
	}
}

Model::Model()
{
	setDrawableType(CORE_DRAWABLETYPE_MODEL);
}
