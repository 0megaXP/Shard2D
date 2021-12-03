#include "GameManager.h"

#include "GraphicManager.h"
#include "ClockManager.h"

GameManager::GameManager()
{
}

GameManager::~GameManager()
{
}

bool GameManager::SetupGame()
{
	_graphicManager = new GraphicManager();
	return _graphicManager->Init();
}
