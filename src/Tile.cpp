#include "Tile.h"

namespace Nimbus
{
	unsigned long long int Tile::count = 0;

	Tile::Tile(float humidity, float temperature, float saturation, float elevation)
	{
		construct(humidity, temperature, saturation, elevation);
	}

	Tile::Tile(void)
	{
		construct(0.0f, 0.0f, 0.0f, 0.0f);
	}

	void Tile::construct(float humidity, float temperature, float saturation, float elevation)
	{
		// Initialize values
		mHumidity = humidity;
		mTemperature = temperature;
		mSaturation = saturation;
		mElevation = elevation;

		Tile::count++;
	}

	Tile::~Tile(void)
	{
		Tile::count--;

		if(Tile::count < 0)
			std::cerr << "SNAPSOMETHINGBADJUSTWENTDOWNBETTERMAKESURETHOSETILESDON'TEXPLODEPREPAREFORSEGFAULT" << std::endl;
	}

	void Tile::update(void)
	{
		std::cout << "TILE!" << std::endl;
	}
}