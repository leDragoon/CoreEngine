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
	vector<string> soundNames;
	vector<string> soundPaths;
	vector<string> scriptNames;
	vector<string> scriptPaths;
	vector<string> guiLayoutNames;
	vector<string> guiLayoutPaths;
	vector<string> fontNames;
	vector<string> fontFiles;
	vector<vector<string>> fontTextures;
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
	vector<string> getSoundNames();
	vector<string> getSoundPaths();
	vector<string> getScriptNames();
	vector<string> getScriptPaths();
	vector<string> getGuiLayoutNames();
	vector<string> getGuiLayoutPaths();
	vector<string> getFontNames();
	vector<string> getFontFiles();
	vector<vector<string>> getFontTextures();
	AssetListFile();
	AssetListFile(string path);
};