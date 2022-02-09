#include "ApplicationMain.h"

#include <SDL.h>

#include "Management/Managers.h"
#include "Utils/ShardUtils.h"
#include "Management/Managers.h"
#include "Events/Event.h"
#include "Events/MouseEvent.h"
#include "Events/KeyboardEvent.h"

import MathUtils;
import BooleanUtils;

void MouseBeginOverlap(MouseEvent* _event)
{
    Log("Begin Overlap");
}

void MouseEndOverlap(MouseEvent* _event)
{
    Log("End overlap");
}

void LeftButtonClicked(KeyboardEvent* _event)
{
    std::cout << "Key pressed: " << _event->GetKeycode() << std::endl;
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
	sprite->scaleX = 0.5f;
	sprite->scaleY = 0.5f;
    sprite->x = 640.f;
    sprite->y = 360.f;
    sprite->a = 1.f;
    sprite->rotation = 45;
    sprite->centerPivot = true;

    childSprite = new Sprite(M_AssetsManager->GetTextureImagePNG("Last_Defenders"));
    childSprite->scaleX = 0.5f;
    childSprite->scaleY = 0.5f;
    childSprite->x = 128.f;
    childSprite->y = 128.f;
    sprite->AddChild(childSprite);
    childSprite->a = 1;
    childSprite->centerPivot = true;
    childSprite->blockMouseEvents = false;

    for (int i = 0; i < 1; i++)
    {
        superChildSprite = new Sprite(M_AssetsManager->GetTextureImagePNG("Doge"));
        superChildSprite->scaleX = 0.30f;
        superChildSprite->scaleY = 0.30f;
        superChildSprite->x = 64.f;
        superChildSprite->y = 64.f;
        childSprite->AddChild(superChildSprite);
        superChildSprite->a = 1.f;
        superChildSprite->centerPivot = true;
    }

    fpsCounter = new TextField("Test", "arial", 36);
    fpsCounter->y = 670;
    AddToStage(fpsCounter);

    for (int i = 0; i < 1; i++)
    {
        TextField* b = new TextField("This is a sad day for ulthuan, when Asurs fight Asurs within sight of the white tower!", "arial", 36);
        b->scaleX = 1;
        b->scaleY = 1;
        b->centerPivot = true;
        b->x = 640;
        b->y = 50;
        b->SetColor(SDL_Color(255, 255, 255, 255));
        AddToStage(b);
    }

    /*TextField* b = new TextField("This is a sad day for ulthuan, when Asurs fight Asurs within sight of the white tower!", "arial", 72);
    b->scaleX = 1;
    b->scaleY = 1;
    b->centerPivot = true;
    b->x = 640;
    b->y = 360;
    b->SetColor(SDL_Color(255, 255, 0, 255));
    AddToStage(b);*/

    sprite->AddEventListener<MouseEvent>(MouseEvent::BeginOverlap, &MouseBeginOverlap);
    sprite->AddEventListener<MouseEvent>(MouseEvent::EndOverlap, &MouseEndOverlap);
    sprite->AddEventListener<KeyboardEvent>(KeyboardEvent::ButtonPressed, &LeftButtonClicked);

    //sprite->AddEventListener<Event>("TestEvent", &EventDispatched);
    //sprite->AddEventListener<MouseEvent>("TestEvent", &SecondEventDispatched);
}

void ApplicationMain::Update()
{
    fpsCounter->SetText("FPS: " + std::to_string(int(M_ClockManager->GetFPS())));
    //point->x = sprite->RenderingX();
    //point->y = sprite->RenderingY();

    //SDL_Event e;
    //childSprite->rotation -= 180 * M_ClockManager->GetDeltaTime();
    //superChildSprite->rotation += 360 * M_ClockManager->GetDeltaTime();
    //sprite->rotation += 30 * M_ClockManager->GetDeltaTime();

   

    /*while (SDL_PollEvent(&e) != 0) {
        switch (e.type) {
        case SDL_QUIT:
            Managers::gameManager->ExitGame();

        case SDL_KEYDOWN:
           //Managers::gameObjectsManager->RemoveObjectFromStage(sprite);
            //sprite->rotation += 360 * M_ClockManager->GetDeltaTime();
            //sprite->DispatchEvent<Event>("TestEvent");
            //sprite->RemoveEventListener<Event>("TestEvent", &EventDispatched);
            //sprite->RemoveEventListener("TestEvent", &EventDispatched);
            break;
        case SDL_KEYUP:
            //Managers::gameObjectsManager->AddObjectToStage(sprite);

            break;
        case SDL_MOUSEBUTTONDOWN:

            //sprite->DispatchEvent<MouseEvent>("TestEvent");
            //sprite->RemoveEventListener<MouseEvent>("TestEvent", &SecondEventDispatched);
            
            //int mouseX = 0;
            //int mouseY = 0;
            //if (SDL_GetMouseState(&mouseX, &mouseY))
            //{
            //    std::cout << mouseX << " - " << mouseY << std::endl;
            //}
            //
            //if (PointInsideRect(Vector2(mouseX, mouseY), Vector2(sprite->RenderingX(), sprite->RenderingY()), sprite->width * sprite->GlobalScaleX(), sprite->height * sprite->GlobalScaleY(), sprite->GlobalRotation()))
            //    std::cout << "Point Inside!" << std::endl;
           
            break;
        }
    }*/
}