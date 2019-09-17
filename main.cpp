#include "generic/Debug.h"
#include "objects/Camera.h"
#include "objects/LightSource.h"
#include "objects/Sphere.h"

int
main() {
	Debug::Presets::untie_io();

	Camera& c = Camera::getInstance();

	c.setVoidColor(Color{0.02});

	LightSource sun{
		{1, 0.5, 0.7},
		{1, 1, 1},
		0.1
	};

	//LightSource sun2{
	//	{2, 1, 0.5},
	//	{1, 1, 1},
	//	1
	//};

	//  LightSource red{
	//  	{2, 2, 2},
	//  	{1, 0, 0},
	//  	1
	//  };

	Sphere redSphere{
		{3, -1, -2},
		0.8
	},     blueSphere{
		{3, 0, 0},
		0.8
	},     greenSphere{
		{3, 0, 2},
		0.8
	};

	redSphere.setMaterial(Material(
		{0.2, 0.05, 0.05},
		{0.8, 0.2, 0.2},
		{0.08, 0.02, 0.02},
		30
	));

	greenSphere.setMaterial(Material(
		{0.05, 0.05, 0.2},
		{0.2, 0.8, 0.2},
		{0.02, 0.08, 0.02},
		30
	));

	blueSphere.setMaterial(Material(
		{0.05, 0.05, 0.2},
		{0.2, 0.2, 0.8},
		{0.02, 0.02, 0.08},
		30
	));

	c.render();

}


