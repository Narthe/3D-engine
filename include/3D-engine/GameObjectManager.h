#pragma once

#include <vector>
#include "GameObject.h"


class GameObjectManager
{
public:
	static GameObjectManager& getInstance();
	void add(GameObject* obj);
	std::vector<GameObject*> getObjects() { return m_objects; }
	static void update(const float _dt);
	//static const GameObject* getClosestTarget(GameObject* obj);

	static std::vector<GameObject*> m_objects;

private:
	GameObjectManager();
	~GameObjectManager();

	GameObjectManager& operator= (const GameObjectManager&) {}
	GameObjectManager(const GameObjectManager&) {}

	static GameObjectManager m_instance;
};