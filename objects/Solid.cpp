//
// Created by root on 01.06.2019.
//

#include "../generic/defines.h"
#include "Solid.h"

bool Solid::initialized = false;

Solid::Solid() {
	if (UNLIKELY(!initialized)) {
		Solid::init();
	}
	Solid::solids.emplace(this);
}

const std::queue<Solid*>&
Solid::getSolids() {
	if (UNLIKELY(!initialized)) {
		Solid::init();
	}
	return Solid::solids;
}