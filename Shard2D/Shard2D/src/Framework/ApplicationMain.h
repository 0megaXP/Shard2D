#pragma once

#include "../Framework/Entities/Sprite.h"
#include "../Framework/Entities/TextField.h"
#include "Events/MouseEvent.h"
#include "Events/KeyboardEvent.h"

class ApplicationMain
{
public:
	ApplicationMain();

private: 
	friend class Shard2D::GameManager;

	void Start();

	void Update();

	void TestMethod(Shard2D::KeyboardEvent* _event);

	Shard2D::Sprite* sprite;
	Shard2D::Sprite* childSprite; 
	Shard2D::Sprite* superChildSprite;

	Shard2D::TextField* fpsCounter;
	Shard2D::TextField* runtimeText;

	float runtime = 0;
};

