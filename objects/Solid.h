//
// Created by root on 01.06.2019.
//

#ifndef RAYTRACING_SOLID_H
#define RAYTRACING_SOLID_H

#include "../math/Point.h"
#include "../visual/Material.h"
#include <vector>
#include <queue>

#define SOLID static_cast<uint8_t>(0)
#define SPHERE static_cast<uint8_t>(1)

class Solid {
private:
	static std::queue<Solid*> solids;
protected:
	Point    _position;
	Material _material;
public:
	explicit Solid();

	static const std::queue<Solid*>&
	getSolids();

	virtual uint8_t
	getType() const;

public:
	Vec3
	getNormal(Point&);

public:
	Point
	getPosition() const;

	void
	setPosition(const Point& position);

	const Material&
	getMaterial() const;

	void
	setMaterial(const Material& material);
};

#endif //RAYTRACING_SOLID_H
