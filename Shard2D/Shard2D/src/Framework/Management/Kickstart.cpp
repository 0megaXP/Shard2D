#include "Kickstart.h"
#include <iostream>
#include <SDL.h>
#include <Windows.h>

#include "Managers.h"
#include "IMain.h"

namespace Shard2D
{
    void Init(IMain* newMain)
    {
#if defined _DEBUG
        if (::IsWindowVisible(::GetConsoleWindow()) == FALSE)
            ::ShowWindow(::GetConsoleWindow(), SW_SHOW);
#else
        if (::IsWindowVisible(::GetConsoleWindow()) == TRUE)
            ::ShowWindow(::GetConsoleWindow(), SW_HIDE);
#endif

        M_GameManager->SetupGame(newMain);

        while (!M_GameManager->GetExitGame())
        {
            M_GameManager->GameUpdate();
        }

        Close();
    }

    void Close()
    {
        Managers::DeleteManagers();

        if (::IsWindowVisible(::GetConsoleWindow()) == FALSE)
            ::ShowWindow(::GetConsoleWindow(), SW_SHOW);
    }
}