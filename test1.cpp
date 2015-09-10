#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#include <Facade.h>

/////////////////////////////////////////////////////////////////////

int main(int argc, char* argv[])
{
	new boardcast::Facade();

	int _hp = 10;

	// 本来打算用tuple 但是没办法泛化型别 将来考虑用其他实现
	stream::OStream os;
	os << _hp;
	SEND_NOTIFY(MSG_ADD_HP, os.getBlock())		// 加点血

	system("pause");
	return 0;
}