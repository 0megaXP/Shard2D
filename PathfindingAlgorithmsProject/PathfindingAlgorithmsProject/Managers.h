#pragma once

#include <memory>

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

