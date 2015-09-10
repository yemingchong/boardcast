#ifndef _STREAM_BLOCK_HEADER__
#define _STREAM_BLOCK_HEADER__

#include <string>
#include <string.h>
#include <memory>
#include "OutOfBound.hpp"

namespace stream
{
	//! 内存块结构
	class Block
	{
	public:
		//! 构造函数
		Block(
			size_t total = 64	//!< 总数据大小
			);
		
		//! 析构函数
		virtual ~Block();

		bool incDataSize(size_t incSize);

		char * buffer;		//!< 缓冲区指针
		size_t size;		//!< 数据长度
		size_t total;		//!< 总的数据大小
	};
	
	typedef std::shared_ptr<Block> BlockPtr;

	//! 构造函数
	inline Block::Block( size_t total /*= 64*/)
	{
		this->total = total;
		if (this->total == 0) this->total = 1;
		this->size = 0;
		this->buffer = static_cast<char*>(malloc(total));
	}

	//! 析构函数
	inline Block::~Block()
	{
		if (this->buffer)
		{
			free(this->buffer);
			this->buffer = NULL;
		}
	}

	inline bool Block::incDataSize(size_t incSize)
	{
		size_t tmpSize = size + incSize;

		if (tmpSize < size)
		{
			throw stream::OutOfBound("wrapped in Block::incDataSize");
		}

		if (tmpSize <= total)
		{
			size = tmpSize;
			return false;
		}

		size_t doubleSize = total;
		while (doubleSize < tmpSize)
		{
			doubleSize <<= 1;
		}
		char* tmpBuffer = static_cast<char*>(malloc(doubleSize));
		memcpy(tmpBuffer, buffer, size);
		free(buffer);
		buffer = tmpBuffer;
		size = tmpSize;
		total = doubleSize;
		return true;
	}
}

#endif
