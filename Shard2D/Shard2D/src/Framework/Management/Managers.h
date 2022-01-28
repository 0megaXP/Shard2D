#pragma once

#include <memory>

#include "GameManager.h"
#include "../Graphic/GraphicManager.h"
#include "../Assets/AssetsManager.h"
#include "../GameObjects/GameObjectsManager.h"
#include "../Clock/ClockManager.h"

#define M_GameManager			Managers::gameManager
#define	M_GraphicManager		Managers::graphicManager
#define	M_ClockManager			Managers::clockManager
#define	M_AssetsManager			Managers::assetsManager
#define	M_GameObjectsManager	Managers::gameObjectsManager


class Managers
{
public:
	static GameManager* const gameManager;
	static GraphicManager* const graphicManager;
	static ClockManager* const clockManager;
	static AssetsManager* const assetsManager;
	static GameObjectsManager* const gameObjectsManager;
};

