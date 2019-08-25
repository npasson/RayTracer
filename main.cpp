#include <cstdint>
#include <iostream>
#include "objects/Camera.h"
#include "generic/Debug.h"
#include "objects/LightSource.h"
#include "objects/Sphere.h"

int
main() {
	Debug::Presets::untie_io();

	Camera& c = Camera::getInstance();

	LightSource sun{
		{1,   1,   1},
		{0.6, 0.2, 0.2},
		1
	};

	Sphere s{
		{2, 0, 0},
		2
	};

	c.forEachPixel([](Ray3 ray,
	                  uint16_t x,
	                  uint16_t y) -> Color {
		std::cout << ray << std::endl;
		auto solids = Solid::getSolids();
		while (!solids.empty()) {
			Solid* s = solids.front();
			solids.pop();


		}
	});
}


