#pragma once

#include <vector>
#include <memory>

/*
Add "object" to the stage. Every object in the stage will be rendered from the GraphicManager frame by frame. 
To avoid the rendering, set the object visibility value as false or remove it from the stage.
*/
#define AddToStage Managers::gameObjectsManager->AddObjectToStage

/*
Remove "object" from the stage, avoiding it to be rendered.
*/
#define RemoveFromStage Managers::gameObjectsManager->RemoveObjectFromStage

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
	/*
	This function does not have to be called manually.
	Function called from the GameObject default constructor. Creates the shared ptr for the created GameObject.
	*/
	void ObjectCreated(GameObject* object);

	/*
	Add "object" to the stage. Every object in the stage will be rendered from the GraphicManager frame by frame.
	To avoid the rendering, set the object visibility value as false or remove it from the stage.
	*/
	void AddObjectToStage(GameObject* object);

	/*
	Remove "object" from the stage, avoiding it to be rendered.
	*/
	void RemoveObjectFromStage(GameObject* object);
};

