#pragma once

namespace Shard2D
{
	class IMain
	{
	public:
		IMain() = default;

	protected:
		friend class GameManager;

		virtual void Init() = 0;

		virtual void Update() = 0;
	};
}