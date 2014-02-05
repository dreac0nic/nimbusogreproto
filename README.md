"Nimbus" [WT] OGRE Prototype
============================

A brief prototype for the continuation of the "Nimbus" (working title) project, focusing on using OGRE to demonstrate the engine capabilities.

## Features
Will focus on implementation of:
 * Basic terrain generation
 * Lighting
 * Camera movement
 * Example gameplay mechanics.

### Current Task List
##### Terrain Generation
Generating, texturing and lighting some basic terrain along with the rest of the world.
 * [X] Proper Scene Manager
 * [_] Refined Heightmap/dat Generation [SpenSer]
 * [_] Lighting/shadow maps
    * [_] Possible bump-mapping
 * [_] Environment Initialization
    * [_] Render to Geometry
	* [_] Texture Layering
 * [_] Water
    * [_] Land -> Water Smoothing

##### Camera Control
Controlling the camera in an RTS style.
 * [X] Over-hanging Camera
 * [X] User Input
    * [X] Arrow-key Panning
    * [X] Border-Pushing
 * [_] Camera Zoom
 * [_] Proper Height Processing

##### Example Gameplay Mechanics
 * [_] Vector Fields
 * [_] Cloud Objects
 * [_] Wind Manipulation

## NOTES
### Installation
We will be using the 1.9 (11.29.2013) VS2012 SDK. This download can be found at [here](http://www.ogre3d.org/download/sdk)
Currently does not include OGRE library files for the sake of repository integrity. May be included in a future version.

To properly install OGRE, copy the contents of the OGRE folder into ./ProjectDir/ogre/
###### Example
```
Project\ogre\bin
Project\ogre\CMake
Project\ogre\Docs
Project\ogre\include
Project\ogre\lib
Project\ogre\media
Project\ogre\version.txt
Project\ogre\boost
Project\ogre\boost
Project\ogre\boost\lib
```

### BaseApplication
The BaseApplication is a simplistic framework class that provides the basic functions of a FrameListener as well as a series of other Ogre objects. We should not be modifying either BaseApplication.h BaseApplication.cpp, but rather overriding its functions using our inheriting class.

### OgreBites
OgreBites is a tutorial framework used to make introduction to the OGRE framework easy. We should be avoiding using anything used within this library and any references to it will be phased out with time.
