#include "WorldManager.h"

namespace Nimbus
{
	// CONSTRUCTORS -----------------------------------
	WorldManager::WorldManager(int tileCountX, int tileCountY, int worldWidth, int worldHeight):
		mTileCount(tileCountX, tileCountY), worldSize(worldWidth, worldHeight)
	{
		// Constructor
		this->initialized = false;
	}

	// DESTRUCTOR   ----------------------------------
	WorldManager::~WorldManager(void)
	{
		// Cleanup all of the tiles.
		if(this->initialized) {
			for(int x = 0; x < mTileCount[0]; ++x) {
				for(int y = 0; y < mTileCount[1]; ++y) {
					delete mTiles[x][y];
				}
			}

			for(unsigned int i = 0; i < mClouds.size(); ++i) {
				delete mClouds[i];
			}
		}
	}

	// MAINTENANCE FUNCTIONS --------------------------
	/* init functin intializes the world, primarily
	 *   allowing each of its delegates to get a chance
	 *   for an initial run before update cycles begin.
	 */
	void WorldManager::init(SceneManager* sceneManager)
	{
		// Setup cloud plane ...
		this->mCloudPlane = sceneManager->getRootSceneNode()->createChildSceneNode("cloudPlane");
		this->mCloudPlane->translate(Vector3::UNIT_Y * 1500);

		// Initialize datastructures ...
		//   Note: See mVectors description for explanation of vector count.
		mTiles.resize(mTileCount[0]);
		mVectors.resize(mTileCount[0]);

		for(int i = 0; i < mTileCount[0]; ++i) {
			mTiles[i].resize(mTileCount[1]);
			mVectors[i].resize(mTileCount[1]);

			for(int j = 0; j < mTileCount[1]; ++j)
				mVectors[i][j] = Ogre::Vector2::ZERO;
		}
		// Expand cloud datastructure.
		this->mClouds.resize(5);

		for(unsigned int i = 0; i < mClouds.size(); ++i) {
			 this->mClouds[i] =  new Cloud(10, 10);

			 this->mClouds[i]->init(sceneManager, "cloudPlane");
		}

		// Generate a bunch of random tiles.
		//   Note: "TILES"
		for(int x = 0; x < mTileCount[0]; ++x) {
			for(int y = 0; y < mTileCount[1]; ++y) {
				mTiles[x][y] = new Tile();
			}
		}

		// Generate a bunch of random vectors and normalize the result.
		//   Range: -10.0 to 10.0 with 1 digit to right of decimal.
		//   Todo: In the future, procedurally create a series of vectors.
		//   Note: See mVectors description for explanation of vector count.
		for(int x = 0; x < mTileCount[0]; ++x) {
			for(int y = 0; y < mTileCount[1]; ++y) {
				mVectors[x][y] = Ogre::Vector2((rand()%200 - 100)/10.0f, (rand()%100 - 100)/10.0f);

				mVectors[x][y].normalise();
			}
		}

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
		//   Note: Does nothing, but simulates iteration.
		for(int x = 0; x < mTileCount[0]; ++x) {
			for(int y = 0; y < mTileCount[1]; ++y) {
				mVectors[x][y].normalise();
			}
		}

		// Update Clouds
		for(unsigned int i = 0; i < this->mClouds.size(); ++i) {
			this->mClouds[i]->update(Vector2::ZERO);
		}
			

		// Update Tiles
		for(int x = 0; x < mTileCount[0]; ++x) {
			for(int y = 0; y < mTileCount[1]; ++y) {
				// Allow each tile to update itself.
				mTiles[x][y]->update();
			}
		}

		return true;
	}
}