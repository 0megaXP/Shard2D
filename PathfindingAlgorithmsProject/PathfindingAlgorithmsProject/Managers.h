#pragma once

class GameManager;
class GraphicManager;
class ClockManager;
class AssetsManager;

class Managers
{
public:
	static GameManager* gameManager;
	static GraphicManager* graphicManager;
	static ClockManager* clockManager;
	static AssetsManager* assetsManager;
};

