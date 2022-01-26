#include "ApplicationMain.h"

#include <SDL.h>

#include "CustomIOStream.h"
#include "MathVectors.h"
#include "ClockManager.h"
#include "TextField.h"

import MathUtils;
import BooleanUtils;

ApplicationMain::ApplicationMain()
{
	Start();
}

void ApplicationMain::Start()
{
	sprite = new Sprite(M_AssetsManager->GetTextureImagePNG("Doge"));
    AddToStage(sprite);
	sprite->SetVisibility(true);
	sprite->scaleX = 0.5;
	sprite->scaleY = 0.5;
    sprite->x = 640;
    sprite->y = 360;
    sprite->a = 1;
    sprite->rotation = 0;
    sprite->centerPivot = true;

    Sprite* point = new Sprite(M_AssetsManager->GetTextureImagePNG("RedPoint"));
    AddToStage(point);
    point->x = sprite->x;
    point->y = sprite->y;
    point->scaleX = 0.01;
    point->scaleY = 0.01;
    point->centerPivot = true;

    childSprite = new Sprite(M_AssetsManager->GetTextureImagePNG("Last_Defenders"));
    childSprite->scaleX = 0.5;
    childSprite->scaleY = 0.5;
    childSprite->x = 128;
    childSprite->y = 128;
    sprite->AddChild(childSprite);
    childSprite->a = 1;
    childSprite->centerPivot = true;

    for (int i = 0; i < 1; i++)
    {
        superChildSprite = new Sprite(M_AssetsManager->GetTextureImagePNG("Doge"));
        superChildSprite->scaleX = 0.25;
        superChildSprite->scaleY = 0.25;
        superChildSprite->x = 64;
        superChildSprite->y = 64;
        childSprite->AddChild(superChildSprite);
        superChildSprite->a = 1;
        superChildSprite->centerPivot = true;
    }

    for (int i = 0; i < 1; i++)
    {
        TextField* b = new TextField("This is a sad day for ulthuan, when Asurs fight Asurs within sight of the white tower!", "arial", 24);
        b->scaleX = 1;
        b->scaleY = 1;
        b->centerPivot = true;
        b->x = 640;
        b->y = 50;
        b->SetColor(SDL_Color(255, 255, 255, 255));
        AddToStage(b);
    }

        TextField* b = new TextField("This is a sad day for ulthuan, when Asurs fight Asurs within sight of the white tower!","arial", 24);
        b->scaleX = 1;
        b->scaleY = 1;
        b->centerPivot = true;
        b->x = 640;
        b->y = 360;
        b->SetColor(SDL_Color(255, 255, 0, 255));
        AddToStage(b);
}

void ApplicationMain::Update()
{
    SDL_Event e;
    childSprite->rotation -= 180 * M_ClockManager->GetDeltaTime();
    superChildSprite->rotation += 360 * M_ClockManager->GetDeltaTime();
    sprite->rotation += 30 * M_ClockManager->GetDeltaTime();

    while (SDL_PollEvent(&e) != 0) {
        switch (e.type) {
        case SDL_QUIT:
            Managers::gameManager->ExitGame();

        case SDL_KEYDOWN:
           //Managers::gameObjectsManager->RemoveObjectFromStage(sprite);
            //sprite->rotation += 360 * M_ClockManager->GetDeltaTime();
            break;
        case SDL_KEYUP:
            //Managers::gameObjectsManager->AddObjectToStage(sprite);

            break;
        case SDL_MOUSEMOTION:


            break;
        }
    }
}
