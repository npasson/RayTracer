#include "objects/Camera.h"
#include "generic/Debug.h"
#include "objects/LightSource.h"
#include "objects/Sphere.h"

int
main() {
	Debug::Presets::untie_io();

	Camera& c = Camera::getInstance();

	LightSource sun{
		{1, 1, 1},
		{1, 1, 1},
		3
	};

	LightSource red{
		{2, 2, 2},
		{1, 0, 0},
		1
	};

	Sphere sa{
		{3, 1, 2},
		1
	},     sb{
		{3, 0, -1},
		1
	},     sc{
		{2, -1, -1},
		1
	};

	c.render();

}


