#include "EntitiesManager.h"

#include "Entity.h"
#include "../Management/Managers.h"
#include "../Utils/ShardUtils.h"
#include "../Events/EventTypes/Event.h"

namespace Shard2D
{
	EntitiesManager::EntitiesManager()
		: _createdEntities(std::vector<std::shared_ptr<Entity>>()), _stagedEntities(std::vector<Entity*>())
	{
		Log("GameObjectsManager created!", TextColor::Blue);
	}

	EntitiesManager::~EntitiesManager()
	{
		Log("GameObjectsManager destroyed!", TextColor::Blue);
	}

	void EntitiesManager::EntityCreated(Entity* entity)
	{
		for (std::shared_ptr<Entity> createdObject : _createdEntities)
		{
			if (createdObject.get() == entity)
			{
				std::cout << "Entity already created!" << std::endl;
				return;
			}
		}

		_createdEntities.push_back(std::shared_ptr<Entity>(entity));
	}

	void EntitiesManager::AddEntityToStage(Entity* entity)
	{
		for (Entity* stagedObject : _stagedEntities)
		{
			if (stagedObject == entity)
			{
				std::cout << "Entity already added to stage!" << std::endl;
				return;
			}
		}

		_stagedEntities.push_back(entity);
		entity->DispatchEvent<Event>(Event::Added);
	}

	void EntitiesManager::RemoveEntityFromStage(Entity* entity)
	{
		int count = 0;
		for (Entity* stagedObject : _stagedEntities)
		{
			if (stagedObject == entity)
			{
				_stagedEntities.erase(_stagedEntities.begin() + count);
				entity->DispatchEvent<Event>(Event::Removed);
				return;
			}
			count++;
		}
	}
}