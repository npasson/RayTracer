//
// Created by root on 01.06.2019.
//

#include "../generic/defines.h"
#include "Solid.h"

std::queue<Solid*> Solid::solids = std::queue<Solid*>{};

Solid::Solid(uint8_t type): TYPE(type) {
	static std::queue<Solid*> solids;
	solids.emplace(this);
}

const std::queue<Solid*>&
Solid::getSolids() {
	return solids;
}

uint8_t
Solid::getType() const {
	return SOLID;
}
