#include "Managers.h"

namespace Shard2D
{
	GameManager* const Managers::gameManager = new GameManager();
	ClockManager* const Managers::clockManager = new ClockManager();
	GraphicManager* const Managers::graphicManager = new GraphicManager();
	AssetsManager* const Managers::assetsManager = new AssetsManager();
	EntitiesManager* const Managers::entitiesManager = new EntitiesManager();
	EventsManager* const Managers::eventsManager = new EventsManager();
}