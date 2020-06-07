#include "Collision.h"
#include "ColliderComponent.h"												// dodany osobno ze wzglêdu na blad z niekompletnym typie w collision::AABB mk.2

bool Collision::AABB(const SDL_Rect& recA, const SDL_Rect& recB) {

	if (
		recA.x + recA.w >= recB.x &&
		recB.x + recB.w >= recA.x &&
		recA.y + recA.h >= recB.y &&
		recB.y + recB.h >= recA.y
		) {
		return true;
	}
	return false;
}

bool Collision::AABB(const ColliderComponent& colA, const ColliderComponent& colB) {		//	mk.2
	
	if (AABB(colA.collider, colB.collider)) {

		std::cout << colA.tag << " hit: " << colB.tag << std::endl;							//wypluje tagi collidera A i B
		return true;
	}
	else {
		return false;
	}
}

bool Collision::AB(const SDL_Rect* recA, const SDL_Rect* recB) {	//	AABB with pointers

	if (
		recA->x + recA->w >= recB->x &&
		recB->x + recB->w >= recA->x &&
		recA->y + recA->h >= recB->y &&
		recB->y + recB->h >= recA->y
		) {
		return true;
	}
	return false;
}