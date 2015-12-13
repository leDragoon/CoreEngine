#pragma once
#include<FileManager.h>
#include<Util.h>

using std::string;

struct AssetList
{
	vector<string> modelNames;
	vector<string> modelPaths;
	vector<string> cameraNames;
	vector<string> vertexShaderNames;
	vector<string> vertexShaderPaths;
	vector<string> pixelShaderNames;
	vector<string> pixelShaderPaths;
	vector<string> lightNames;
	vector<string> lightPaths;
	vector<string> textureNames;
	vector<string> texturePaths;
	vector<string> materialNames;
	vector<string> materialPaths;
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
	vector<string> getCameraNames();
	vector<string> getVertexShaderNames();
	vector<string> getVertexShaderPaths();
	vector<string> getPixelShaderNames();
	vector<string> getPixelShaderPaths();
	vector<string> getLightNames();
	vector<string> getLightPaths();
	vector<string> getTextureNames();
	vector<string> getTexturePaths();
	vector<string> getMaterialNames();
	vector<string> getMaterialPaths();
	AssetListFile();
	AssetListFile(string path);
};