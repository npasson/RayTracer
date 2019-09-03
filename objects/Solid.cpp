//
// Created by root on 01.06.2019.
//

#include "../generic/defines.h"
#include "Solid.h"

std::queue<Solid*> Solid::solids = std::queue<Solid*>{};

Solid::Solid() {
	Solid::solids.emplace(this);
}

const std::queue<Solid*>&
Solid::getSolids() {
	return Solid::solids;
}

uint8_t
Solid::getType() const {
	return SOLID;
}

Point
Solid::getPosition() const {
	return _position;
}

void
Solid::setPosition(const Point& position) {
	_position = position;
}

const Material&
Solid::getMaterial() const {
	return _material;
}

void
Solid::setMaterial(const Material& material) {
	_material = material;
}

Vec3
Solid::getNormal(Point& p) {
	return this->getPosition().getVectorTo(p).getNormalize();
}
