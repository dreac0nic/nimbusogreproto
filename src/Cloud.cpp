#include "Cloud.h"

namespace Nimbus
{
	// INTIALIZE CLASS VARIABLES
	//   Not necessary under most C++ standards, and especially C++11,
	//   but kept for consistancy of initialization.
	unsigned long long int Cloud::count = 0;

	// CONSTRUCTORS -----------------------------------
	Cloud::Cloud(int width, int height):
		mDimensions(width, height)
	{
		// Initialize the cloud's name.
		stringstream buffer;

		buffer << "cloud" << Cloud::count;

		this->mName = buffer.str();

		// Incremement count of the clouds.
		Cloud::count++;

		// Set the cloud as uninitialized.
		this->initialized = false;
	}

	// DESTRUCTOR    ----------------------------------
	Cloud::~Cloud(void)
	{
		// Decrement count of the clouds.
		Cloud::count--;
		
		// Check for environment security.
		if(Cloud::count < 0)
			std::cerr << "OHGOODNESSWHATHAPPENEDSOMETHINGBROKEWOWYOU'RESCREWEDCLOUDSAREINVADINGOHSNAP" << std::endl;
	}

	// INITIALIZE    ----------------------------------
	void Cloud::init(SceneManager* sceneManager, std::string cloudPlaneName)
	{
		// Make sure the cloud isn't already initialized.
		if(this->initialized) // || !sceneManager->hasSceneNode(cloudPlaneName)) return;
		{
			return;
		}

		if(!sceneManager->hasSceneNode(cloudPlaneName))
		{
			//sceneManager->getRootSceneNode()->addChild(sceneManager->createSceneNode(cloudPlaneName));
			return;
		}

		// Create the entity and node.
		this->mCloudEntity = sceneManager->createEntity(this->mName.c_str(), "ogrehead.mesh");
		this->mCloudNode = sceneManager->getSceneNode(cloudPlaneName)->createChildSceneNode((this->mName + "_node"));

		// Add the entity to the node.
		this->mCloudNode->attachObject(mCloudEntity);

		this->initialized = true;
	}

	// UPDATE        ----------------------------------
	void Cloud::update(Vector2 affectedVector)
	{
		Vector3 realVector = Vector3::ZERO;

		realVector.x = affectedVector.x;
		realVector.z = affectedVector.y;

		this->mCloudNode->translate(realVector);
	}
}