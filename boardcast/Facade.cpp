#include "Facade.h"
#include "Observer.h"

#include "../Player.h"
#include "../Mail.h"

void boardcast::Facade::regist_notify(int msg, NotifyFunc func)
{
	ob->regist_notify(msg, func);
}

void boardcast::Facade::send(int msg, stream::BlockPtr block)
{
	ob->notify(msg, block);
}

boardcast::Facade::Facade()
{
	ob = new Observer();

	player_listener_ = new PlayerListListener();
	mail_listener_ = new MailListener();
}

bool boardcast::Facade::check_have_hp(int val)
{
	return player_listener_->check_have_hp(val);
}
