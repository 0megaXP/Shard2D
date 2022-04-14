#pragma once

#define SDL_MAIN_HANDLED

namespace Shard2D
{
	class IMain;

	void Init(IMain* newMain);
	void Close();
}

