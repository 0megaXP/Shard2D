#include "TweensManager.h"

#include "../Utils/CustomIOStream.h"

namespace Shard2D
{
	TweensManager::TweensManager()
	{

	}

	TweensManager::~TweensManager()
	{
		for (ITween* _tween : _createdTweens)
			delete _tween;

		Log("Tweens Manager destroyed!", TextColor::Green);
	}
}
