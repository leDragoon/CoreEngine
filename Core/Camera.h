#pragma once
#include<DirectXMath.h>
#include<string>

#define PI 3.14159265359f

using std::string;
using namespace DirectX;
using namespace std;

class Camera
{
private:
	string name;
	XMFLOAT3 position = XMFLOAT3(0.0f, 0.0f, 0.0f);
	XMFLOAT3 target = XMFLOAT3(0.0f, 0.0f, 0.0f);
	XMFLOAT3 forward = XMFLOAT3(0.0f, 0.0f, 0.0f);
	XMFLOAT3 right = XMFLOAT3(0.0f, 0.0f, 0.0f);
	XMFLOAT3 up = XMFLOAT3(0.0f, 0.0f, 0.0f);
	XMFLOAT3 rotateAroundPoint = XMFLOAT3(0.0f, 0.0f, 0.0f);
	XMFLOAT4X4 view;
	XMFLOAT4X4 projection;
	float rotationRadius = 15.0f;
	float theta = (3.0f * PI) / 2.0f;
	float phi = PI / 2;
	float pitch = 0.0f;
	float yaw = 0.0f;
	float roll = 0.0f;
	int renderWidth = 1;
	int renderHeight = 1;
	float fieldOfView = 45.0f;
	bool orthoPerspective = false;
	bool rotationMode = false;
	void update();
	void updateProjection();
public:
	void initialize();
	void setPosition(XMFLOAT3 toSet);
	void move(XMFLOAT3 toSet);
	void setPitch(float toSet);
	void pitchCamera(float toSet);
	void setYaw(float toSet);
	void yawCamera(float toSet);
	void setRoll(float toSet);
	void rollCamera(float toSet);
	void setRotation(XMFLOAT3 toSet);
	void rotate(XMFLOAT3 toRotate);
	void setFieldOfView(float toSet);
	void setRotationRadius(float toSet);
	float getRotationRadius();
	void setRotateAroundPoint(XMFLOAT3 toSet);
	float getFieldOfView();
	void setRenderDims(int width, int height);
	void setName(string toSet);
	XMFLOAT3 getViewDirection();
	string getName();
	XMFLOAT2 getRenderDims();
	XMFLOAT4X4 getViewMatrix();
	XMFLOAT4X4 getProjectionMatrix();
	XMFLOAT3 getPosition();
	XMFLOAT3 getRotation();
	XMFLOAT3 getRotateAroundPoint();
	XMFLOAT3 getForward();

	Camera();
	Camera(XMFLOAT3 pos);
	Camera(XMFLOAT3 pos, XMFLOAT3 rot);
	Camera(XMFLOAT3 pos, XMFLOAT3 rot, int RenderWidth, int RenderHeight);
};

class FirstPersonCamera : public Camera
{

};

class ThirdPersonCamera : public Camera
{

};