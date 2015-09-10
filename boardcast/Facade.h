#ifndef _FACADE_HEADER_
#define _FACADE_HEADER_

#include "Singleton.h"
#include <functional>
#include "IListener.h"
#include "stream/OStream.hpp"
#include "stream/IStream.hpp"

enum Message
{
	MSG_ADD_HP = 0,
	MSG_SEND_MAIL,
};

class PlayerListListener;
class MailListener;

namespace boardcast
{
	class Observer;
	typedef std::function<void(stream::BlockPtr)> NotifyFunc;

	class Facade : public Singleton<Facade>
	{
	public:
		Facade();

		void regist_notify(int msg, NotifyFunc func);

		void send(int msg, stream::BlockPtr block);

		//
		bool check_have_hp(int val);

	private:
		Observer * ob;

		PlayerListListener *player_listener_;
		MailListener *mail_listener_;
	};
}

#define SEND_NOTIFY(msg , block)\
	boardcast::Facade::getRef().send(msg, block);

#endif
