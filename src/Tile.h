#ifndef __NIMBUS_TILE
#define __NIMBUS_TILE

#include <OgreRoot.h>

namespace Nimbus
{
	using namespace Ogre;

	class Tile
	{
		// MEMBER ATTRIBUTES
	private:

		// Represents different aspects of the tile environment.
		//   NOTE: DETAIL EACH LATER.
		//   NOTE: REAL TYPE UNKNOWN, MAY BE SUBJECT TO CHANGE.
		float humidity;
		float temperature;
		float saturation;
		float elevation;

		// MEMBER METHODS
	public:
		// CONSTRUCTORS --
		Tile(void);

		// DESTRUCTORS (I WILL CALL THEM WHAT I WANT YOU CAN'T TELL ME WAHT TO DO) --
		~Tile(void);
	};
}

#endif