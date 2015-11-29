#pragma once
#include<DirectXMath.h>
#include<string>

using std::string;
using namespace DirectX;

class Camera
{
private:
	string name;
	XMVECTOR position;
	XMVECTOR target;
	XMVECTOR forward;
	XMVECTOR right;
	XMVECTOR up;
	XMMATRIX view;
	XMMATRIX projection;
	float pitch;
	float yaw;
	float roll;
	int renderWidth;
	int renderHeight;
	float fieldOfView;
	bool orthoPerspective;
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
	float getFieldOfView();
	void setRenderDims(int width, int height);
	void setName(string toSet);
	string getName();
	XMFLOAT2 getRenderDims();
	XMMATRIX getViewMatrix();
	XMMATRIX getProjectionMatrix();
	XMFLOAT3 getPosition();
	XMFLOAT3 getRotation();

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