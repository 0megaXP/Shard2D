#pragma once

namespace Shard2D
{
	class ITween
	{
	protected:
		ITween();
		~ITween();

		friend class TweensManager;

	protected:

		virtual void UpdateValue() = 0;

	};
}