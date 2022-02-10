#pragma once

#include "../Framework/Entities/Sprite.h"
#include "../Framework/Entities/TextField.h"

class ApplicationMain
{
public:
	ApplicationMain();

private: 
	friend class GameManager;

	void Start();

	void Update();

	Sprite* sprite;
	Sprite* childSprite; 
	Sprite* superChildSprite;

	TextField* fpsCounter;
	TextField* runtimeText;

	float runtime = 0;
};

