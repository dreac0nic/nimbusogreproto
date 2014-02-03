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
 * [ ] Proper Scene Manager [SpenSer]
 * [ ] Heightmap/dat Generation
 * [ ] Lighting/shadow maps
    * [ ] Possible bump-mapping
 * [ ] Environment Initialization
    * [ ] Render to Geometry
	* [ ] Texture Layering
 * [ ] Water
    * [ ] Land -> Water Smoothing

##### Camera Control
Controlling the camera in an RTS style.
 * [ ] Over-hanging Camera
 * [ ] User Input
    * [ ] Arrow-key Panning
    * [ ] Border-Pushing
 * [ ] Camera Zoom
 * [ ] Proper Height Processing

##### Example Gameplay Mechanics
 * [ ] Vector Fields
 * [ ] Cloud Objects
 * [ ] Wind Manipulation

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
