//
// Created by root on 01.06.2019.
//

#ifndef RAYTRACING_SOLID_H
#define RAYTRACING_SOLID_H

#include <vector>
#include <queue>

#define SOLID static_cast<uint8_t>(0)
#define SPHERE static_cast<uint8_t>(1)

class Solid {
private:
	static std::queue<Solid*> solids;
public:
	static const std::queue<Solid*>&
	getSolids();

	virtual uint8_t
	getType() const;

	explicit Solid(uint8_t type);
};

#endif //RAYTRACING_SOLID_H
