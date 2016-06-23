#pragma once
#include<FileManager.h>
#include<DirectXMath.h>
#include<Util.h>

#define CORE_OBJECTTYPE_MODEL 1
#define CORE_OBJECTTYPE_SKYMAP 2
#define CORE_OBJECTTYPE_LIGHTPROBE 3
#define CORE_OBJECTTYPE_SOUND 4
#define CORE_OBJECTTYPE_CAMERA 10

using std::stof;

struct ObjectInstance
{
	int type = 0;
	string objectName;
	int identifier = 0;
	vector<string> scripts;
	DirectX::XMFLOAT3 position, rotation, scale;
};

class SceneFile : public File
{
private:
	void parse();
	void assignObjectInstanceIdentifiers();
	string sceneName = "";
	vector<ObjectInstance> objectInstances;
public:
	void loadFile();
	void loadFile(string path);
	vector<ObjectInstance> getObjectInstances();
	string getSceneName();

	SceneFile();
	SceneFile(string path);
};