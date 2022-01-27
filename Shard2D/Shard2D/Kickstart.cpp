#include "Kickstart.h"
#include <iostream>
#include <SDL.h>
#include <Windows.h>

#include "GameManager.h"
#include "GameObjectsManager.h"
#include "AssetsManager.h"
#include "GameManager.h"
#include "ClockManager.h"
#include "GraphicManager.h"
#include "Managers.h"

void Shard2D::Init()
{
#if defined _DEBUG
    if (::IsWindowVisible(::GetConsoleWindow()) == FALSE)
        ::ShowWindow(::GetConsoleWindow(), SW_SHOW);
#else
    if (::IsWindowVisible(::GetConsoleWindow()) == TRUE)
        ::ShowWindow(::GetConsoleWindow(), SW_HIDE);
#endif

    M_GameManager->SetupGame();

    while (!M_GameManager->GetExitGame())
    {
        M_GameManager->GameUpdate();
    }

    delete M_AssetsManager;
    delete M_ClockManager;
    delete M_GraphicManager;
    delete M_GameObjectsManager;
    delete M_GameManager;

    if (::IsWindowVisible(::GetConsoleWindow()) == FALSE)
        ::ShowWindow(::GetConsoleWindow(), SW_SHOW);
}
