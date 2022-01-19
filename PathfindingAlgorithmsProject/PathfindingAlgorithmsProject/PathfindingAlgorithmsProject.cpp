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

void HideConsole()
{
    ::ShowWindow(::GetConsoleWindow(), SW_HIDE);
}

void ShowConsole()
{
    ::ShowWindow(::GetConsoleWindow(), SW_SHOW);
}

bool IsConsoleVisible()
{
    return ::IsWindowVisible(::GetConsoleWindow()) != FALSE;
}

int main(int argc, char** args)
{
#if defined _DEBUG
    if (!IsConsoleVisible())
        ShowConsole();
#else
    if (IsConsoleVisible())
        HideConsole();
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

    if (!IsConsoleVisible())
        ShowConsole();

    return 0;
}