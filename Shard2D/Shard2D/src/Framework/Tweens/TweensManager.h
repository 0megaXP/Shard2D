#pragma once

#include <vector>
#include <memory>

namespace Shard2D
{
	class ITween;

	class TweensManager
	{
	private:
		TweensManager();

		~TweensManager();

		friend class Managers;

	private:
		std::vector<ITween*> _activeTweens;
		std::vector<ITween*> _createdTweens;
		
	public:
		template<typename T>
		ITween* CreateTween(T& value, T targetValue, float duration);
	};
}

#include "TweensManager.tpp"