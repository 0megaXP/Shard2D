#include "Event.h"

namespace Shard2D
{
    std::string Event::GetType() const
    {
        return _type;
    }

    EventDispatcher* Event::GetTarget() const
    {
        return _target;
    }
}