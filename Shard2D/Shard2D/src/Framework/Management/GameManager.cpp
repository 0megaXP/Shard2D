#include "GameManager.h"

#include <SDL_events.h>
#include <memory>

#include "../Management/Managers.h"
#include "../ApplicationMain.h"
#include "../Events/Event.h"

namespace Shard2D
{
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
        appMain = new ::ApplicationMain();
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
            for (Entity* object : M_EntitiesManager->_stagedEntities)
                object->DispatchEvent<Event>(Event::Update);

            M_EventsManager->CatchInputs();

            // Logic update
            appMain->Update();
            for (Entity* object : M_EntitiesManager->_stagedEntities)
                object->Update();

            // Graphic update
            M_GraphicManager->RenderScene();

            M_ClockManager->ManageFramesCap();
            M_ClockManager->UpdateDeltaTime();
            //DebugFPS(Managers::clockManager->GetFPS());
            _updating = false;
        }
    }
}