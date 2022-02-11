#pragma once

class ApplicationMain;

namespace Shard2D
{
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

		ApplicationMain* appMain;

	public:
		void SetupGame();

		/*
		Function called to close the application. Use this function for a properly memory deallocation
		*/
		void ExitGame();
		bool GetExitGame();

		/*
		This function does not have to be called manually.
		The game main update function.
		*/
		void GameUpdate();
	};
}