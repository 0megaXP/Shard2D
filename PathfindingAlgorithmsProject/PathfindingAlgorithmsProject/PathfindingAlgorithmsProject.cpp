// PathfindingAlgorithmsProject.cpp : Questo file contiene la funzione 'main', in cui inizia e termina l'esecuzione del programma.
//
#include <iostream>
#include <SDL.h>

#include "GameManager.h"

int main(int argc, char** args)
{
    GameManager* gameManager = new GameManager();
    if (!gameManager->SetupGame())
    {
        std::cout << "Failed to load the game!\n";
        return 0;
    }

    system("pause");

    // Destroy GraphicManager

    return 0;
}