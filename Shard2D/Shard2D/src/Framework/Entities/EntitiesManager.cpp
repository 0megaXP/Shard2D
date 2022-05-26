/*
The MIT License (MIT)

Copyright (c) 2021-2022 Filippo Alberto Munaro

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

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