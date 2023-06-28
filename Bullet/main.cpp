#include <iostream>
#include <memory>
#include <fmt/format.h>
#include <btBulletDynamicsCommon.h>

int main()
{
	// Note bullet really likes to use raw pointers under the hood
	auto *broadphase = new btDbvtBroadphase();
	auto *collisionConfiguration = new btDefaultCollisionConfiguration();
	auto *dispatcher = new btCollisionDispatcher(collisionConfiguration);
	auto *solver = new btSequentialImpulseConstraintSolver;
	auto *dynamicsWorld = new btDiscreteDynamicsWorld(dispatcher, broadphase, solver, collisionConfiguration);

	// Set gravity
	dynamicsWorld->setGravity(btVector3(0, -9.82, 0));
	// create static ground plane
	auto *groundShape = new btStaticPlaneShape(btVector3(0, 1, 0), 1);

	auto *fallShape = new btSphereShape(1);

	auto *groundMotionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(0, -1, 0)));
	btRigidBody::btRigidBodyConstructionInfo
		groundRigidBodyCI(0, groundMotionState, groundShape, btVector3(0, 0, 0));
	auto *groundRigidBody = new btRigidBody(groundRigidBodyCI);
	dynamicsWorld->addRigidBody(groundRigidBody);

	auto *fallMotionState =
		new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(0, 50, 0)));
	btScalar mass = 1;
	btVector3 fallInertia(2, 1, 2);
	fallShape->calculateLocalInertia(mass, fallInertia);
	btRigidBody::btRigidBodyConstructionInfo fallRigidBodyCI(mass, fallMotionState, fallShape, fallInertia);
	auto *fallRigidBody = new btRigidBody(fallRigidBodyCI);
	dynamicsWorld->addRigidBody(fallRigidBody);

	for (int i = 0; i < 300; i++)
	{
		dynamicsWorld->stepSimulation(1 / 60.f, 10);

		btTransform trans;
		fallRigidBody->getMotionState()->getWorldTransform(trans);
		fmt::print("{} {} {} \n", trans.getOrigin().getX(), trans.getOrigin().getY(), trans.getOrigin().getZ());
	}
	std::cout << '\n';
	dynamicsWorld->removeRigidBody(fallRigidBody);

	// if only we had smart pointers :-)
	delete fallRigidBody->getMotionState();
	delete fallRigidBody;
	dynamicsWorld->removeRigidBody(groundRigidBody);
	delete groundRigidBody->getMotionState();
	delete groundRigidBody;
	delete fallShape;
	delete groundShape;
	delete dynamicsWorld;
	delete solver;
	delete collisionConfiguration;
	delete dispatcher;
	delete broadphase;

	return 0;
}
