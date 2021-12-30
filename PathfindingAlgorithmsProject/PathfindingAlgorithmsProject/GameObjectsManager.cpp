#include "GameObjectsManager.h"
#include "GameObject.h"
#include "Managers.h"

#include <iostream>

GameObjectsManager::GameObjectsManager()
	//: _stagedObjects(std::vector<GameObject*>()), _unusedObjects(std::vector<GameObject*>())
{

}

GameObjectsManager::~GameObjectsManager()
{
}

void GameObjectsManager::ObjectCreated(GameObject* object)
{
	for (std::shared_ptr<GameObject> createdObject : _createdObjects)
	{
		if (createdObject.get() == object)
		{
			std::cout << "Object already created!" << std::endl;
			return;
		}
	}

	std::cout << "Object created!" << std::endl;
	_createdObjects.push_back(std::shared_ptr<GameObject>(object));
}

/**
Add the GameObject to the stage (the first rendered layer).
*/
void GameObjectsManager::AddObjectToStage(GameObject* object)
{
	for (GameObject* stagedObject : _stagedObjects)
	{
		if (stagedObject == object)
		{
			std::cout << "Object already added to stage!" << std::endl;
			return;
		}
	}

	_stagedObjects.push_back(object);
}

/**
Remove the GameObject from the stage.
*/
void GameObjectsManager::RemoveObjectFromStage(GameObject* object)
{
	int count = 0;
	for (GameObject* stagedObject : _stagedObjects)
	{
		if (stagedObject == object)
		{
			_stagedObjects.erase(_stagedObjects.begin() + count);
			return;
		}
		count++;
	}
}