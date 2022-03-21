#pragma once

#include <vector>
#include <memory>

namespace Shard2D
{
	class Tween;

	class TweensManager
	{
	private:
		TweensManager();

		~TweensManager();

		friend class Managers;

	private:
		std::vector<Tween*> _activeTweens;
		std::vector<Tween*> _createdTweens;
		
	public:
		template<typename T>
		Tween* CreateTween(T &value);
	};
}

#include "TweensManager.tpp"