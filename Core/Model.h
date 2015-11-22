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
	vector<Vertex> vertices;
public:
	void loadVertices(string modelFilePath);
	void loadVertices(vector<Vertex> vertices);
	void loadVertices(ID3D11Buffer *VertexBuffer);
	void loadVertices(vector<DirectX::XMFLOAT3> vertexPositions, vector<DirectX::XMFLOAT3> vertexNormals, vector<DirectX::XMFLOAT2> vertexUVs);
	void setVertexBuffer(ID3D11Buffer *VertexBuffer);
	void setFilePath(string path);
	string getFilePath();
	vector<Vertex> *getVertices();
	ID3D11Buffer** getVertexBuffer();
	void draw();
	void close();

	Model();
};
