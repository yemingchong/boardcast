#ifndef _FACADE_HEADER_
#define _FACADE_HEADER_

#include "Singleton.h"
#include <functional>
#include "IListener.h"
#include "Observer.h"

#include <tuple>

enum Message
{
	MSG_ADD_HP = 0,
	MSG_SEND_MAIL,
};

namespace boardcast
{
	class Facade : public Singleton<Facade>
	{
	public:
		Facade();

		void regist_notify(int msg, type::any func);

		template <typename F , std::size_t ...I , typename T>
		void send(int msg , const T& t);

	private:
		Observer * ob;
	};
}

void boardcast::Facade::regist_notify(int msg, type::any func)
{
	ob->regist_notify(msg, func);
}

template <typename F, std::size_t ...I, typename T>
void boardcast::Facade::send(int msg , const T& t)
{
	ob->notify<std::function<void(int)>>(msg
		, typename type::make_int_sequence<sizeof... (I)>{}
		, t);
}

boardcast::Facade::Facade()
{
	ob = new Observer();
}


#endif
