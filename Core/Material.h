#pragma once
#include<MaterialFile.h>
#include<vector>

using std::string;
using std::vector;

class Material
{
private:
	string name;
	int albedoTexture = -1;
	int roughnessTexture = -1;
	int metalnessTexture = -1;
	int normalTexture = -1;
	int radianceTexture = -1;
	int irradianceTexture = -1;
	vector<int> textureUsages;
	vector<string> textures;
	vector<string> vertexShaders;
	vector<string> pixelShaders;
public:
	void loadMaterial(string path, ID3D11Device **dev);
	void setName(string toSet);
	void setAlbedoTextureCode(int toSet);
	void setRoughnessTextureCode(int toSet);
	void setMetalnessTextureCode(int toSet);
	void setNormalTextureCode(int toSet);
	void setRadianceTextureCode(int toSet);
	void setIrradianceTextureCode(int toSet);
	int getAlbedoTextureCode();
	int getRoughnessTextureCode();
	int getMetalnessTextureCode();
	int getNormalTextureCode();
	int getRadianceTextureCode();
	int getIrradianceTextureCode();
	vector<int> getTextureUsages();
	vector<string> getTextureNames();
	vector<string> getVertexShaderNames();
	vector<string> getPixelShaderNames();
	string getName();
	void close();
	Material();
};