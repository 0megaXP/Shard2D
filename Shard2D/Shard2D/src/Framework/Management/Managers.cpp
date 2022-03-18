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
		delete M_TweensManager;
		delete M_EventsManager;
		delete M_AssetsManager;
		delete M_ClockManager;
		delete M_GraphicManager;
		delete M_EntitiesManager;
		delete M_GameManager;
	}

}