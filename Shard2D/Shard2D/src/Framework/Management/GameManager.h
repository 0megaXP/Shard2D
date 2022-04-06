#pragma once

namespace Shard2D
{
	class IMain;
	class ClockManager;
	class GraphicManager;

	class GameManager
	{
	private:
		GameManager();
		~GameManager();

		friend class Managers;

		bool _updating = false;
		bool _exitGame = false;

		IMain* appMain;

	public:
		void SetupGame(IMain* newMain);

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