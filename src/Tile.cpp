#include "Tile.h"

namespace Nimbus
{
	Tile::Tile(float humidity, float temperature, float saturation, float elevation):
		mHumidity(humidity), mTemperature(temperature), mSaturation(saturation), mElevation(elevation)
	{
	}

	Tile::Tile(void): Tile(0.0f, 0.0f, 0.0f, 0.0f) {}

	Tile::~Tile(void)
	{
	}
}