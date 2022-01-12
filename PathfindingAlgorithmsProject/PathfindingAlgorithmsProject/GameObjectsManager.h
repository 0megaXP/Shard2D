#pragma once

#include <vector>
#include <memory>

#define AddToStage Managers::gameObjectsManager->AddObjectToStage

class GameObject;

class GameObjectsManager
{
public:
	GameObjectsManager();
	virtual ~GameObjectsManager();

	friend class GraphicManager;

private:

	std::vector<GameObject*> _stagedObjects;
	std::vector<std::shared_ptr<GameObject>> _createdObjects;

public:
	void ObjectCreated(GameObject* object);

	void AddObjectToStage(GameObject* object);
	void RemoveObjectFromStage(GameObject* object);
};

