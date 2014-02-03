#ifndef __CustCameraMan_H__
#define __CustCameraMan_H__

#include "Ogre.h"
#include <limits>

class CustCameraMan : public OgreBites::SdkCameraMan
{
public:
	// Constructor snitching .. oh well
	CustCameraMan(Ogre::Camera* cam) : SdkCameraMan(cam) {}
	
	virtual bool frameRenderingQueued(const Ogre::FrameEvent& evt)
	{
		if (mStyle == OgreBites::CS_FREELOOK)
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

			if (mVelocity != Ogre::Vector3::ZERO) mCamera->move(mVelocity * evt.timeSinceLastFrame);
		}

		return true;
	}
};

#endif