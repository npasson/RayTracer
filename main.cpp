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

	Sphere s{
		{5, 1, 1},
		2
	};

	Sphere s2{
		{15, -1, -5},
		7
	};

	c.forEachPixel([](Ray3 ray,
	                  uint16_t x,
	                  uint16_t y) -> Color {
		//std::cout << ray << std::endl;
		auto solids = Solid::getSolids();

		LightSource sun{
			{1, 1, 1},
			{0.6, 0.2, 0.2},
			2
		};

		while (!solids.empty()) {
			Solid* s = solids.front();
			solids.pop();

			Point* p = ray.getIntersect(*s);

			if (p == nullptr) {
				continue;
			}

			return p->getBrightnessFromLightSource(sun);


		}
		return {0,0,0};
	});

}


