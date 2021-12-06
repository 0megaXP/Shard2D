#include "GameManager.h"

#include "GraphicManager.h"
#include "ClockManager.h"
#include "Managers.h"

GameManager::GameManager()
{
}

GameManager::~GameManager()
{
}

void GameManager::SetupGame()
{
    Managers::graphicManager = new GraphicManager();
    Managers::clockManager = new ClockManager();
}
