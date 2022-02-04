#include "GameManager.h"

#include <SDL_events.h>
#include <memory>

#include "../Management/Managers.h"
#include "../ApplicationMain.h"
#include "../Events/Event.h"

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
        for (GameObject* object : M_GameObjectsManager->_stagedObjects)
            object->DispatchEvent<Event>(Event::Update);

        // Logic update
        appMain->Update();
        for (GameObject* object : M_GameObjectsManager->_stagedObjects)
            object->Update();

        // Graphic update
        M_GraphicManager->RenderScene();

        M_ClockManager->ManageFramesCap();
        M_ClockManager->UpdateDeltaTime();
        DebugFPS(Managers::clockManager->GetFPS());
        _updating = false;
    }
}
