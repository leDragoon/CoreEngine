#pragma once
#include<FileManager.h>
#include<DirectXMath.h>
#include<Util.h>

#define CORE_GAMEOBJECTTYPE_MODEL 1

using std::stof;

struct ObjectInstance
{
	int type;
	string objectName;
	int identifier = 0;
	DirectX::XMFLOAT3 position, rotation, scale;
};

class SceneFile : public File
{
private:
	void parse();
	void assignObjectInstanceIdentifiers();
	string sceneName;
	vector<ObjectInstance> objectInstances;
public:
	void loadFile();
	void loadFile(string path);
	vector<ObjectInstance> getObjectInstances();
	string getSceneName();

	SceneFile();
	SceneFile(string path);
};