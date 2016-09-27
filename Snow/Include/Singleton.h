/*******************************************************
* Free game engine : SNOW
*
* FileName: Singleton.h
* Summary: 

* Author: maoyanwen
* Date: 2015/06/27 
*******************************************************/
#ifndef Snow_Singleton_h__
#define Snow_Singleton_h__
#include "Define.h"
namespace Snow
{
	template<class T> struct Singleton
	{
	public:
		static T*& Instance()
		{
			static T* sp_instance = NULL;
			if(sp_instance == NULL)
			{
				sp_instance = new T();
			}
			return sp_instance;
		}

		static void DestroyInst()
		{
			if (T*& t = Instance())
			{
				mars_delete(t);
			}
		}
	};
}

#endif // Snow_Singleton_h__
