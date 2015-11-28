#pragma once
#include<Vertex.h>
#include<vector>
#include<Drawable.h>
#include<ModelFile.h>

using std::vector;
using std::string;

class Model : public Drawable
{
private:
	string filePath;
	ID3D11Buffer *vertexBuffer;
	ID3D11Buffer *indexBuffer;
	int numberOfVertices;
	int numberOfIndices;
	vector<Vertex> vertices;
	vector<DWORD> indices;
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
