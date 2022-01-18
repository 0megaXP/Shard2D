#include "ApplicationMain.h"

#include "CustomIOStream.h"
#include "MathVectors.h"
#include "ClockManager.h"

import MathUtils;
import BooleanUtils;

ApplicationMain::ApplicationMain()
{
	Start();
}

void ApplicationMain::Start()
{
	sprite = new Sprite(Managers::assetsManager->GetImagePNG("Assets/PNGs/Doge.png"));
    AddToStage(sprite);
	sprite->SetVisibility(true);
	sprite->scaleX = 0.5;
	sprite->scaleY = 0.5;
    sprite->x = 500;
    sprite->y = 500;
    sprite->a = 1;
    sprite->rotation = 0;
    sprite->centerPivot = false;

    Sprite* point = new Sprite(Managers::assetsManager->GetImagePNG("Assets/PNGs/RedPoint.png"));
    AddToStage(point);
    point->x = sprite->x;
    point->y = sprite->y;
    point->scaleX = 0.01;
    point->scaleY = 0.01;
    point->centerPivot = true;

    childSprite = new Sprite(Managers::assetsManager->GetImagePNG("Assets/PNGs/Last_Defenders.png"));
    childSprite->scaleX = 0.5;
    childSprite->scaleY = 0.5;
    childSprite->x = 128;
    childSprite->y = 128;
    sprite->AddChild(childSprite);
    childSprite->a = 1;
    childSprite->centerPivot = false;

    superChildSprite = new Sprite(Managers::assetsManager->GetImagePNG("Assets/PNGs/Doge.png"));
    superChildSprite->scaleX = 0.25;
    superChildSprite->scaleY = 0.25;
    superChildSprite->x = 0;
    superChildSprite->y = 0;
    childSprite->AddChild(superChildSprite);
    superChildSprite->a = 1;
    superChildSprite->centerPivot = false;
}

void ApplicationMain::Update()
{
    SDL_Event e;
    //childSprite->rotation++;
    //std::cout << "parent Sprite Fixed position: " << sprite->GlobalFixedX() << " - " << sprite->GlobalFixedY() << std::endl;
    //std::cout << "Child Sprite Fixed position: " << childSprite->GlobalFixedX() << " - " << childSprite->GlobalFixedY() << std::endl;
    //std::cout << "Super Child Sprite Fixed position: " << superChildSprite->GlobalFixedX() << " - " << superChildSprite->GlobalFixedY() << std::endl;

    while (SDL_PollEvent(&e) != 0) {
        switch (e.type) {
        case SDL_QUIT:
            Managers::gameManager->ExitGame();

        case SDL_KEYDOWN:
           //Managers::gameObjectsManager->RemoveObjectFromStage(sprite);
            sprite->rotation += 1;
            break;
        case SDL_KEYUP:
            //Managers::gameObjectsManager->AddObjectToStage(sprite);

            break;
        case SDL_MOUSEMOTION:


            break;
        }
    }
}
