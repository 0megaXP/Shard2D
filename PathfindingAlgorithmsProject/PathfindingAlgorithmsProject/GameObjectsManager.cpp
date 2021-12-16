#include "GameObjectsManager.h"

#include "GameObject.h"

GameObjectsManager::GameObjectsManager()
{

	_stagedObjects = std::vector<GameObject*>();
	_unusedObjects = std::vector<GameObject*>();
}

GameObjectsManager::~GameObjectsManager()
{
}

/**
Add the GameObject to the stage (the first rendered layer).
*/
void GameObjectsManager::AddObjectToStage(GameObject* object)
{
	_stagedObjects.push_back(object);
	UnsetObjectUnused(object);
	if (object->Parent() != nullptr)
	{
		object->_parent->RemoveChild(object);
	}

	for (GameObject* child : object->_children)
	{
		UnsetObjectUnused(child);
	}

}

/**
Remove the GameObject from the stage.
*/
void GameObjectsManager::RemoveObjectFromStage(GameObject* object)
{
	int count = 0;
	for (GameObject* stagedObject : _stagedObjects)
	{
		if (object == stagedObject)
		{
			_stagedObjects.erase(_stagedObjects.begin() + count);
			SetObjectUnused(object);
			for (GameObject* child : object->_children)
			{
				SetObjectUnused(child);
			}
			return;
		}
		count++;
	}
}

void GameObjectsManager::ChildAdded(GameObject* child)
{
	UnsetObjectUnused(child);
}

void GameObjectsManager::ChildRemoved(GameObject* child)
{
	SetObjectUnused(child);
}

void GameObjectsManager::SetObjectUnused(GameObject* object)
{
	// Check if the object to add is already unused
	for (GameObject* unusedObject : _unusedObjects)
	{
		if (unusedObject == object)
			return;
	}

	_unusedObjects.push_back(object);
}

void GameObjectsManager::UnsetObjectUnused(GameObject* object)
{
	int count = 0;
	for (GameObject* unusedObject : _unusedObjects)
	{
		if (unusedObject == object)
		{
			_unusedObjects.erase(_unusedObjects.begin() + count);
			return;
		}

		count++;
	}
}