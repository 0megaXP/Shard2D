#include "GameObjectsManager.h"

#include "GameObject.h"
#include "../Management/Managers.h"
#include "../Utils/ShardUtils.h"

GameObjectsManager::GameObjectsManager()
	: _createdObjects(std::vector<std::shared_ptr<GameObject>>()) ,_stagedObjects(std::vector<GameObject*>())
{
	Log("GameObjectsManager created!", TextColor::Blue);
}

GameObjectsManager::~GameObjectsManager()
{
	Log("GameObjectsManager destroyed!", TextColor::Blue);
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

	_createdObjects.push_back(std::shared_ptr<GameObject>(object));
}

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