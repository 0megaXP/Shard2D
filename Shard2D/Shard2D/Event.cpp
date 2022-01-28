#include "Event.h"

std::string Event::GetType() const
{
    return _type;
}

EventDispatcher* Event::GetTarget() const
{
    return _target;
}
