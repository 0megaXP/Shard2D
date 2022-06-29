#include "ApplicationMain.h"

#include <SDL.h>

#include "Framework/Management/Managers.h"
#include "Framework/ShardUtils.h"
#include "Framework/Entities/Entity.h"
#include "Framework/Tweens/TweensManager.h"

#include "Framework/ShardTweens.h"

#ifndef _USE_MATH_DEFINES
#define _USE_MATH_DEFINES
#endif

#include <math.h>

//import MathUtils;
//import BooleanUtils;

using namespace Shard2D;

void ApplicationMain::ButtonPressed(KeyboardEvent* _event)
{
    //ITween* tweenX = CreateTween(parent->scaleX, 0.5f, 0.5f)->Ease(EaseType::SineInOut)->SelfDelete();
    ITween* tweenY = CreateTween(parent->rotation, 30.f, 0.5f)->Ease(EaseType::SineInOut)->SelfDelete();
    //StartTween(tweenX, true);
    StartTween(tweenY, true);
}

void ApplicationMain::ButtonReleased(KeyboardEvent* _event)
{
    //ITween* tweenX = CreateTween(parent->scaleX, 1.f, 0.5f)->Ease(EaseType::SineInOut)->SelfDelete();
    ITween* tweenY = CreateTween(parent->rotation, 0.f, 0.5f)->Ease(EaseType::SineInOut)->SelfDelete();
    //StartTween(tweenX, true);
    StartTween(tweenY, true);
}

void ApplicationMain::Init()
{
    M_GraphicManager->SetDefaultResolution(1280, 720, true);
    M_GraphicManager->ResizeWindow(640, 360, WindowType::Window);

    M_ClockManager->EnableFrameRateCap(60);

    logoContainer = new Entity();
    logoContainer->a = 0;
    AddToStage(logoContainer);

    logoText = new TextField("Welcome to Shard2D", "Assets/Fonts/FiveBoroughsHandwriting.ttf", 72);
    logoContainer->AddChild(logoText);
    logoText->centerPivot = true;
    logoText->x = 640;
    logoText->y = 320;

    demoContainer = new Entity();
    demoContainer->a = 0;
    AddToStage(demoContainer);

    fpsCounter = new TextField("", "Assets/Fonts/arial.ttf", 36);
    fpsCounter->y = 670;
    demoContainer->AddChild(fpsCounter);

    runtimeText = new TextField("Test", "Assets/Fonts/arial.ttf", 36);
    runtimeText->y = 620;
    demoContainer->AddChild(runtimeText);

    ITween* logoAlphaOn = CreateTween(logoContainer->a, 1.f, 2.f)->Delay(1)->SelfDelete();
    ITween* logoAlphaOff = CreateTween(logoContainer->a, 0.f, 1.f)->Delay(4)->SelfDelete();
    ITween* demoAlphaOn = CreateTween(demoContainer->a, 1.f, 1.f)->Delay(5)->SelfDelete();
    StartTween(logoAlphaOn);
    StartTween(logoAlphaOff);
    StartTween(demoAlphaOn);

    parent = new Sprite(M_AssetsManager->GetImageFromPNG("Assets/PNGs/Doge.png"));
    parent->x = 640;
    parent->y = 360;
    parent->rotation = 0;
    parent->centerPivot = true;
    demoContainer->AddChild(parent);

    child = new Sprite(M_AssetsManager->GetImageFromPNG("Assets/PNGs/Doge.png"));
    child->x = -parent->width / 4;
    child->y = parent->height / 4;
    child->scaleX = 0.5;
    child->scaleY = 0.5;
    child->centerPivot = true;
    child->blockMouseEvents = false;
    parent->AddChild(child);

    grandChild = new Sprite(M_AssetsManager->GetImageFromPNG("Assets/PNGs/Doge.png"));
    grandChild->x = child->width / 4;
    grandChild->y = -child->height / 4;
    grandChild->scaleX = 0.5;
    grandChild->scaleY = 0.5;
    grandChild->centerPivot = true;
    grandChild->blockMouseEvents = false;
    child->AddChild(grandChild);

    spriteScaleDebug = new TextField("Test", "Assets/Fonts/arial.ttf", 36);
    spriteScaleDebug->y = 570;
    demoContainer->AddChild(spriteScaleDebug);

    //parent->AddEventListener<KeyboardEvent, ApplicationMain>(KeyboardEvent::ButtonPressed, &ApplicationMain::ButtonPressed, this);
    //parent->AddEventListener<KeyboardEvent, ApplicationMain>(KeyboardEvent::ButtonReleased, &ApplicationMain::ButtonReleased, this);

    ITween* tweenX = CreateTween(parent->scaleX, 0.25f, 0.5f)->Ease(EaseType::SineInOut)->Repeat(-1)->Reflect();
    ITween* tweenY = CreateTween(parent->scaleY, 0.25f, 0.5f)->Ease(EaseType::SineInOut)->Repeat(-1)->Reflect();
    //ITween* tweenRot = CreateTween(parent->rotation, 360.f, 1.5f)->Ease(EaseType::SineInOut)->Repeat(6)->Reflect()->SelfDelete();
    StartTween(tweenX, true);
    StartTween(tweenY, true);
    //StartTween(tweenRot, true);
}

void ApplicationMain::Update()
{
    fpsCounter->SetText("FPS: " + std::to_string(int(M_ClockManager->GetFPS())));

    runtime += M_ClockManager->GetDeltaTime();
    runtimeText->SetText("Runtime: " + std::to_string(runtime) + " seconds");

    if (parent->scaleX != parent->scaleY)
        Log("Fail!");
    //spriteScaleDebug->SetText("Rendering X: " + std::to_string(grandChild->_finalFixedX) + " - Rendering Y: " + std::to_string(grandChild->_finalFixedY));
}
