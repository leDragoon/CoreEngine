#include "Light.h"

void Light::update()
{

}

void Light::setLightType(int toSet)
{
	lightType = toSet;
}

int Light::getLightType()
{
	return lightType;
}

void Light::setLightTemperature(float toSet)
{
	lightTemperature = toSet;
}

float Light::getLightTemperature()
{
	return lightTemperature;
}

void Light::setLightColor(XMFLOAT3 color)
{
	lightColor = color;
}

XMFLOAT3 Light::getLightColor()
{
	return lightColor;
}

void Light::setLightDirection(XMFLOAT3 direction)
{
	XMVECTOR dirNorm = XMVector3Normalize(XMVectorSet(direction.x, direction.y, direction.z, 1.0f));
	lightDirection = XMFLOAT3(XMVectorGetX(dirNorm), XMVectorGetY(dirNorm), XMVectorGetZ(dirNorm));
}

XMFLOAT3 Light::getLightDirection()
{
	return lightDirection;
}

void Light::setLightPosition(XMFLOAT3 position)
{
	lightPosition = position;
}

XMFLOAT3 Light::getLightPosition()
{
	return lightPosition;
}

void Light::setLightIntensity(float toSet)
{
	lightIntensity = toSet;
}

float Light::getLightIntensity()
{
	return lightIntensity;
}

void Light::setLightAttenuationRange(float toSet)
{
	lightAttenuationRange = toSet;
}

float Light::getLightAttenuationRange()
{
	return lightAttenuationRange;
}

void Light::setName(string toSet)
{
	name = toSet;
}

string Light::getName()
{
	return name;
}


Light::Light()
{
	update();
}

Light::Light(int type, XMFLOAT3 color, float intensity, float range)
{
	lightType = type;
	lightColor = color;
	lightIntensity = intensity;
	lightAttenuationRange = range;
	update();
}

Light::Light(string path)
{

}
