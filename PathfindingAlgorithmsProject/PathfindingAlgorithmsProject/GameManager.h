#pragma once

class ClockManager;
class GraphicManager;

class GameManager
{
public:
	GameManager();
	~GameManager();

private:
	ClockManager* _clockManager;
	GraphicManager* _graphicManager;

public:
	bool SetupGame();

};

