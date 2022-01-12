#include <iostream>
#include <SDL.h>

#include "GameManager.h"
#include "GameObjectsManager.h"
#include "AssetsManager.h"
#include "GameManager.h"
#include "ClockManager.h"
#include "GraphicManager.h"
#include "Managers.h"

int main(int argc, char** args)
{
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

    return 0;
}