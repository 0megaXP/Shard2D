// PathfindingAlgorithmsProject.cpp : Questo file contiene la funzione 'main', in cui inizia e termina l'esecuzione del programma.
//
#include <iostream>
#include <SDL.h>

#include "GameManager.h"

int main(int argc, char** args)
{
    std::cout << "Hello World!\n";

    GameManager* gameManager = new GameManager();
    if (!gameManager->SetupGame())
    {
        return 0;
    }

    system("pause");

    return 0;
}