#pragma once
#include<FileManager.h>
#include<Texture.h>

class MaterialFile : public File
{
private:
	string name;
	vector<int> textureUsages;
	vector<string> textureNames;
	vector<string> vertexShaderNames;
	vector<string> pixelShaderNames;
public:
	void loadMaterial(string path);
	vector<int> getTextureUsages();
	vector<string> getTextureNames();
	vector<string> getVertexShaderNames();
	vector<string> getPixelShaderNames();
	MaterialFile();
	MaterialFile(string path);
};