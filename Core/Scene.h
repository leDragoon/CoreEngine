#pragma once
#include<Audio.h>
#include<AssetListFile.h>
#include<Renderer.h>
#include<Physics.h>
#include<SceneFile.h>
#include<LightFile.h>
#include<Texture.h>
#include<Script.h>
#include<UserInterfaceFile.h>

class Scene
{
private:
	Renderer *renderer;
	AudioHandler *audioHandler;
	PhysicsHandler *physicsHandler;
	ScriptHandler *scriptHandler;
	int sceneType = 0;
	string sceneName;
	string filePath;
	AssetList *globalAssetList;
	AssetList sceneAssetList;
	Model quadModel;
	vector<Model> sceneModels;
	vector<Camera> sceneCameras;
	Camera sceneCamera;
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
	void setAudioHandler(AudioHandler *toSet);
	void setPhysicsHandler(PhysicsHandler *toSet);
	void setScriptHandler(ScriptHandler *toSet);
	Renderer *getRenderer();
	AudioHandler *getAudioHandler();
	PhysicsHandler *getPhysicsHandler();
	ScriptHandler *getScriptHandler();
	AssetList getAssetList();
	Camera *getCamera();
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