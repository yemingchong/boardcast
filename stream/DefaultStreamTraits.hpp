
#ifndef _STREAM_DEFAULTSTREAMTRAITS_HEADER__
#define _STREAM_DEFAULTSTREAMTRAITS_HEADER__

#include "Endian.hpp"

namespace stream
{
	//! 默认流特征类
	struct DefaultStreamTraits
	{
	public:
		typedef LittleEndian	IntEndian;				//!< 整数类型序列
		typedef unsigned short	LengthType;				//!< 字符串长度类型
	};
}

#endif
