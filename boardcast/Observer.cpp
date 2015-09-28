#include "Observer.h"


void boardcast::Observer::regist_notify(int msg, type::any func)
{
	notify_map_.insert(NotifyMap::value_type(msg, func));
}

void boardcast::Observer::remove_notify(int msg)
{
	auto range = notify_map_.equal_range(msg);
	
	notify_map_.erase(range.first, range.second);
}


