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
	private:
		EntitiesManager();
		virtual ~EntitiesManager();

		friend class Managers;
		friend class GraphicManager;
		friend class GameManager;
		friend class EventsManager;

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