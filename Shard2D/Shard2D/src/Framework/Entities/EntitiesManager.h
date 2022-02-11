#pragma once

#include <vector>
#include <memory>

namespace Shard2D
{
	/*
	Add "object" to the stage. Every object in the stage will be rendered from the GraphicManager frame by frame.
	To avoid the rendering, set the object visibility value as false or remove it from the stage.
	*/
#define AddToStage Managers::entitiesManager->AddEntityToStage

	/*
	Remove "object" from the stage, avoiding it to be rendered and receive events.
	*/
#define RemoveFromStage Managers::entitiesManager->RemoveEntityFromStage

	class Entity;

	class EntitiesManager
	{
	public:
		EntitiesManager();
		virtual ~EntitiesManager();

		friend class GraphicManager;
		friend class GameManager;
		friend class EventsManager;

	private:
		std::vector<Entity*> _stagedEntities;
		std::vector<std::shared_ptr<Entity>> _createdEntities;

	public:
		/*
		This function does not have to be called manually.
		Function called from the GameObject default constructor. Creates the shared ptr for the created GameObject.
		*/
		void EntityCreated(Entity* entity);

		/*
		Add "object" to the stage. Every object in the stage will be rendered from the GraphicManager frame by frame.
		To avoid the rendering, set the object visibility value as false or remove it from the stage.
		*/
		void AddEntityToStage(Entity* entity);

		/*
		Remove "object" from the stage, avoiding it to be rendered.
		*/
		void RemoveEntityFromStage(Entity* entity);
	};
}