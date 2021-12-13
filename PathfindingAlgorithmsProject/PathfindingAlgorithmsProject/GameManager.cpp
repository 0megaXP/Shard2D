#include "GameManager.h"

#include <iostream>

#include "GraphicManager.h"
#include "ClockManager.h"
#include "AssetsManager.h"
#include "Managers.h"
#include "GameObject.h"

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

    Managers::graphicManager->AddObjectToStage(new GameObject());
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
    if (!_updating)
    {
        _updating = true;

        // Clock update
        Managers::clockManager->NewFrame();

        // Events update

        // Logic update

        // Graphic update
        Managers::graphicManager->RenderScene();

        Managers::clockManager->ManageFramesCap();
        Managers::clockManager->UpdateDeltaTime();
        _updating = false;
    }

}
