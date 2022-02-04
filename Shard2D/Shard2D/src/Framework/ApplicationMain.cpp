#include "ApplicationMain.h"

#include <SDL.h>

#include "Management/Managers.h"
#include "Utils/ShardUtils.h"
#include "Management/Managers.h"
#include "Events/Event.h"
#include "Events/MouseEvent.h"

import MathUtils;
import BooleanUtils;

void EventDispatched(Event* _event)
{
    Log("Event dispatched succesfully!");
}

void SecondEventDispatched(MouseEvent* _event)
{
    Log("Mouse event dispatched succesfully!");
}

ApplicationMain::ApplicationMain()
{
	Start();
}

void ApplicationMain::Start()
{
    GameObject* a = new GameObject();
    AddToStage(a);

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
        superChildSprite->scaleX = 0.30;
        superChildSprite->scaleY = 0.30;
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

    sprite->AddEventListener<Event>("TestEvent", &EventDispatched);
    sprite->AddEventListener<MouseEvent>("TestMouseEvent", &SecondEventDispatched);
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
            sprite->DispatchEvent<Event>("TestEvent");
            //sprite->RemoveEventListener("TestEvent", &EventDispatched);
            break;
        case SDL_KEYUP:
            //Managers::gameObjectsManager->AddObjectToStage(sprite);

            break;
        case SDL_MOUSEBUTTONDOWN:

            sprite->DispatchEvent<MouseEvent>("TestMouseEvent");

            break;
        }
    }
}