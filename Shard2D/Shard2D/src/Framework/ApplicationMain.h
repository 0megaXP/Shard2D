#pragma once

#include "../Framework/GameObjects/Sprite.h"
#include "../Framework/GameObjects/TextField.h"

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
};

