/*
-----------------------------------------------------------------------------
Filename:    TutorialApplication.cpp
-----------------------------------------------------------------------------

This source file is part of the
   ___                 __    __ _ _    _ 
  /___\__ _ _ __ ___  / / /\ \ (_) | _(_)
 //  // _` | '__/ _ \ \ \/  \/ / | |/ / |
/ \_// (_| | | |  __/  \  /\  /| |   <| |
\___/ \__, |_|  \___|   \/  \/ |_|_|\_\_|
      |___/                              
      Tutorial Framework
      http://www.ogre3d.org/tikiwiki/
-----------------------------------------------------------------------------
*/
#include "NimbusPrototype.h"

//-------------------------------------------------------------------------------------
NimbusPrototype::NimbusPrototype(void)
{
}

//-------------------------------------------------------------------------------------
NimbusPrototype::~NimbusPrototype(void)
{
}

//-------------------------------------------------------------------------------------
void NimbusPrototype::destroyScene(void)
{
	OGRE_DELETE mTerrainGroup;
	OGRE_DELETE mTerrainGlobals;
}

//-------------------------------------------------------------------------------------
void getTerrainImage(bool flipX, bool flipY, Ogre::Image& img)
{
	img.load("terrain.png", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);

	if(flipX) img.flipAroundY();

	if(flipY) img.flipAroundX();
}

//-------------------------------------------------------------------------------------
void NimbusPrototype::defineTerrain(long x, long y)
{
	Ogre::String filename = mTerrainGroup->generateFilename(x, y);

	if(Ogre::ResourceGroupManager::getSingleton().resourceExists(mTerrainGroup->getResourceGroup(), filename))
	{
		mTerrainGroup->defineTerrain(x, y);
	}
	else
	{
		Ogre::Image img;

		getTerrainImage((x%2) != 0, (y%2) != 0, img);
		mTerrainGroup->defineTerrain(x, y, &img);
		mTerrainsImported = true;
	}
}

//-------------------------------------------------------------------------------------
void NimbusPrototype::initBlendMaps(Ogre::Terrain* terrain)
{
	// Create blend maps for texture blending
	Ogre::TerrainLayerBlendMap* blendMap0 = terrain->getLayerBlendMap(1);
	Ogre::TerrainLayerBlendMap* blendMap1 = terrain->getLayerBlendMap(2);

	// Set up default terrain settings
	Ogre::Real minHeight0 = 70;
	Ogre::Real fadeDist0 = 40;
	Ogre::Real minHeight1 = 70;
	Ogre::Real fadeDist1 = 15;

	float* pBlend0 = blendMap0->getBlendPointer();
	float* pBlend1 = blendMap1->getBlendPointer();

	for(Ogre::uint16 y = 0 ; y < terrain->getLayerBlendMapSize(); ++y)
	{
		for(Ogre::uint16 x = 0; x < terrain->getLayerBlendMapSize(); ++x)
		{
			Ogre::Real tx, ty;

			blendMap0->convertImageToTerrainSpace(x, y, &tx, &ty);
			
			Ogre::Real height = terrain->getHeightAtTerrainPosition(tx, ty);
			Ogre::Real val = (height - minHeight0)/fadeDist0;

			val = Ogre::Math::Clamp(val, (Ogre::Real)0, (Ogre::Real)1);
			*pBlend0++ = val;

			val = (height - minHeight1)/fadeDist1;
			val = Ogre::Math::Clamp(val, (Ogre::Real)0, (Ogre::Real)1);
			*pBlend1++ = val;
		}
	}
	
	// Set blend maps to be updated
	blendMap0->dirty();
	blendMap1->dirty();

	// Update blend maps
	blendMap0->update();
	blendMap1->update();
}

//-------------------------------------------------------------------------------------
void NimbusPrototype::configureTerrainDefaults(Ogre::Light* light)
{
	// Configure globals.
	mTerrainGlobals->setMaxPixelError(8);
	
	// Test composites.
	mTerrainGlobals->setCompositeMapDistance(3000);

	// Set map globals for lighting.
	mTerrainGlobals->setLightMapDirection(light->getDerivedDirection());
	mTerrainGlobals->setCompositeMapAmbient(mSceneMgr->getAmbientLight());
	mTerrainGlobals->setCompositeMapDiffuse(light->getDiffuseColour());

	// Configure the settings for importing.
	Ogre::Terrain::ImportData& importConfig = mTerrainGroup->getDefaultImportSettings();
	importConfig.terrainSize = TERRAIN_SIZE;
	importConfig.worldSize = WORLD_SIZE;
	importConfig.inputScale = 600;
	importConfig.minBatchSize = 33;
	importConfig.maxBatchSize = 65;

	// Load some textures!
	importConfig.layerList.resize(3);
	
	importConfig.layerList[0].worldSize = 100;
	importConfig.layerList[0].textureNames.push_back("dirt_grayrocky_diffusespecular.dds");
	importConfig.layerList[0].textureNames.push_back("dirt_grayrocky_normalheight.dds");

	importConfig.layerList[1].worldSize = 30;
	importConfig.layerList[1].textureNames.push_back("grass_green-01_diffusespecular.dds");
	importConfig.layerList[1].textureNames.push_back("grass_green-01_normalheight.dds");

	importConfig.layerList[2].worldSize = 200;
	importConfig.layerList[2].textureNames.push_back("growth_weirdfungus-03_diffusespecular.dds");
	importConfig.layerList[2].textureNames.push_back("growth_weirdfungus-03_normalheight.dds");
}

//-------------------------------------------------------------------------------------
void NimbusPrototype::createScene(void)
{
	// Variables
	cameraLookAt = Ogre::Vector3(2150, 50, 1500);
	cameraPosition = Ogre::Vector3(cameraLookAt.x, cameraLookAt.y + 2450, cameraLookAt.z - 1200);

	// Setup camera, actually using a FAR CLIP PLANE this time.
	mCamera->setPosition(cameraPosition);
	mCamera->lookAt(cameraLookAt);
	mCamera->setNearClipDistance(0.1f);
	mCamera->setFarClipDistance(50000.0f);

	// Setup infinite far clip plane, if supported.
	if(mRoot->getRenderSystem()->getCapabilities()->hasCapability(Ogre::RSC_INFINITE_FAR_PLANE))
		mCamera->setFarClipDistance(0);

	// Setup some lighting.
	Ogre::Vector3 lightdir(0.55f, -0.3f, 0.75f);
	lightdir.normalise();

	Ogre::Light* sunLight = mSceneMgr->createLight("sceneLight");
	sunLight->setType(Ogre::Light::LT_DIRECTIONAL);
	sunLight->setDirection(lightdir);
	sunLight->setDiffuseColour(Ogre::ColourValue::White);
	sunLight->setSpecularColour(Ogre::ColourValue(0.4f, 0.4f, 0.4f));

	// -- Blarge, ambient light ...
	mSceneMgr->setAmbientLight(Ogre::ColourValue(0.2f, 0.2f, 0.2f));

	// Create terrain ...
	mTerrainGlobals = OGRE_NEW Ogre::TerrainGlobalOptions();

	mTerrainGroup = OGRE_NEW Ogre::TerrainGroup(mSceneMgr, Ogre::Terrain::ALIGN_X_Z, TERRAIN_SIZE, WORLD_SIZE);
	mTerrainGroup->setFilenameConvention(Ogre::String("BasicTutorial3Terrain"), Ogre::String("dat")); // TERRAIN LOADING
	mTerrainGroup->setOrigin(Ogre::Vector3::ZERO);

	this->configureTerrainDefaults(sunLight);
	
	// Define our terrains...?
	for(long x = 0; x <= 0; ++x)
		for(long y = 0; y <= 0; ++y)
			defineTerrain(x, y);

	// Force loading of all terrains before starting application.
	mTerrainGroup->loadAllTerrains(true);

	// Calculate blend maps.
	if(mTerrainsImported)
	{
		Ogre::TerrainGroup::TerrainIterator ti = mTerrainGroup->getTerrainIterator();

		while(ti.hasMoreElements())
		{
			Ogre::Terrain* t = ti.getNext()->instance;

			initBlendMaps(t);
		}
	}

	// Clean up terrain generation.
	mTerrainGroup->freeTemporaryResources();

	// Add skydome.
	mSceneMgr->setSkyDome(true, "Examples/CloudySky", 5.0f, 8.0f);
}

//-------------------------------------------------------------------------------------
void NimbusPrototype::createFrameListener(void)
{
	mCamNode = mSceneMgr->getSceneNode("BasicCamNode");
	mTopSpeed = 150;

	BaseApplication::createFrameListener();

	mInfoLabel = mTrayMgr->createLabel(OgreBites::TL_TOP, "TInfo", "", 350);
}

//-------------------------------------------------------------------------------------
bool NimbusPrototype::frameRenderingQueued(const Ogre::FrameEvent& event)
{
	bool ret = BaseApplication::frameRenderingQueued(event);

	if(mTerrainGroup->isDerivedDataUpdateInProgress())
	{
		mTrayMgr->moveWidgetToTray(mInfoLabel, OgreBites::TL_TOP, 0);
		mInfoLabel->show();

		if(mTerrainsImported) mInfoLabel->setCaption("Building terrain, please wait ...");
		else mInfoLabel->setCaption("Updating textures, please wait ...");
	}
	else
	{
		mTrayMgr->removeWidgetFromTray(mInfoLabel);
		mInfoLabel->hide();

		if(mTerrainsImported)
		{
			mTerrainGroup->saveAllTerrains(true);
			mTerrainsImported = false;
		}
	}

	mCamNode->translate(mDirection * event.timeSinceLastFrame, Ogre::Node::TS_LOCAL);

	cameraKeyAccel(event);

	return ret;
}


void NimbusPrototype::cameraKeyAccel(const Ogre::FrameEvent &event)
{
	// build our acceleration vector based on keyboard input composite
	Ogre::Vector3 accel = Ogre::Vector3::ZERO;
	if (mGoingForward) accel += Ogre::Vector3(mCamera->getDirection().x, 0, mCamera->getDirection().z);
	if (mGoingBack) accel -= Ogre::Vector3(mCamera->getDirection().x, 0, mCamera->getDirection().z);
	if (mGoingRight) accel += mCamera->getRight();
	if (mGoingLeft) accel -= mCamera->getRight();
	if (mGoingUp) accel += mCamera->getUp();
	if (mGoingDown) accel -= mCamera->getUp();

	// if accelerating, try to reach top speed in a certain time
	Ogre::Real topSpeed = mFastMove ? mTopSpeed * 20 : mTopSpeed;
	if (accel.squaredLength() != 0)
	{
		accel.normalise();
		mVelocity += accel * topSpeed * event.timeSinceLastFrame * 10;
	}
	// if not accelerating, try to stop in a certain time
	else mVelocity -= mVelocity * event.timeSinceLastFrame * 10;

	Ogre::Real tooSmall = std::numeric_limits<Ogre::Real>::epsilon();

	// keep camera velocity below top speed and above epsilon
	if (mVelocity.squaredLength() > topSpeed * topSpeed)
	{
		mVelocity.normalise();
		mVelocity *= topSpeed;
	}
	else if (mVelocity.squaredLength() < tooSmall * tooSmall)
		mVelocity = Ogre::Vector3::ZERO;

	if (mVelocity != Ogre::Vector3::ZERO) mCamera->move(mVelocity * event.timeSinceLastFrame);
}

//-------------------------------------------------------------------------------------
bool NimbusPrototype::mouseMoved(const OIS::MouseEvent &arg)
{
	mCamera->move(Ogre::Vector3(arg.state.X.rel, 0, arg.state.Y.rel));

	return true;
}

//-------------------------------------------------------------------------------------
bool NimbusPrototype::keyPressed( const OIS::KeyEvent &arg )
{
	switch (arg.key)
	{
	case OIS::KC_UP:
	case OIS::KC_W:
		mGoingForward = true;
		break;

	case OIS::KC_DOWN:
	case OIS::KC_S:
		mGoingBack = true;
		break;

	case OIS::KC_LEFT:
	case OIS::KC_A:
		mGoingLeft = true;
		break;

	case OIS::KC_RIGHT:
	case OIS::KC_D:
		mGoingRight = true;
		break;
	}

	return true;
}

//-------------------------------------------------------------------------------------
bool NimbusPrototype::keyReleased( const OIS::KeyEvent &arg )
{
	switch (arg.key)
	{
	case OIS::KC_UP:
	case OIS::KC_W:
		mGoingForward = false;
		break;

	case OIS::KC_DOWN:
	case OIS::KC_S:
		mGoingBack = false;
		break;

	case OIS::KC_LEFT:
	case OIS::KC_A:
		mGoingLeft = false;
		break;

	case OIS::KC_RIGHT:
	case OIS::KC_D:
		mGoingRight = false;
		break;
	}

	return true;
}