#ifndef __NIMBUS_CLOUD
#define __NIMBUS_CLOUD

#include <vector>

#include <OgreRoot.h>
#include <OgreEntity.h>

namespace Nimbus
{
	using namespace Ogre;

	class Cloud
	{
	private:
		// CLASS ATTRIBUTES
		// Represents the number of current active clouds, could implement a counting class.
		static unsigned long long int count;

		// MEMBER ATTRIBUTES
		// Tells whether or not the cloud has been initialized.
		bool initialized;

		// Holds this specific cloud's name.
		std::string mName;

		// Holds the width and height of the cloud's dimensions.
		std::vector<int> mDimensions;

		// Ogre Objects
		Entity* mCloudEntity;
		SceneNode* mCloudNode;

		// MEMBER METHODS
	public:
		// CONSTRUCTIONS --
		Cloud(int width, int height);

		// DESTRUCTOR --
		~Cloud(void);

		// ACCESSOR METHODS --
		int getWidth(void) { return this->mDimensions[0]; }
		int getHeight(void) { return this->mDimensions[1]; }
		void setWidth(int width) { this->mDimensions[0] = width; }
		void setHeight(int height) { this->mDimensions[1] = height; }

		// OBJECT METHODS --
		void init(SceneManager* sceneManager, std::string cloudPlaneName);
		void update(Vector2 affectedVector);
	};
}

#endif