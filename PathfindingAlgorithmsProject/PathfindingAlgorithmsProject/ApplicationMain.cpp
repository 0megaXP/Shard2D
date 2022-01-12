#include "ApplicationMain.h"

#include "CustomIOStream.h"
#include "MathVectors.h"
#include "MathVectors.h"

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
    sprite->x = 200;
    sprite->y = 200;
    sprite->a = 1;
    sprite->rotation = 0;
    sprite->centerPivot = true;

    Sprite* point = new Sprite(Managers::assetsManager->GetImagePNG("Assets/PNGs/RedPoint.png"));
    AddToStage(point);
    point->x = sprite->x;
    point->y = sprite->y;
    point->scaleX = 0.01;
    point->scaleY = 0.01;
    point->centerPivot = true;

    /*childSprite = new Sprite(Managers::assetsManager->GetImagePNG("Assets/PNGs/Last_Defenders.png"));


    childSprite->scaleX = 0.5;
    childSprite->scaleY = 0.5;
    sprite->AddChild(childSprite);
    childSprite->a = 1;*/

    /*int angle1 = 0;
    int angle2 = 90;
    int angle3 = 180;
    int angle4 = 270;

    std::cout << NormalizedVectorFromAngle(angle1) << std::endl;
    std::cout << NormalizedVectorFromAngle(angle2) << std::endl;
    std::cout << NormalizedVectorFromAngle(angle3) << std::endl;
    std::cout << NormalizedVectorFromAngle(angle4) << std::endl;*/
}

void ApplicationMain::Update()
{
    SDL_Event e;
    sprite->rotation += 1;

    while (SDL_PollEvent(&e) != 0) {
        switch (e.type) {
        case SDL_QUIT:
            Managers::gameManager->ExitGame();

        case SDL_KEYDOWN:
           //Managers::gameObjectsManager->RemoveObjectFromStage(sprite);
            break;
        case SDL_KEYUP:
            //Managers::gameObjectsManager->AddObjectToStage(sprite);

            break;
        case SDL_MOUSEMOTION:


            break;
        }
    }
}
