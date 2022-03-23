#include "ITween.h"

namespace Shard2D
{
	ITween::ITween() {}

	ITween::~ITween()
	{
		Log("Tween destroyed!", TextColor::Aqua);
	}
}
