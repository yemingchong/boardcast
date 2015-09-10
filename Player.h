#ifndef _PLAYER_HEADER_
#define _PLAYER_HEADER_

#include <iostream>
#include <Facade.h>

/**!
	模块 Player 负责管理玩家的数据 和 行为
	模块 PlayerList 负责管理玩家列表

	PlayerListListener 是玩家模块唯一的对外接口
*/

class Player
{
public:
	void add_hp(int val)
	{
		std::cout << "player : add hp " << val << std::endl;

		stream::OStream os;
		os << std::string("add hp");
		SEND_NOTIFY(MSG_SEND_MAIL, os.getBlock())	// 发个邮件
	}
};

class PlayerList
{
	typedef std::map<int, Player*> PlayerMap;
public:

	PlayerList()
	{
		playermap_.insert(PlayerMap::value_type(1, new Player()));
	}

	void add_hp(int val)
	{
		auto itr = playermap_.find(1);
		itr->second->add_hp(val);
	}

private:
	PlayerMap playermap_;
};

class PlayerListListener : public boardcast::IListener
{
public:

	PlayerListListener()
	{
		playerlist_ = new PlayerList();

		init();
	}

	void init()
	{
		boardcast::Facade::getRef().regist_notify(MSG_ADD_HP
			, std::bind(&PlayerListListener::add_hp, this, std::placeholders::_1));
	}

	/**
		如果外部需要player模块的数据 ， 通过listener生成的接口调用
	*/
	bool check_have_hp(int val)
	{
		return false;
	}

private:
	void add_hp(stream::BlockPtr block)
	{
		int _val;
		stream::IStream is(block);
		is >> _val;

		playerlist_->add_hp(_val);
	}

private:
	PlayerList * playerlist_;
};

#endif