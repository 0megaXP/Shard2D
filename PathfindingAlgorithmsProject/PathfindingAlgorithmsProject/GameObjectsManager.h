#pragma once

#include <vector>

class GameObject;

class GameObjectsManager
{
public:
	GameObjectsManager();

protected:
	~GameObjectsManager();

	friend class GraphicManager;

private:
	std::vector<GameObject*> _stagedObjects;
	std::vector<GameObject*> _unusedObjects;

public:
	void AddObjectToStage(GameObject* object);
	void RemoveObjectFromStage(GameObject* object);

	void ChildAdded(GameObject* child);
	void ChildRemoved(GameObject* child);

private:
	void SetObjectUnused(GameObject* object);
	void UnsetObjectUnused(GameObject* object);
};

