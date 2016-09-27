/*******************************************************
* Free game engine : SNOW
*
* FileName: ComTest.h
* Summary: TEST

* Author: maoyanwen
* Date: 2015/08/07 
*******************************************************/
#ifndef Snow_ComTest_h__
#define Snow_ComTest_h__

#include "Interface/IComponent.h"
#include "Interface/IGameObject.h"
#include "EventDefine.h"

namespace Snow
{
	class ComTest : public IComponent
	{
	public:
		ComTest(IGameObject* pGameObject):IComponent(pGameObject){};

		virtual Result Init();

		static Result TestProcess(EventTest* evt, void* data);
	};
}

#endif // Snow_ComTest_h__