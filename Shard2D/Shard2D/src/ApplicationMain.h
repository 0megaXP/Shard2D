#pragma once

#include "Framework/Entities/Sprite.h"
#include "Framework/Entities/TextField.h"
#include "Framework/Events/EventTypes/MouseEvent.h"
#include "Framework/Events/EventTypes/KeyboardEvent.h"
#include "Framework/Management/IMain.h"

class ApplicationMain : public Shard2D::IMain
{
private:
	void Init();

	void Update();

	Shard2D::Entity* logoContainer;
	Shard2D::TextField* logoText;

	Shard2D::Entity* demoContainer;
	Shard2D::TextField* fpsCounter;
	Shard2D::TextField* runtimeText;

	Shard2D::Sprite* parent;
	Shard2D::Sprite* child;
	Shard2D::Sprite* grandChild;
	Shard2D::TextField* spriteScaleDebug;

	void ButtonPressed(Shard2D::KeyboardEvent* _event);

	void ButtonReleased(Shard2D::KeyboardEvent* _event);

	float runtime = 0;
};

