#ifndef __NIMBUS_WORLDMANAGER
#define __NIMBUS_WORLDMANAGER

#include <vector>

#include <math.h>

#include <OgreRoot.h>

#include "Tile.h"
#include "Cloud.h"

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
		std::vector<int> mTileCount;
		std::vector<int> worldSize;

		// Represents the world's tile map with a vector of vectors of [chars]. (NOTE: Temp until tile class exists.)
		std::vector< std::vector<Nimbus::Tile*> > mTiles;

		// Represents our map's vector field with a vector of vectores of ogre vectors. Number of vectors currently dependent on tiles (1:1), but could be changed in the future.
		std::vector< std::vector<Ogre::Vector2> > mVectors;

		// Holds all the clouds!
		std::vector<Cloud*> mClouds;

		// Holds the world's cloud plane, allowing the clouds to be moved as one unit.
		SceneNode* mCloudPlane;

		// MEMBER METHODS
	public:
		// CONSTRUCTORS --
		WorldManager(int tileCountX, int tileCountY, int worldWidth, int worldHeight);

		// DESTRUCTOR
		~WorldManager(void);

		// MAINTENANCE FUNCTIONS
		void init(SceneManager* sceneManager);
		bool update(void);
	};
}

#endif