#include "ApplicationMain.h"

#include <SDL.h>

#include "Management/Managers.h"
#include "Utils/ShardUtils.h"
#include "Entities/Entity.h"
#include "Tweens/TweensManager.h"

import MathUtils;
import BooleanUtils;

using namespace Shard2D;

void MouseBeginOverlap(MouseEvent* _event)
{
    Shard2D::Log("Begin Overlap");
    ITween* scalingXTween = CreateTween(static_cast<Entity*>(_event->GetTarget())->scaleX, 0.6f, 0.25f)->Ease(EaseType::SineOut)->SelfDelete();
    ITween* scalingYTween = CreateTween(static_cast<Entity*>(_event->GetTarget())->scaleY, 0.6f, 0.25f)->Ease(EaseType::SineOut)->SelfDelete();
    StartTween(scalingXTween, true);
    StartTween(scalingYTween, true);
}

void MouseEndOverlap(MouseEvent* _event)
{
    Shard2D::Log("End overlap");
    ITween* scalingXTween = CreateTween(static_cast<Entity*>(_event->GetTarget())->scaleX, 0.5f, 0.25f)->Ease(EaseType::SineOut)->SelfDelete();
    ITween* scalingYTween = CreateTween(static_cast<Entity*>(_event->GetTarget())->scaleY, 0.5f, 0.25f)->Ease(EaseType::SineOut)->SelfDelete();
    StartTween(scalingXTween, true);
    StartTween(scalingYTween, true);
}

ApplicationMain::ApplicationMain()
{

}

void ApplicationMain::Init()
{
    M_GraphicManager->SetDefaultResolution(1280, 720, true);
    M_GraphicManager->ResizeWindow(1280, 720, WindowType::Window);

    M_ClockManager->EnableFrameRateCap(60);

    sprite = new Sprite(M_AssetsManager->GetImageFromPNG("PNGs/Doge"));
    AddToStage(sprite);
    sprite->SetVisibility(true);
    sprite->x = 640.f;
    sprite->y = 360.f;
    sprite->scaleX = 0.5;
    sprite->scaleY = 0.5;
    sprite->centerPivot = true;
    sprite->AddEventListener<MouseEvent>(MouseEvent::BeginOverlap, &MouseBeginOverlap);
    sprite->AddEventListener<MouseEvent>(MouseEvent::EndOverlap, &MouseEndOverlap);

    fpsCounter = new TextField("", "Fonts/arial", 36);
    fpsCounter->y = 670;
    AddToStage(fpsCounter);

    runtimeText = new TextField("Test", "Fonts/arial", 36);
    runtimeText->y = 620;
    AddToStage(runtimeText);
}

void ApplicationMain::Update()
{
    fpsCounter->SetText("FPS: " + std::to_string(int(M_ClockManager->GetFPS())));

    runtime += M_ClockManager->GetDeltaTime();
    runtimeText->SetText("Runtime: " + std::to_string(runtime) + " seconds");
}
