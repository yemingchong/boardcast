#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>

#include "all.hpp"
#include "Player.h"

#include "any.h"

#include <windows.h>

/////////////////////////////////////////////////////////////////////

void func1(int arg1, char arg2, const std::string &arg3)
{
	std::cout << arg1 << arg2 << arg3 << std::endl;
}

void func2(int arg1, char arg2)
{
	std::cout << arg1 << arg2 << std::endl;
}


template <std::size_t ... I , typename F , typename T>
void apply(F f, const T& t)
{
	f(std::get<I>(t)...);
}

typedef std::vector<type::any> TypeList;

int main(int argc, char* argv[])
{
	new boardcast::Facade();

	new PlayerListListener();

	//boardcast::Facade::getRef().send<0,1,2>(MSG_ADD_HP, std::make_tuple(1, 'a', "hello"));

	boardcast::Facade::getRef().send<std::function<void(int)> , 1>(MSG_ADD_HP , std::make_tuple(1));
	//int _hp = 10;
	//std::string _str = "test";

	//TypeList t1;

	//std::function<void(int,char,std::string)> f1 = std::bind(&func1, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
	//t1.push_back(f1);
		//t1.push_back(std::bind(&func2, std::placeholders::_1, std::placeholders::_2));
	
		//apply<0, 1, 2>(t1[0].as<std::function<void(int,char,std::string)>>() , std::make_tuple(1, 'a', "hello"));

		//std::function<void(int, char, std::string)> f2 = ;
	//apply<0, 1, 2>(t1[0].as<std::function<void(int, char, std::string)>>(), std::make_tuple(1, 'a', "hello"));

	// 本来打算用tuple 但是没办法泛化型别 将来考虑用其他实现



	//for (int i = 0; i < 100 * 100; ++i)
	//{
	//	stream::OStream os;
	//	os << _hp << _str;
	//	SEND_NOTIFY(MSG_ADD_HP, os.getBlock())		// 加点血
	//}



	system("pause");
	return 0;
}