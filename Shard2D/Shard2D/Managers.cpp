#include "Managers.h"

#include "GameManager.h"
#include "GraphicManager.h"
#include "ClockManager.h"
#include "AssetsManager.h"
#include "GameObjectsManager.h"

GameManager* const Managers::gameManager = new GameManager();
ClockManager* const Managers::clockManager = new ClockManager();
GraphicManager* const Managers::graphicManager = new GraphicManager();
AssetsManager* const Managers::assetsManager = new AssetsManager();
GameObjectsManager* const Managers::gameObjectsManager = new GameObjectsManager();