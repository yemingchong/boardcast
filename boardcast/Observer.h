#ifndef _OBSERVER_HEADER_
#define _OBSERVER_HEADER_

#include <unordered_map>
#include <functional>
#include "stream/OStream.hpp"

namespace boardcast
{
	class Observer
	{
		typedef std::function<void(stream::BlockPtr)> NotifyFunc;
		typedef std::unordered_multimap<int, NotifyFunc> NotifyMap;

	public:

		void regist_notify(int msg, NotifyFunc &nofity);

		/**
			std::function 不支持== , 这里先设定为只能删除所有绑定在msg上面的observer
		*/
		void remove_notify(int msg);

		void notify(int msg, stream::BlockPtr block);

	private:
		NotifyMap notify_map_;
	};
}

#endif // !_MODULE_HEADER_
