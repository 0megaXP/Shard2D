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

#include "Managers.h"

namespace Shard2D
{
	GameManager* const Managers::gameManager = new GameManager();
	ClockManager* const Managers::clockManager = new ClockManager();
	GraphicManager* const Managers::graphicManager = new GraphicManager();
	AssetsManager* const Managers::assetsManager = new AssetsManager();
	EntitiesManager* const Managers::entitiesManager = new EntitiesManager();
	EventsManager* const Managers::eventsManager = new EventsManager();
	TweensManager* const Managers::tweensManager = new TweensManager();

	void Managers::DeleteManagers()
	{
		delete ShardTweens;
		delete ShardEvents;
		delete ShardAssets;
		delete ShardClock;
		delete ShardGraphic;
		delete ShardEntities;
		delete ShardManager;
	}

}