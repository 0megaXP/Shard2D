#pragma once

class ClockManager;
class GraphicManager;
class ApplicationMain;

class GameManager
{
public:
	GameManager();
	~GameManager();

private:
	bool _updating = false;
	bool _exitGame = false;

	ApplicationMain* appMain;

public:
	void SetupGame();

	void ExitGame();
	bool GetExitGame();

	void GameUpdate();
};

