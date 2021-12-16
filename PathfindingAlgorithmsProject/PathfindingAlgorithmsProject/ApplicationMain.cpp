#include "ApplicationMain.h"

ApplicationMain::ApplicationMain()
{
	Start();
}

void ApplicationMain::Start()
{
	sprite = new Sprite(Managers::assetsManager->GetImagePNG("Assets/PNGs/Doge.png"));
	Managers::gameObjectsManager->AddObjectToStage(sprite);
	sprite->SetVisibility(true);
	sprite->scaleX = 0.5;
	sprite->scaleY = 0.5;
    sprite->x = 200;
    sprite->y = 200;
    sprite->a = 1;

    childSprite = new Sprite(Managers::assetsManager->GetImagePNG("Assets/PNGs/Doge.png"));


    childSprite->scaleX = 0.25;
    childSprite->scaleY = 0.25;
    sprite->AddChild(childSprite);
    childSprite->a = 0.25;
}

void ApplicationMain::Update()
{
    SDL_Event e;

    while (SDL_PollEvent(&e) != 0) {
        switch (e.type) {
        case SDL_QUIT:

        case SDL_KEYDOWN:
            Managers::gameObjectsManager->RemoveObjectFromStage(sprite);
            break;
        case SDL_KEYUP:
            Managers::gameObjectsManager->AddObjectToStage(sprite);

            break;
        case SDL_MOUSEMOTION:

            break;
        }
    }
}
