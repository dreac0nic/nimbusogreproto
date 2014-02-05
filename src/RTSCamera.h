#pragma once

#define TOP_SPEED 150.0f
#define SET_CAMERA_SUCESSFUL 1
#define SET_CAMERA_FAILED 2
#define NORTH Ogre::Vector3::UNIT_X
#define EAST Ogre::Vector3::UNIT_Y
#define UP Ogre::Vector3::UNIT_Z

#include <OgreCamera.h>
#include <OgreSceneManager.h>

#include <OISEvents.h>
#include <OISInputManager.h>
#include <OISKeyboard.h>
#include <OISMouse.h>

class RTSCamera
{
	public:
		RTSCamera(void);
		virtual ~RTSCamera(void);
		virtual int setCamera(Ogre::Camera* p_cam);
		virtual bool frameRenderingQueued(const Ogre::FrameEvent& evt);
		virtual void injectKeyDown(const OIS::KeyEvent& evt);
		virtual void injectKeyUp(const OIS::KeyEvent& evt);


	protected:
	Ogre::Camera* p_mCamera;
	Ogre::Vector3 mTarget;
	Ogre::Vector3 mVelocity;
	float mTopSpeed;
	bool isGoingNorth;
	bool isGoingSouth;
	bool isGoingEast;
	bool isGoingWest;
	bool isZoomingIn;
	bool isZoomingOut;
	bool isMovingFast;
};