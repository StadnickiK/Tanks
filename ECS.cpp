#include "ECS.h"



void Entity::addGroup(group mGroup) {
	GroupBitSet[mGroup] = true;
	manager.addToGroup(this, mGroup);
}