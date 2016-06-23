#pragma once
#include<DirectXMath.h>
#include<string>

#define CORE_LIGHTTYPE_POINT 0
#define CORE_LIGHTTYPE_DIRECTIONAL 1
#define CORE_LIGHTTYPE_SPOT 2
#define CORE_LIGHTTYPE_DISC 3
#define CORE_LIGHTTYPE_SPHERE 4
#define CORE_LIGHTTYPE_TUBE 5

using std::string;
using namespace DirectX;

class Light
{
private:
	int lightType = 0;
	float lightTemperature = 0;
	float lightIntensity = 0;
	float lightAttenuationRange = 0;
	float lightSize = 0;
	string name;
	XMFLOAT3 lightColor = XMFLOAT3(0.0f, 0.0f, 0.0f);
	XMFLOAT3 lightDirection = XMFLOAT3(0.0f, 0.0f, 0.0f);;
	XMFLOAT3 lightPosition = XMFLOAT3(0.0f, 0.0f, 0.0f);;
public:
	void update();
	void setLightType(int toSet);
	int getLightType();
	void setLightTemperature(float toSet);
	float getLightTemperature();
	void setLightColor(XMFLOAT3 color);
	XMFLOAT3 getLightColor();
	void setLightDirection(XMFLOAT3 direction);
	XMFLOAT3 getLightDirection();
	void setLightPosition(XMFLOAT3 position);
	XMFLOAT3 getLightPosition();
	void setLightIntensity(float toSet);
	float getLightIntensity();
	void setLightAttenuationRange(float toSet);
	float getLightAttenuationRange();
	void setName(string toSet);
	string getName();

	Light();
	Light(int type, XMFLOAT3 color, float intensity, float range);
	Light(string path);
};
