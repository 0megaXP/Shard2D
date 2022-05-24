#include "GameManager.h"

#include <SDL_events.h>
#include <memory>

#include "../Management/Managers.h"
#include "../Events/EventTypes/Event.h"
#include "../Entities/Entity.h"
#include "IMain.h"

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

    void GameManager::SetupGame(IMain* newMain)
    {
        appMain = newMain;
        appMain->Init();
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

            //Tween Update
            M_TweensManager->UpdateTweens();

            // Logic update
            appMain->Update();
            for (Entity* object : M_EntitiesManager->_stagedEntities)
                object->Update();

            // Graphic update
            M_GraphicManager->RenderScene();

            _updating = false;
        }
    }
}