#ifndef __NIMBUS_WORLDMANAGER
#define __NIMBUS_WORLDMANAGER

#include <vector>

#include <OgreRoot.h>

namespace Nimbus
{
	using namespace Ogre;

	class WorldManager
	{
		// MEMBER ATTRIBUTES
	private:
		// Tells whether or not the manager has been initialized
		bool initialized;

		// Tile information
		std::vector<int> tileCount;
		std::vector<int> worldSize;

		// Represents the world's tile map with a vector of vectors of [chars]. (NOTE: Temp until tile class exists.)
		std::vector< std::vector<char> > tiles;

		// Represents our map's vector field with a vector of vectores of ogre vectors.
		std::vector< std::vector<Ogre::Vector2> > vectors;

		// MEMBER METHODS
	public:
		// CONSTRUCTORS --
		WorldManager(int tileCountX, int tileCountY, int worldWidth, int worldHeight);

		// DESTRUCTOR
		~WorldManager();

		// MAINTENANCE FUNCTIONS
		void init(void);
		bool update(void);
	};
}

#endif