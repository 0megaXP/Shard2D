#include "GameManager.h"

#include <iostream>

#include "GraphicManager.h"
#include "ClockManager.h"
#include "AssetsManager.h"
#include "GameObjectsManager.h"
#include "Managers.h"
#include "GameObject.h"
#include "ApplicationMain.h"
#include <SDL_events.h>

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
    Managers::assetsManager = new AssetsManager();
    Managers::gameObjectsManager = new GameObjectsManager();

    appMain = new ApplicationMain();
}

void GameManager::ExitGame()
{
    _exitGame = true;
}

bool GameManager::GetExitGame()
{
    return _exitGame;
}

void GameManager::GameUpdate()
{

    // Clock update
    Managers::clockManager->NewFrame();

    // Events update

    // Logic update
    appMain->Update();

    // Graphic update
    Managers::graphicManager->RenderScene();

    Managers::clockManager->ManageFramesCap();
    Managers::clockManager->UpdateDeltaTime();
}
