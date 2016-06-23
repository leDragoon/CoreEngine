#pragma once
#include<DirectXMath.h>
#include<vector>
#include<string>
#include<btBulletCollisionCommon.h>
#include<btBulletDynamicsCommon.h>

using std::vector;
using std::string;
using namespace DirectX;

class PhysicsHandler
{
private:
	int physicsIterations;
	int frameRate;
	vector<string> shapeNames;
	vector<btRigidBody*> physicsShapes;
	btDiscreteDynamicsWorld *physicsWorld;
	btBroadphaseInterface *broadphase;
	btDefaultCollisionConfiguration *collisionConfig;
	btCollisionDispatcher *collisionDispatcher;
	btSequentialImpulseConstraintSolver *constraintSolver;
public:
	void init();
	void update();
	void close();
	void setPhysicsIterations(int toSet);
	void setFrameRate(int toSet);
	void addBox(string name, XMFLOAT3 position, XMFLOAT3 rotation, XMFLOAT3 scale);
	void moveObject(string name, XMFLOAT3 toMove);
	void rotateObject(string name, XMFLOAT3 toRotate);
	void scaleObject(string name, XMFLOAT3 toScale);
	void setObjectPosition(string name, XMFLOAT3 toMove);
	void setObjectRotation(string name, XMFLOAT3 toRotate);
	void setObjectScale(string name, XMFLOAT3 toScale);
	void deleteObject(string name);

	~PhysicsHandler();
};
