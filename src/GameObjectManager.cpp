#include <iostream>
#include <vector>
#include "GameObjectManager.h"
#include "GameObject.h"

GameObjectManager GameObjectManager::m_instance = GameObjectManager();
std::vector<GameObject*> GameObjectManager::m_objects = std::vector<GameObject*>();

GameObjectManager::GameObjectManager()
{
}


GameObjectManager::~GameObjectManager()
{
}

GameObjectManager& GameObjectManager::getInstance()
{
	return m_instance;
}

void GameObjectManager::add(GameObject* obj)
{
	m_objects.push_back(obj);
}
