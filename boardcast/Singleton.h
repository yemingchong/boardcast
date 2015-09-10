#ifndef _SINGLETON_HEADER_
#define _SINGLETON_HEADER_

#include <assert.h>

namespace boardcast
{
	template<typename T>
	class Singleton
	{
	public:
		Singleton()
		{
			assert(!m_singleton);
			m_singleton = static_cast<T*>(this);
		}

		~Singleton(){ m_singleton = 0; }

		static T& getRef() {assert(m_singleton); return (*m_singleton);}

		static T* getPtr() { return (m_singleton);}

	private:
		Singleton& operator = (const Singleton&){return this;}
		Singleton(const Singleton&){}

	protected:
		static T* m_singleton;
	};

	template<typename T> T* Singleton<T>::m_singleton = 0;
}

#endif
