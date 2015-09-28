#ifndef _MAIL_HEADER_
#define _MAIL_HEADER_

#include <iostream>

/**!
模块 Mail 负责处理邮件相关的逻辑
MailListener 是 Mail 模块唯一的对外接口
*/
class Mail
{
public:
	Mail(){}	// 外部无法构造

	void send_mail(std::string str)
	{
	}
};

class MailListener : public boardcast::IListener
{
public:
	MailListener()
	{
		mail_ = new Mail();

		init();
	}

	void init()
	{
		boardcast::Facade::getRef().regist_notify(MSG_SEND_MAIL
			, std::bind(&MailListener::send_mail, this, std::placeholders::_1));
	}

private:
	void send_mail(stream::BlockPtr block)
	{
		std::string _str;
		stream::IStream is(block);
		is >> _str;
		mail_->send_mail(_str);
	}

private:

	Mail * mail_;
};

#endif