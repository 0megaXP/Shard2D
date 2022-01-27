#include "GameManager.h"

#include <memory>

#include "GraphicManager.h"
#include "ClockManager.h"
#include "AssetsManager.h"
#include "GameObjectsManager.h"
#include "Managers.h"
#include "GameObject.h"
#include "ApplicationMain.h"
#include <SDL_events.h>
#include "CustomIOStream.h"

GameManager::GameManager()
{
    std::cout << "GameManager created!" << std::endl;
}

GameManager::~GameManager()
{
    std::cout << "GameManager destroyed!" << std::endl;
}

void GameManager::SetupGame()
{
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
    if (!_updating)
    {
        _updating = true;
        // Clock update
        M_ClockManager->NewFrame();

        // Events update

        // Logic update
        appMain->Update();

        // Graphic update
        M_GraphicManager->RenderScene();

        M_ClockManager->ManageFramesCap();
        M_ClockManager->UpdateDeltaTime();
        DebugFPS(Managers::clockManager->GetFPS());
        _updating = false;
    }
}
