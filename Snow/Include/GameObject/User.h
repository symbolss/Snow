/*******************************************************
* Free game engine : SNOW
*
* FileName: User.h
* Summary: Íæ¼Ò

* Author: maoyanwen
* Date: 2015/08/07 
*******************************************************/
#ifndef Snow_User_h__
#define Snow_User_h__

#include "Interface/IGameObject.h"

namespace Snow
{
	class User : public Snow::IGameObject
	{
	public:
		virtual Result InitComponents();

		virtual Result Init();
	}; 
}

#endif // Snow_User_h__