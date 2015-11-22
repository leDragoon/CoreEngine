#pragma once
#include<FileManager.h>
#include<Vertex.h>
#include<openctm.h>

class ModelFile : public File
{
private:
	void parse();
	void parseCTM();
	void parseCTM(string path);
	string convertToCTM();
	string fileExtension;
	vector<Vertex> mvertices;
public:
	vector<Vertex> loadFile(string path);
	ModelFile();
	ModelFile(string path);
};