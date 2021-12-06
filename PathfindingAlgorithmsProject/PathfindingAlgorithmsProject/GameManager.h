#pragma once

class ClockManager;
class GraphicManager;

class GameManager
{
public:
	GameManager();
	~GameManager();

private:
	bool _updating = false;
	bool _exitGame = false;

public:
	void SetupGame();

	void ExitGame();
	bool GetExitGame();

	void GameUpdate();
};

