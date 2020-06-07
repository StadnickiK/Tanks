#pragma once

#include <SDL.h>
#include "Components.h"


class HitPointComponent : public Component {

private:

	double maxHitPoints = 100;
	double hitPoints = maxHitPoints;

public:

	HitPointComponent() = default;
	HitPointComponent(double maxHP) {
		maxHitPoints = maxHP;
		hitPoints = maxHitPoints;
	}

	void standardDamage(double damage) {
		hitPoints = hitPoints - damage;
	}



};