#include "Observer.h"


void boardcast::Observer::regist_notify(int msg, NotifyFunc &observer)
{
	notify_map_.insert(NotifyMap::value_type(msg, observer));
}

void boardcast::Observer::remove_notify(int msg)
{
	auto range = notify_map_.equal_range(msg);
	
	notify_map_.erase(range.first, range.second);
}

void boardcast::Observer::notify(int msg, stream::BlockPtr block)
{
	typedef std::vector<NotifyFunc> NotifyList_t;

	NotifyList_t _list;

	do 
	{
		NotifyMap::iterator itr = notify_map_.find(msg);

		for (; itr != notify_map_.end() && itr->first == msg; ++itr)
		{
			_list.push_back(itr->second);	// pushback notify
		}
	} while (false);

	NotifyList_t::const_iterator itr = _list.begin();
	for (; itr != _list.end(); ++itr)
	{
		(*itr)(block);
	}
}
