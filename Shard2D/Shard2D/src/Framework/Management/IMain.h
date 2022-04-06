#pragma once

namespace Shard2D
{
	class IMain
	{
	public:
		IMain() = default;

	protected:
		friend class GameManager;

		virtual void Start() = 0;

		virtual void Update() = 0;
	};
}