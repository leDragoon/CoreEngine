#pragma once
#include<FileManager.h>
#include<Util.h>

using std::string;

struct AssetList
{
	vector<string> modelNames;
	vector<string> modelPaths;
	vector<string> vertexShaderNames;
	vector<string> vertexShaderPaths;
	vector<string> pixelShaderNames;
	vector<string> pixelShaderPaths;
};

class AssetListFile : public File
{
private:
	void parse();
	AssetList assets;
public:
	void loadFile(string path);
	AssetList getAssetList();
	vector<string> getModelNames();
	vector<string> getModelPaths();
	vector<string> getVertexShaderNames();
	vector<string> getVertexShaderPaths();
	vector<string> getPixelShaderNames();
	vector<string> getPixelShaderPaths();
	AssetListFile();
	AssetListFile(string path);
};