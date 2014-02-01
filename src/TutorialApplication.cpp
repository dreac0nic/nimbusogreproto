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
#include "TutorialApplication.h"

//-------------------------------------------------------------------------------------
TutorialApplication::TutorialApplication(void)
{
}
//-------------------------------------------------------------------------------------
TutorialApplication::~TutorialApplication(void)
{
}

//-------------------------------------------------------------------------------------
void TutorialApplication::createScene(void)
{
	// Setup light and shadow settings.
	mSceneMgr->setAmbientLight(Ogre::ColourValue(0, 0, 0)); // Ugh more black ...
	mSceneMgr->setShadowTechnique(Ogre::SHADOWTYPE_STENCIL_ADDITIVE);

	// Add some objects to the scene.
	Ogre::Entity* entNinja = mSceneMgr->createEntity("Ninja", "ninja.mesh");
	entNinja->setCastShadows(true);

	mSceneMgr->getRootSceneNode()->createChildSceneNode()->attachObject(entNinja);

	// Setup plane.
	Ogre::Plane plane(Ogre::Vector3::UNIT_Y, 0);

	Ogre::MeshManager::getSingleton().createPlane("ground", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, plane, 1500, 1500, 20, 20, true, 1, 5, 5, Ogre::Vector3::UNIT_Z);

	Ogre::Entity* entGround = mSceneMgr->createEntity("Ground", "ground");
	mSceneMgr->getRootSceneNode()->createChildSceneNode()->attachObject(entGround);

	// Create plane material.
	entGround->setMaterialName("Examples\Rockwall");
	entGround->setCastShadows(false);
}

//-------------------------------------------------------------------------------------
void TutorialApplication::createCamera(void)
{
	// Create the camera.
    mCamera = mSceneMgr->createCamera("PlayCamera");

	// Setup position and direction.
	mCamera->setPosition(Ogre::Vector3(0, 10, 500));
	mCamera->lookAt(Ogre::Vector3(0, 0, 0));

	// Setup camera properties.
	mCamera->setNearClipDistance(5);
	//mCamera->setFarClipDistance(100); // DO NOT USE, WE'RE STENCILING SO FAR CLIP IS NOT NECESSARY

	// Setup and bind camera man.
	mCameraMan = new OgreBites::SdkCameraMan(mCamera);
}

//-------------------------------------------------------------------------------------
void TutorialApplication::createViewports(void)
{
	// Create our viewport.
	Ogre::Viewport *vp = mWindow->addViewport(mCamera);

	// Set viewport background color.
	vp->setBackgroundColour(Ogre::ColourValue(0, 0, 0)); // Ew, black. Fix later. Black is dumb.

	// Fix camera aspect ratio.
	mCamera->setAspectRatio(Ogre::Real(vp->getActualWidth())/Ogre::Real(vp->getActualHeight()));
}

#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
#define WIN32_LEAN_AND_MEAN
#include "windows.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif

#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
    INT WINAPI WinMain( HINSTANCE hInst, HINSTANCE, LPSTR strCmdLine, INT )
#else
    int main(int argc, char *argv[])
#endif
    {
        // Create application object
        TutorialApplication app;

        try {
            app.go();
        } catch( Ogre::Exception& e ) {
#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
            MessageBox( NULL, e.getFullDescription().c_str(), "An exception has occured!", MB_OK | MB_ICONERROR | MB_TASKMODAL);
#else
            std::cerr << "An exception has occured: " <<
                e.getFullDescription().c_str() << std::endl;
#endif
        }

        return 0;
    }

#ifdef __cplusplus
}
#endif
