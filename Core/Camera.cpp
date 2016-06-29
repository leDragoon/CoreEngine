#include "Camera.h"

void Camera::initialize()
{
	update();
	updateProjection();
}

void Camera::update()
{
	float pitchr = XMConvertToRadians(pitch);
	float yawr = XMConvertToRadians(yaw);
	float rollr = XMConvertToRadians(roll + 270);

	up = XMFLOAT3(0.0f, 1.0f, 0.0f);
	XMVECTOR defForward = XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f);
	XMVECTOR defRight = XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f);

	XMMATRIX rotMatrix = XMMatrixRotationRollPitchYaw(pitchr, yawr, rollr);
	XMStoreFloat3(&target, XMVector3TransformCoord(defForward, rotMatrix));
	XMStoreFloat3(&target, XMVector3Normalize(XMLoadFloat3(&target)));

	XMMATRIX rotY = XMMatrixRotationY(yawr);
	XMMATRIX rotZ = XMMatrixRotationZ(rollr);
	rotY = XMMatrixMultiply(rotY, rotZ);

	XMStoreFloat3(&right, XMVector3TransformCoord(defRight, rotY));
	XMStoreFloat3(&up, XMVector3TransformCoord(XMLoadFloat3(&up), rotY));
	XMStoreFloat3(&forward, XMVector3TransformCoord(defForward, rotY));

	XMStoreFloat3(&target, XMLoadFloat3(&target) + XMLoadFloat3(&position));
	
	if (rotationMode == true)
	{
		up = XMFLOAT3(0.0f, 1.0f, 0.0f);
		target = rotateAroundPoint;

		position.x = rotateAroundPoint.x + (rotationRadius * cosf(theta) * sinf(phi));
		position.y = rotateAroundPoint.y + (-(rotationRadius * cosf(phi)));
		position.z = rotateAroundPoint.z + (rotationRadius * sinf(theta) * sinf(phi));
	}

	XMStoreFloat4x4(&view, XMMatrixLookAtLH(XMLoadFloat3(&position), XMLoadFloat3(&target), XMLoadFloat3(&up)));
}

void Camera::setPosition(XMFLOAT3 toSet)
{
	if (rotationMode == false)
	{
		position = toSet;
	}

	else
	{
		rotateAroundPoint = toSet;
	}

	update();
}

void Camera::move(XMFLOAT3 toSet)
{
	if (rotationMode == false)
	{
		XMStoreFloat3(&position, XMLoadFloat3(&position) + toSet.x * XMLoadFloat3(&right));
		XMStoreFloat3(&position, XMLoadFloat3(&position) + toSet.y * XMLoadFloat3(&up));
		XMStoreFloat3(&position, XMLoadFloat3(&position) + toSet.z * XMLoadFloat3(&forward));
	}

	else
	{
		rotateAroundPoint.x += toSet.x;
		rotateAroundPoint.y += toSet.y;
		rotateAroundPoint.z += toSet.z;
	}

	update();
}

void Camera::setPitch(float toSet)
{
	if (rotationMode == false)
	{
		pitch = toSet;
		update();
	}
}

void Camera::pitchCamera(float toSet)
{
	if (rotationMode == false)
	{
		pitch += toSet;
	}

	else
	{
		phi += toSet;
	}

	update();
}

void Camera::setYaw(float toSet)
{
	if (rotationMode == false)
	{
		yaw = toSet;
		update();
	}
}

void Camera::yawCamera(float toSet)
{
	if (rotationMode == false)
	{
		yaw += toSet;
		
	}
	else
	{
		theta += toSet;
	}

	update();
}

void Camera::setRoll(float toSet)
{
	if (rotationMode == false)
	{
		roll = toSet;
		update();
	}
}

void Camera::rollCamera(float toSet)
{
	if (rotationMode == false)
	{
		roll += toSet;
		update();
	}
}

void Camera::setRotation(XMFLOAT3 toSet)
{
	if (rotationMode == false)
	{
		pitch = toSet.x;
		yaw = toSet.y;
		roll = toSet.z;
		update();
	}
}

void Camera::rotate(XMFLOAT3 toRotate)
{
	if (rotationMode == false)
	{
		pitch += toRotate.x;
		yaw += toRotate.y;
		roll += toRotate.z;
		update();
	}
}

XMFLOAT3 Camera::getPosition()
{
	return position;
}

XMFLOAT3 Camera::getRotation()
{
	XMFLOAT3 toReturn = XMFLOAT3(pitch, yaw, roll);
	return toReturn;
}

XMFLOAT3 Camera::getRotateAroundPoint()
{
	return rotateAroundPoint;
}

XMFLOAT3 Camera::getForward()
{
	return forward;
}

XMFLOAT3 Camera::getViewDirection()
{
	return XMFLOAT3(view._13, view._23, view._33);
}

void Camera::setFieldOfView(float toSet)
{
	fieldOfView = toSet;
	updateProjection();
}

void Camera::setRotationRadius(float toSet)
{
	rotationMode = true;
	rotationRadius = toSet;
}

float Camera::getRotationRadius()
{
	return rotationRadius;
}

void Camera::setRotateAroundPoint(XMFLOAT3 toSet)
{
	rotateAroundPoint = toSet;
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

XMFLOAT4X4 Camera::getViewMatrix()
{
	return view;
}

XMFLOAT4X4 Camera::getProjectionMatrix()
{
	return projection;
}

void Camera::updateProjection()
{
	if (orthoPerspective == false)
	{
		XMStoreFloat4x4(&projection, XMMatrixPerspectiveFovLH(XMConvertToRadians(fieldOfView), (float)renderHeight / renderWidth, 1.0, 1000.0));
		//XMStoreFloat4x4(&projection, XMMatrixPerspectiveFovLH(XMConvertToRadians(fieldOfView), (float)renderWidth / renderHeight, 1.0, 1000.0));
	}

	else
	{
		XMStoreFloat4x4(&projection, XMMatrixOrthographicLH((float)renderWidth, (float)renderHeight, 1.0, 1000.0));
	}
}

Camera::Camera()
{
	position = XMFLOAT3(0.0f, 0.0f, 0.0f);
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
