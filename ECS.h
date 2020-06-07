#pragma once

#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include <bitset>
#include <array>


// entity component system


class Component;
class Entity;
class Manager;

using ComponentID = std::size_t;
using group = std::size_t;

inline ComponentID getNewComponentTypeID() {

	static ComponentID lastID = 0;
	return lastID++;

}

template <typename T> inline ComponentID getComponentTypeID() noexcept {		//  template <typename T> s�u�y jako placeholder dla dowolnego typu danych (np. int,long int itd..) 

	static ComponentID typeID = getNewComponentTypeID();
	return typeID;
}

constexpr std::size_t maxComponents = 32;
constexpr std::size_t maxGroups = 32;

using ComponentBitSet = std::bitset<maxComponents>;			
using groupBitSet = std::bitset<maxGroups>;
using ComponentArray = std::array<Component*, maxComponents>;					//

class Component {
public:
	Entity* entity;

	virtual void init() {}														// virtual pozwala na override
	virtual void update() {}
	virtual void draw() {}

	virtual ~Component(){}
};

class Entity {

private:
	Manager& manager;
	bool active = true;
	std::vector<std::unique_ptr<Component>> components;
	ComponentArray componentArray;
	ComponentBitSet componentBitSet;
	groupBitSet GroupBitSet;
public:
	Entity(Manager& memberManager) : manager(memberManager){}
	void update() 
	{
		for (auto& c : components) { c->update(); };
	}

	void draw() 
	{
		for (auto& c : components) {
			c->draw();
	};
	}

	bool isActive() const { return active; }
	void destroy() { active = false; }

	bool hasGroup(group memberGroup) {
		return GroupBitSet[memberGroup];
	}

	void addGroup(group mGroup);
	void delGroup(group mGroup){
		GroupBitSet[mGroup] = false;
	}

	template <typename T> bool hasComponent() const {						// sprawdzi czy entity ma component
		return componentBitSet[getComponentTypeID<T>()];
	}

	template <typename T, typename... TArgs>
	T& addComponent(TArgs&&... mArgs) {
		T* c(new T(std::forward<TArgs>(mArgs)...));
		c->entity = this;
		std::unique_ptr<Component> uPtr{ c };
		components.emplace_back(std::move(uPtr));
		componentArray[getComponentTypeID<T>()] = c;
		componentBitSet[getComponentTypeID<T>()] = true;
		c->init();
		return *c;
	}

	template<typename T> T& getComponent() const{
		auto ptr(componentArray[getComponentTypeID<T>()]);
		return *static_cast<T*>(ptr);
	}
																		// Np gameObject.getComponent<PositionComponent>().setXpos(25); 
};


class Manager {

private:
	std::array<std::vector<Entity*>, maxGroups> groupedEntities;	// 32 miejscowa tabela 
	std::vector<std::unique_ptr<Entity>> entities;		// wektor trzyma liste entities

public:

	void update() {
		
		for (std::size_t i = 0; i < entities.size(); i++){
			entities.at(i)->update();
		}
		
		/*          // nie usuwa� !!!
		for (auto& e : entities) { // for each e in entities
			e->update();
		}*/
	}

	void draw() {

		for (auto& e : entities) {
			e->draw();
		};

	}

	void refresh() {
		for(auto i(0u); i< maxGroups;i++){
			auto& v(groupedEntities[i]);
			v.erase(
				std::remove_if(std::begin(v), std::end(v), 
					[i](Entity* mEntity) {
				return !mEntity->isActive() || !mEntity->hasGroup(i);
			}),
				std::end(v));
		}
		entities.erase(std::remove_if(std::begin(entities), std::end(entities), [](const std::unique_ptr<Entity> &mEntity) {
			return !mEntity->isActive();
		}),
			std::end(entities));
	}

	void addToGroup(Entity* mEntity, group mGroup) {
		groupedEntities[mGroup].emplace_back(mEntity);
	}

	std::vector<Entity*>& getGroup(group mGroup) {			// zwr�ci grupe
		return groupedEntities[mGroup];
	}

	Entity& addEntity() {
		Entity* e = new Entity(*this);
		std::unique_ptr<Entity> uPtr{ e };
		entities.emplace_back(std::move(uPtr));
		return *e;
	}
};