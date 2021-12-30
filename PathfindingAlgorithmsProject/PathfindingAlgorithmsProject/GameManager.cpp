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

    // Clock update
    Managers::clockManager->NewFrame();

    // Events update

    // Logic update
    appMain->Update();

    // Graphic update
    Managers::graphicManager->RenderScene();

    Managers::clockManager->ManageFramesCap();
    Managers::clockManager->UpdateDeltaTime();
    //DebugFPS(((1 / Managers::clockManager->_deltaTime) * 1000));
}
