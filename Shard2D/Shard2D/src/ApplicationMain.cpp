#include "ApplicationMain.h"

#include <SDL.h>

#include "Framework/Management/Managers.h"
#include "Framework/Utils/ShardUtils.h"
#include "Framework/Entities/Entity.h"
#include "Framework/Tweens/TweensManager.h"

import MathUtils;
import BooleanUtils;

using namespace Shard2D;

void MouseBeginOverlap(MouseEvent* _event)
{

}

void MouseEndOverlap(MouseEvent* _event)
{

}

void ApplicationMain::Init()
{
    M_GraphicManager->SetDefaultResolution(1280, 720, true);
    M_GraphicManager->ResizeWindow(1280, 720, WindowType::Window);

    M_ClockManager->EnableFrameRateCap(60);

    logoContainer = new Entity();
    logoContainer->a = 0;
    AddToStage(logoContainer);

    logoText = new TextField("Welcome to Shard2D", "Fonts/FiveBoroughsHandwriting", 72);
    logoContainer->AddChild(logoText);
    logoText->centerPivot = true;
    logoText->x = 640;
    logoText->y = 320;

    demoContainer = new Entity();
    demoContainer->a = 0;
    AddToStage(demoContainer);

    fpsCounter = new TextField("", "Fonts/arial", 36);
    fpsCounter->y = 670;
    demoContainer->AddChild(fpsCounter);

    runtimeText = new TextField("Test", "Fonts/arial", 36);
    runtimeText->y = 620;
    demoContainer->AddChild(runtimeText);

    ITween* logoAlphaOn = CreateTween(logoContainer->a, 1.f, 2.f)->Delay(1)->SelfDelete();
    ITween* logoAlphaOff = CreateTween(logoContainer->a, 0.f, 1.f)->Delay(4)->SelfDelete();
    ITween* demoAlphaOn = CreateTween(demoContainer->a, 1.f, 1.f)->Delay(5)->SelfDelete();
    StartTween(logoAlphaOn);
    StartTween(logoAlphaOff);
    StartTween(demoAlphaOn);

}

void ApplicationMain::Update()
{
    fpsCounter->SetText("FPS: " + std::to_string(int(M_ClockManager->GetFPS())));

    runtime += M_ClockManager->GetDeltaTime();
    runtimeText->SetText("Runtime: " + std::to_string(runtime) + " seconds");
}
