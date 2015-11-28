#pragma once
#include<FileManager.h>
#include<Vertex.h>
#include<openctm.h>

struct ModelData
{
	vector<Vertex> vertices;
	vector<DWORD> indices;
};

class ModelFile : public File
{
private:
	void parse();
	void parseCTM();
	void parseCTM(string path);
	string convertToCTM();
	string fileExtension;
	ModelData mData;
public:
	ModelData loadFile(string path);
	ModelFile();
	ModelFile(string path);
};