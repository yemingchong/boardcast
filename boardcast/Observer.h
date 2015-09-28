#ifndef _OBSERVER_HEADER_
#define _OBSERVER_HEADER_

#include <unordered_map>
#include <functional>

#include "../any.h"
#include "../Bind.hpp"

namespace boardcast
{
	class Observer
	{
		typedef std::unordered_multimap<int, type::any> NotifyMap;

	public:

		void regist_notify(int msg, type::any func);

		/**
			std::function 不支持== , 这里先设定为只能删除所有绑定在msg上面的observer
		*/
		void remove_notify(int msg);

		/**
			广播消息 （带参）
		*/
		template <typename F, std::size_t ... I, typename T>
		void notify(int msg, type::int_sequence<I...>, const T& t);

		/**
			广播消息 （不带参）
		*/
		template <typename F>
		void notify(int msg);

	private:
		NotifyMap notify_map_;
	};
}


template <typename F , std::size_t ... I, typename T>
void boardcast::Observer::notify(int msg, type::int_sequence<I...> , const T& t)
{
	typedef std::vector<type::any> NotifyList_t;

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
		(*itr).as<F>()(std::get<I>(t)...);
	}
}


template <typename F>
void boardcast::Observer::notify(int msg)
{
	typedef std::vector<type::any> NotifyList_t;

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
		(*itr).as<F>()();
	}
}



#endif // !_MODULE_HEADER_
