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
		// Incremement count of the clouds.
		Cloud::count++;
	}

	// DESTRUCTOR   ----------------------------------
	Cloud::~Cloud(void)
	{
		// Decrement count of the clouds.
		Cloud::count--;
		
		// Check for environment security.
		if(Cloud::count < 0)
			std::cerr << "OHGOODNESSWHATHAPPENEDSOMETHINGBROKEWOWYOU'RESCREWEDCLOUDSAREINVADINGOHSNAP" << std::endl;
	}
}