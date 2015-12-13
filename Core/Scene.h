#pragma once
#include<AssetListFile.h>
#include<Renderer.h>
#include<SceneFile.h>
#include<LightFile.h>
#include<Texture.h>

class Scene
{
private:
	Renderer *renderer;
	int sceneType;
	string sceneName;
	string filePath;
	AssetList *globalAssetList;
	AssetList sceneAssetList;
	vector<Model> sceneModels;
	bool sceneAndGlobalAssetListCombined = false;
public:
	void load();
	void load(string FilePath);
	void load(string FilePath, string assetListFilePath);
	void load(string FilePath, AssetList assetList);
	void load(string FilePath, AssetList assetList, AssetList *globalList);
	void load(string FilePath, string assetListFilePath, AssetList *globalList);
	void unloadAssets();
	void unload();
	void setGlobalAssetList(AssetList *globalList);
	void setAssetList(AssetList toSet);
	void setRenderer(Renderer *toSet);
	Renderer *getRenderer();
	AssetList getAssetList();
	void setFilePath(string filePath);
	string getFilePath();
	void getModel(string modelName);
	Model* getModelArray();
	void setSceneType(int typeToSet);
	int getSceneType();

	void add(Camera *toAdd);
	void add(Drawable *toAdd);
	void add(Shader *toAdd);

	Scene();
	Scene(string FilePath);
	Scene(string FilePath, string assetListFilePath);
	Scene(string FilePath, AssetList assetList);
	Scene(string FilePath, AssetList assetList, AssetList *globalList);
	Scene(string FilePath, string assetListFilePath, AssetList *globalList);
	~Scene();
};