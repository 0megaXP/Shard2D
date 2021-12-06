#include "GameManager.h"

#include "GraphicManager.h"
#include "ClockManager.h"
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
        Managers::clockManager->UpdateDeltaTime();

        // Events update

        // Logic update

        // Graphic update
    }
    _updating = false;

    SDL_Delay(Managers::clockManager->GetDeltaTime());
}
