#include "Camera.h"

void Camera::initialize()
{
	update();
	updateProjection();
}

void Camera::update()
{
	up = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
	XMVECTOR defForward = XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f);
	XMVECTOR defRight = XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f);

	XMMATRIX rotMatrix = XMMatrixRotationRollPitchYaw(pitch, yaw, roll);
	target = XMVector3TransformCoord(defForward, rotMatrix);
	target = XMVector3Normalize(target);

	XMMATRIX rotY = XMMatrixRotationY(yaw);

	right = XMVector3TransformCoord(defRight, rotY);
	up = XMVector3TransformCoord(up, rotY);
	forward = XMVector3TransformCoord(defForward, rotY);

	target = position + target;
	view = XMMatrixLookAtLH(position, target, up);
}

void Camera::setPosition(XMFLOAT3 toSet)
{
	position = DirectX::XMVectorSet(toSet.x, toSet.y, toSet.z, 0.0f);
	update();
}

void Camera::move(XMFLOAT3 toSet)
{
	position += toSet.x * right;
	position += toSet.y * up;
	position += toSet.z * forward;
	update();
}

void Camera::setPitch(float toSet)
{
	pitch = toSet;
	update();
}

void Camera::pitchCamera(float toSet)
{
	pitch += toSet;
	update();
}

void Camera::setYaw(float toSet)
{
	yaw = toSet;
	update();
}

void Camera::yawCamera(float toSet)
{
	yaw += toSet;
	update();
}

void Camera::setRoll(float toSet)
{
	roll = toSet;
	update();
}

void Camera::rollCamera(float toSet)
{
	roll += toSet;
	update();
}

void Camera::setRotation(XMFLOAT3 toSet)
{
	pitch = toSet.x;
	yaw = toSet.y;
	roll = toSet.z;
	update();
}

void Camera::rotate(XMFLOAT3 toRotate)
{
	pitch += toRotate.x;
	yaw += toRotate.y;
	roll += toRotate.z;
	update();
}

XMFLOAT3 Camera::getPosition()
{
	XMFLOAT3 toReturn;
	XMStoreFloat3(&toReturn, position);
	return toReturn;
}

XMFLOAT3 Camera::getRotation()
{
	XMFLOAT3 toReturn = XMFLOAT3(pitch, yaw, roll);
	return toReturn;
}

void Camera::setFieldOfView(float toSet)
{
	fieldOfView = toSet;
	updateProjection();
}

float Camera::getFieldOfView()
{
	return fieldOfView;
}

void Camera::setRenderDims(int width, int height)
{
	renderWidth = width;
	renderHeight = height;
	updateProjection();
}

void Camera::setName(string toSet)
{
	name = toSet;
}

string Camera::getName()
{
	return name;
}

XMFLOAT2 Camera::getRenderDims()
{
	return XMFLOAT2((float)renderWidth, (float)renderHeight);
}

XMMATRIX Camera::getViewMatrix()
{
	return view;
}

XMMATRIX Camera::getProjectionMatrix()
{
	return projection;
}

void Camera::updateProjection()
{
	if (orthoPerspective == false)
	{
		projection = XMMatrixPerspectiveFovLH(XMConvertToRadians(fieldOfView), (float)renderWidth / renderHeight, 1.0, 1000.0);
	}

	else
	{
		projection = XMMatrixOrthographicLH((float)renderWidth, (float)renderHeight, 1.0, 1000.0);
	}
}

Camera::Camera()
{
	position = XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);
	pitch = 0;
	yaw = 0;
	roll = 0;
	orthoPerspective = false;
}

Camera::Camera(XMFLOAT3 pos)
{
	setPosition(pos);
	pitch = 0;
	yaw = 0;
	roll = 0;
	orthoPerspective = false;
}

Camera::Camera(XMFLOAT3 pos, XMFLOAT3 rot)
{
	setPosition(pos);
	setRotation(rot);
	orthoPerspective = false;
}

Camera::Camera(XMFLOAT3 pos, XMFLOAT3 rot, int RenderWidth, int RenderHeight)
{
	setPosition(pos);
	setRotation(rot);
	renderWidth = RenderWidth;
	renderHeight = RenderHeight;
	orthoPerspective = false;
	initialize();
}
