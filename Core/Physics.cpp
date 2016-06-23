#include "Physics.h"

void PhysicsHandler::init()
{
	physicsIterations = 300;
	frameRate = 60;
	broadphase = new btDbvtBroadphase();
	collisionConfig = new btDefaultCollisionConfiguration();
	collisionDispatcher = new btCollisionDispatcher(collisionConfig);
	constraintSolver = new btSequentialImpulseConstraintSolver();

	physicsWorld = new btDiscreteDynamicsWorld(collisionDispatcher, broadphase, constraintSolver, collisionConfig);
	physicsWorld->setGravity(btVector3(0.0f, 0.0f, 0.0f));
}

void PhysicsHandler::update()
{
	for (int i = 0; i < physicsIterations; i++)
	{
		physicsWorld->stepSimulation((btScalar)1.0 / frameRate, 10);
	}
}

void PhysicsHandler::close()
{
	for (unsigned int i = 0; i < physicsShapes.size(); i++)
	{
		physicsWorld->removeRigidBody(physicsShapes[i]);
		//delete physicsShapes[i]->getMotionState();
		//delete physicsShapes[i];
	}

	//delete physicsWorld;
	//delete broadphase;
	//delete collisionConfig;
	//delete collisionDispatcher;
	//delete constraintSolver;
}

void PhysicsHandler::setPhysicsIterations(int toSet)
{
	physicsIterations = toSet;
}

void PhysicsHandler::setFrameRate(int toSet)
{
	frameRate = toSet;
}

void PhysicsHandler::addBox(string name, XMFLOAT3 position, XMFLOAT3 rotation, XMFLOAT3 scale)
{
	shapeNames.push_back(name);

	btCollisionShape *boxShape = new btBoxShape(btVector3(scale.x, scale.y, scale.z));
	btDefaultMotionState *groundMotionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(0, -1, 0)));
	btRigidBody::btRigidBodyConstructionInfo cInfo = btRigidBody::btRigidBodyConstructionInfo(1.0, groundMotionState, boxShape);

	btRigidBody *boxRigidBody = new btRigidBody(cInfo);
	physicsWorld->addRigidBody(boxRigidBody);

	delete boxShape;
	delete groundMotionState;
	delete boxRigidBody;
}

void PhysicsHandler::moveObject(string name, XMFLOAT3 toMove)
{
	
}

void PhysicsHandler::rotateObject(string name, XMFLOAT3 toRotate)
{

}

void PhysicsHandler::scaleObject(string name, XMFLOAT3 toScale)
{

}

void PhysicsHandler::setObjectPosition(string name, XMFLOAT3 toMove)
{
	
}

void PhysicsHandler::setObjectRotation(string name, XMFLOAT3 toRotate)
{

}

void PhysicsHandler::setObjectScale(string name, XMFLOAT3 toScale)
{

}

void PhysicsHandler::deleteObject(string name)
{
	
}


PhysicsHandler::~PhysicsHandler()
{
	close();
}
