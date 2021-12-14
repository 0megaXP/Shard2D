#pragma once

#include "GameObject.h"
#include "Sprite.h"
#include "Managers.h"
#include "AssetsManager.h"
#include "GameObjectsManager.h"
#include "GameManager.h"

class ApplicationMain
{
public:
	ApplicationMain();

private: 
	friend class GameManager;

	void Start();

	void Update();

	Sprite* sprite;
};

