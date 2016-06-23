#pragma once
#include<Vertex.h>
#include<vector>
#include<Drawable.h>
#include<ModelFile.h>
#include<btBulletCollisionCommon.h>

using std::vector;
using std::string;

struct AABB
{
	btVector3 min;
	btVector3 max;
};

class Model : public Drawable
{
private:
	string filePath;
	ID3D11Buffer *vertexBuffer;
	ID3D11Buffer *indexBuffer;
	int numberOfVertices = 1;
	int numberOfIndices = 1;
	vector<Vertex> vertices;
	vector<DWORD> indices;
	AABB collisionBox;
	void generateCollisionBox();
public:
	void loadData(string modelFilePath);
	void loadVertices(vector<Vertex> Vertices);
	void loadIndices(vector<DWORD> Indices);
	void loadVertices(ID3D11Buffer *VertexBuffer);
	void loadVertices(vector<DirectX::XMFLOAT3> vertexPositions, vector<DirectX::XMFLOAT3> vertexNormals, vector<DirectX::XMFLOAT2> vertexUVs);
	void setVertexBuffer(ID3D11Buffer *VertexBuffer);
	void setIndexBuffer(ID3D11Buffer *IndexBuffer);
	void setFilePath(string path);
	int getNumberOfVertices();
	int getNumberOfIndices();
	string getFilePath();
	vector<Vertex> *getVertices();
	vector<DWORD> *getIndices();
	ID3D11Buffer** getVertexBuffer();
	ID3D11Buffer** getIndexBuffer();
	void draw();
	void close();

	Model();
};
