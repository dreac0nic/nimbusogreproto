#include "RTSCamera.h"

//defualt constructer
RTSCamera::RTSCamera(void)
{
	mTarget = Ogre::Vector3::ZERO;
	mVelocity = Ogre::Vector3::ZERO;
	mTopSpeed = TOP_SPEED;
	isGoingNorth = false;
	isGoingSouth = false;
	isGoingEast = false;
	isGoingWest = false;
	isZoomingIn = false;
	isZoomingOut = false;
	isMovingFast = false;


}

//Deconstructer
RTSCamera::~RTSCamera(void)
{
}

//Changes the current camera controlled by the camera manager-------
int RTSCamera::setCamera(Ogre::Camera* p_cam)
{
	p_mCamera = p_cam;
	if (p_mCamera == p_cam)
	{
		return SET_CAMERA_SUCESSFUL;
	}
	return SET_CAMERA_FAILED;
}

bool RTSCamera::frameRenderingQueued(const Ogre::FrameEvent& evt)
	{
		// build our acceleration vector based on keyboard input composite
		Ogre::Vector3 accel = Ogre::Vector3::ZERO;
		if (isGoingNorth) accel += NORTH;
		if (isGoingSouth) accel -= NORTH;
		if (isGoingEast) accel += EAST;
		if (isGoingWest) accel -= EAST;
		if (isZoomingOut) accel += UP;
		if (isZoomingIn) accel -= UP;
		// if accelerating, try to reach top speed in a certain time
		Ogre::Real topSpeed = isMovingFast ? mTopSpeed * 20 : mTopSpeed;
		if (accel.squaredLength() != 0)
		{
			accel.normalise();
			mVelocity += accel * topSpeed * evt.timeSinceLastFrame * 10;
		}
		// if not accelerating, try to stop in a certain time
		else mVelocity -= mVelocity * evt.timeSinceLastFrame * 10;
		Ogre::Real tooSmall = std::numeric_limits<Ogre::Real>::epsilon();
		// keep camera velocity below top speed and above epsilon
	if (mVelocity.squaredLength() > topSpeed * topSpeed)
		{
			mVelocity.normalise();
			mVelocity *= topSpeed;
		}
		else if (mVelocity.squaredLength() < tooSmall * tooSmall)
			mVelocity = Ogre::Vector3::ZERO;
		if (mVelocity != Ogre::Vector3::ZERO) p_mCamera->move(mVelocity * evt.timeSinceLastFrame);
	return true;
}

//processes key presses and start movement in a direction
void RTSCamera::injectKeyDown(const OIS::KeyEvent& evt)
{
	if (evt.key == OIS::KC_W || evt.key == OIS::KC_UP) RTSCamera::isGoingNorth = true;
	else if (evt.key == OIS::KC_S || evt.key == OIS::KC_DOWN) isGoingSouth = true;
	else if (evt.key == OIS::KC_A || evt.key == OIS::KC_LEFT) isGoingWest = true;
	else if (evt.key == OIS::KC_D || evt.key == OIS::KC_RIGHT) isGoingEast = true;
	else if (evt.key == OIS::KC_PGUP) isZoomingIn = true;
	else if (evt.key == OIS::KC_PGDOWN) isZoomingOut = true;
	else if (evt.key == OIS::KC_LSHIFT) isMovingFast = true;
}

//process key releases to stop movement in a direction
void RTSCamera::injectKeyUp(const OIS::KeyEvent& evt)
{
	if (evt.key == OIS::KC_W || evt.key == OIS::KC_UP) RTSCamera::isGoingNorth = false;
	else if (evt.key == OIS::KC_S || evt.key == OIS::KC_DOWN) isGoingSouth = false;
	else if (evt.key == OIS::KC_A || evt.key == OIS::KC_LEFT) isGoingWest = false;
	else if (evt.key == OIS::KC_D || evt.key == OIS::KC_RIGHT) isGoingEast = false;
	else if (evt.key == OIS::KC_PGUP) isZoomingIn = false;
	else if (evt.key == OIS::KC_PGDOWN) isZoomingOut = false;
	else if (evt.key == OIS::KC_LSHIFT) isMovingFast = false;
}
