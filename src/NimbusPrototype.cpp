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
void NimbusPrototype::chooseSceneManager(void)
{
	// Create the scene manager.
	mSceneMgr = mRoot->createSceneManager(Ogre::ST_EXTERIOR_REAL_FAR);

	// Create the OverlaySystem for use in the HUD later.
	mOverlaySystem = new Ogre::OverlaySystem();
	mSceneMgr->addRenderQueueListener(mOverlaySystem);
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
	// BLARGE DOCUMENT LATER JGNLKAJSDNGFLKAJSDNLKAJSNBLFASBHABSLFBALDSKJHFBLSAJKSDDHbfLKJABSFLKJBSALFKJBSALKJDBASLKJFHBALKJDGNLIUASNLIUABEWF
	Ogre::TerrainLayerBlendMap* blendMap0 = terrain->getLayerBlendMap(1);
	Ogre::TerrainLayerBlendMap* blendMap1 = terrain->getLayerBlendMap(2);

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

	blendMap0->dirty();
	blendMap1->dirty();

	blendMap0->update();
	blendMap1->update();
}

//-------------------------------------------------------------------------------------
void NimbusPrototype::configureTerrainDefaults(Ogre::Light* light)
{
	// Configure globals.
	mTerrainGlobals->setMaxPixelError(8);
	
	// Test composites.
	mTerrainGlobals->setCompositeMapDistance(12000);

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
	// Setup camera, actually using a FAR CLIP PLANE this time.
	mCamera->setPosition(Ogre::Vector3(1683, 50, 2116));
	mCamera->lookAt(Ogre::Vector3(1963, 50, 1660));
	mCamera->setNearClipDistance(0.1f);
	mCamera->setFarClipDistance(50000.0f);

	// Setup infinite far clip plane, if supported.
	if(mRoot->getRenderSystem()->getCapabilities()->hasCapability(Ogre::RSC_INFINITE_FAR_PLANE))
		mCamera->setFarClipDistance(0);

	// Setup some lighting.
	Ogre::Vector3 lightdir(0.55f, -0.3f, 0.75f);
	lightdir.normalise();

	Ogre::Light* light = mSceneMgr->createLight("sun");
	light->setType(Ogre::Light::LT_DIRECTIONAL);
	light->setDirection(lightdir);
	light->setDiffuseColour(Ogre::ColourValue::White);
	light->setSpecularColour(Ogre::ColourValue(0.4f, 0.4f, 0.4f));

	// -- Blarge, ambient light ...
	mSceneMgr->setAmbientLight(Ogre::ColourValue(0.1f, 0.1f, 0.1f));

	// Create terrain ...
	mTerrainGlobals = OGRE_NEW Ogre::TerrainGlobalOptions();

	mTerrainGroup = OGRE_NEW Ogre::TerrainGroup(mSceneMgr, Ogre::Terrain::ALIGN_X_Z, TERRAIN_SIZE, WORLD_SIZE);
	mTerrainGroup->setFilenameConvention(Ogre::String("NimbusTerrain"), Ogre::String("dat")); // TERRAIN LOADING
	mTerrainGroup->setOrigin(Ogre::Vector3::ZERO);

	this->configureTerrainDefaults(light);
	
	// Define our terrains
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

	// Lets make some water!
	Ogre::Entity* waterEntity;
	Ogre::Plane waterPlane;

	// Create the plane.
	waterPlane.normal = Ogre::Vector3::UNIT_Y;
	waterPlane.d = -1.5;

	Ogre::MeshManager::getSingleton().createPlane("waterPlane", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, waterPlane, 8000, 8000, 20, 20, true, 1, 10, 10, Ogre::Vector3::UNIT_Z);

	// Create the water entity.
	waterEntity = mSceneMgr->createEntity("water", "waterPlane");
	waterEntity->setMaterialName("Examples/TextureEffect4");
	
	Ogre::SceneNode *waterNode = mSceneMgr->getRootSceneNode()->createChildSceneNode("waterNode");
	waterNode->attachObject(waterEntity);
	waterNode->translate(0.0f, 100.0f, 0.0f);
}

//-------------------------------------------------------------------------------------
void NimbusPrototype::createFrameListener(void)
{
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

	return ret;
}
