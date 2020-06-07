#pragma once
#include <SDL.h>

class ColliderComponent;

class Collision {

public:
	static bool AABB(const SDL_Rect& recA,const SDL_Rect& recB);		// Axis-aligned minimum bounding box
	static bool AABB(const ColliderComponent& colA, const ColliderComponent& colB);
	static bool AB(const SDL_Rect * recA, const SDL_Rect * recB);
	static bool ab(const ColliderComponent * colA, const ColliderComponent & colB);
};
