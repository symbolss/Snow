/*******************************************************
* Free game engine : SNOW
*
* FileName: IInterface.h
* Summary: Base Interface

* Author: maoyanwen
* Date: 2015/06/05 
*******************************************************/
#ifndef Snow_IInterface_h__
#define Snow_IInterface_h__

#include "Define.h"

namespace Snow
{
	class IInterface
	{
	public:
		/*template<typename T>
		Result QueryInterface(T* pInterface) = 0;*/
		virtual ~IInterface(){};
	};
}

#endif // Snow_IInterface_h__