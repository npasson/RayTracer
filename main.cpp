#include <cstdint>
#include <iostream>
#include "objects/Camera.h"
#include "generic/Debug.h"

int
main() {
	Debug::Presets::untie_io();

	Camera& c = Camera::getInstance();

	c.forEachPixel([](Ray3 ray, uint16_t x, uint16_t y) -> Color {
		std::cout << ray << std::endl;
		return {0,0,0};
	});
}


