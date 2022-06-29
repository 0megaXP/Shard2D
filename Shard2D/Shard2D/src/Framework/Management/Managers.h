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

#include <memory>

#include "GameManager.h"
#include "../Graphic/GraphicManager.h"
#include "../Assets/AssetsManager.h"
#include "../Entities/EntitiesManager.h"
#include "../Clock/ClockManager.h"
#include "../Events/EventsManager.h"
#include "../Tweens/TweensManager.h"

namespace Shard2D
{
#define ShardManager			Managers::gameManager
#define	ShardGraphic			Managers::graphicManager
#define	ShardClock				Managers::clockManager
#define	ShardAssets				Managers::assetsManager
#define	ShardEntities			Managers::entitiesManager
#define	ShardEvents				Managers::eventsManager
#define	ShardTweens				Managers::tweensManager

	class Managers
	{
	public:
		static GameManager* const gameManager;
		static GraphicManager* const graphicManager;
		static ClockManager* const clockManager;
		static AssetsManager* const assetsManager;
		static EntitiesManager* const entitiesManager;
		static EventsManager* const eventsManager;
		static TweensManager* const tweensManager;

		static void DeleteManagers();
	};
}