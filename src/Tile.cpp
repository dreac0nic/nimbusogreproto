#include "Tile.h"

namespace Nimbus
{
	unsigned long long int Tile::count = 0;

	Tile::Tile(float humidity, float temperature, float saturation, float elevation):
		mHumidity(humidity), mTemperature(temperature), mSaturation(saturation), mElevation(elevation)
	{
		Tile::count++;
	}

	Tile::Tile(void): Tile(0.0f, 0.0f, 0.0f, 0.0f) {}

	Tile::~Tile(void)
	{
		Tile::count--;

		if(Tile::count < 0)
			std::cerr << "SNAPSOMETHINGBADJUSTWENTDOWNBETTERMAKESURETHOSETILESDON'TEXPLODEPREPAREFORSEGFAULT" << std::endl;
	}
}