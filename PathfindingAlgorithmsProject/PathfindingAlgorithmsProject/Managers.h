#pragma once

#include <memory>

#define M_GameManager			Managers::gameManager
#define	M_GraphicManager		Managers::graphicManager
#define	M_ClockManager			Managers::clockManager
#define	M_AssetsManager			Managers::assetsManager
#define	M_GameObjectsManager	Managers::gameObjectsManager

class GameManager;
class GraphicManager;
class ClockManager;
class AssetsManager;
class GameObjectsManager;

class Managers
{
public:
	static GameManager* const gameManager;
	static GraphicManager* const graphicManager;
	static ClockManager* const clockManager;
	static AssetsManager* const assetsManager;
	static GameObjectsManager* const gameObjectsManager;
};

