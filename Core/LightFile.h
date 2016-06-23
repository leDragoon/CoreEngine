#pragma once
#include<FileManager.h>
#include<Light.h>
#include<Util.h>

class LightFile : public File
{
private:
	Light light;
	void parse();
public:
	 Light getLight();
	 Light loadLightFile(string path);
	 LightFile();
	 LightFile(string path);
};