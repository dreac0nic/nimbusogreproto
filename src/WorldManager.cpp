#include "WorldManager.h"

namespace Nimbus
{
	// CONSTRUCTORS -----------------------------------
	WorldManager::WorldManager(int tileCountX, int tileCountY, int worldWidth, int worldHeight):
		tileCount(tileCountX, tileCountY), worldSize(worldWidth, worldHeight)
	{
		// Constructor
		this->initialized = false;
	}

	// DESTRUCTOR   -----------------------------------
	WorldManager::~WorldManager(void)
	{
		// Destructor
	}

	// MAINTENANCE FUNCTIONS --------------------------
	/* init functin intializes the world, primarily
	 *   allowing each of its delegates to get a chance
	 *   for an initial run before update cycles begin.
	 */
	void WorldManager::init(void)
	{
		// After we're all done, mark as initialized
		this->initialized = true;
	}

	/* update function runs an update cycle on each of its
	 * delegates.
	 */
	bool WorldManager::update(void)
	{
		// Check to see if manager has been initialized.
		if(!this->initialized) return false;

		// Update Vectors
		// Update Clouds
		// Update Tiles

		return true;
	}
}