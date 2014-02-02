#include <iostream>
#include <windows.h>

#include <OgreRoot.h>

#include "NimbusPrototype.h"

#ifdef __cplusplus
extern "C" {
#endif

int main(int argc, char *argv[])
{
	// Create application object
    NimbusPrototype app;
	
	try {
		app.go();
	} catch( Ogre::Exception& e ) {
		std::cerr << "An exception has occured: " << e.getFullDescription().c_str() << std::endl;
	}

	return 0;
}

#ifdef __cplusplus
}
#endif