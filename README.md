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
    * [X] Border-Pushing [In testing]
 * [_] Camera Zoom
 * [_] Proper Height Processing

##### Example Gameplay Mechanics
 * [_] Vector Fields
 * [_] Cloud Objects
 * [_] Wind Manipulation

## NOTES
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

###### TIP
After moving OGRE to ./ProjectDir/ogre/, edit ogre/bin/Release/resources.cfg and ogre/bin/debug/resources_d.cfg to include glsl shaders if you plan on using OpenGL
Additionally, add the OGRE_HOME execution directories to your PATH to run from Visual Studio
