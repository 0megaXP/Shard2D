#pragma once

#include "Framework/Entities/Sprite.h"
#include "Framework/Entities/TextField.h"
#include "Framework/Events/EventTypes/MouseEvent.h"
#include "Framework/Events/EventTypes/KeyboardEvent.h"
#include "Framework/Management/IMain.h"

class ApplicationMain : public Shard2D::IMain
{
public:
	ApplicationMain();

private:
	void Init();

	void Update();


	Shard2D::Entity* logoContainer;
	Shard2D::TextField* logoText;

	Shard2D::Entity* demoContainer;
	Shard2D::TextField* fpsCounter;
	Shard2D::TextField* runtimeText;

	float runtime = 0;
};

