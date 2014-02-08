#ifndef __NIMBUS_CLOUD
#define __NIMBUS_CLOUD

#include <vector>

#include <OgreRoot.h>

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
		// Holds the width and height of the cloud's dimensions.
		std::vector<int> mDimensions;

		// MEMBER METHODS
	public:
		// CONSTRUCTIONS --
		Cloud(int width, int height);

		// DESTRUCTOR
		~Cloud(void);
	};
}

#endif