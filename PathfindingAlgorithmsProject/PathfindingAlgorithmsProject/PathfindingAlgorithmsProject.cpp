// PathfindingAlgorithmsProject.cpp : Questo file contiene la funzione 'main', in cui inizia e termina l'esecuzione del programma.
//
#include <iostream>
#include <SDL.h>

#include "GameManager.h"
#include "ClockManager.h"
#include "GraphicManager.h"
#include "Managers.h"

int main(int argc, char** args)
{
    Managers::gameManager->SetupGame();

    while (!Managers::gameManager->GetExitGame())
    {
        Managers::gameManager->GameUpdate();
    }

    delete Managers::gameManager;
    delete Managers::assetsManager;
    delete Managers::gameObjectsManager;
    delete Managers::clockManager;
    delete Managers::graphicManager;

    return 0;
}