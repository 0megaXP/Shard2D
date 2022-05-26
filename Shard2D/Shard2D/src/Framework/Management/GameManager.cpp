/*
The MIT License (MIT)

Copyright (c) 2021-2022 Filippo Alberto Munaro

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

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