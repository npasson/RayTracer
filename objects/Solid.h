//
// Created by root on 01.06.2019.
//

#ifndef RAYTRACING_SOLID_H
#define RAYTRACING_SOLID_H

#include <vector>
#include <queue>

class Solid {
private:
	static std::queue<Solid*> solids;
public:
	static const std::queue<Solid*>&
	getSolids();

	Solid();
};

#endif //RAYTRACING_SOLID_H
