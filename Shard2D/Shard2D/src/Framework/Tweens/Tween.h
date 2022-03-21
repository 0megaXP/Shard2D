#pragma once


namespace Shard2D
{
	class Tween
	{
	private:
		Tween();
		~Tween();

		friend class TweensManager;

	private:

		void GetType();
	};
}