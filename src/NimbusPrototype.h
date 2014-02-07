/*
-----------------------------------------------------------------------------
Filename:    NimbusPrototype.h
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
#ifndef __NIMBUSPROTOTYPE
#define __NIMBUSPROTOTYPE

#include <Terrain/OgreTerrain.h>
#include <Terrain/OgreTerrainGroup.h>

#include "BaseApplication.h"

#define TERRAIN_SIZE 513
#define WORLD_SIZE   12000.0f
#define MOUSE_PUSH_DISTANCE 80
#define ZOOM_MAX 12.0f
#define ZOOM_MIN 1.2f

class NimbusPrototype : public BaseApplication
{
private:
	Ogre::TerrainGlobalOptions* mTerrainGlobals;
	Ogre::TerrainGroup* mTerrainGroup;

	OgreBites::Label* mInfoLabel;
	
	bool mTerrainsImported;

	void defineTerrain(long x, long y); // Thank goodness for no type redefs.
	void initBlendMaps(Ogre::Terrain* terrain);
	void configureTerrainDefaults(Ogre::Light* light);

public:
    NimbusPrototype(void);
    virtual ~NimbusPrototype(void);

protected:
    virtual void createScene(void);
	virtual void createFrameListener(void);
    virtual void chooseSceneManager(void);
	virtual void destroyScene(void);
	virtual bool frameRenderingQueued(const Ogre::FrameEvent& event);
	virtual bool mousePressed( const OIS::MouseEvent &arg, OIS::MouseButtonID id );
	virtual	bool mouseReleased( const OIS::MouseEvent &arg, OIS::MouseButtonID id );
	virtual bool mouseMoved(const OIS::MouseEvent &arg);
	virtual bool keyPressed(const OIS::KeyEvent &arg);
	virtual bool keyReleased(const OIS::KeyEvent &arg);
	virtual void createCamera(void);
	bool cameraAccel(const Ogre::FrameEvent &event);
	bool baseKeyPressFunc(const OIS::KeyEvent &arg);

	Ogre::Real mZoom;
	Ogre::Real mZoomVelocity;

	Ogre::Real mTopSpeed;
	Ogre::Vector3 mVelocity;
	bool mGoingForward;
	bool mGoingBack;
	bool mGoingLeft;
	bool mGoingRight;
	bool mMouseGoingForward;
	bool mMouseGoingBack;
	bool mMouseGoingLeft;
	bool mMouseGoingRight;
	bool mFastMove;
};

#endif
