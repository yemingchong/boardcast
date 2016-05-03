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
import socket
import struct
import sys
import time

HOST = '127.0.0.1'
PORT = 9870

BUFSIZE = 1024

addr = (HOST, PORT)
client = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
client.connect(addr)


package_len = 125
message_size = 121
message_id = 145568146

user_name = "test30"
proof_type = 0
version_id = 825110528
distribution_id = 0
password = ""
account_id = 3435973836
client_crc = 0
str_mac_len = 17
str_mac = "9C-5C-8E-7B-9E-F2"
str_guid_len = 0
str_guid = ""


msg = struct.pack('<III32sIII36sIII17sI'\
                  , package_len\
                  , message_size\
                  , message_id\
                  , user_name.encode('utf-8')\
                  , proof_type\
                  , version_id\
                  , distribution_id\
                  , password.encode('utf-8')\
                  , account_id\
                  , client_crc\
                  , str_mac_len\
                  , str_mac.encode('utf-8')\
                  , str_guid_len)
client.send(msg)
