/*******************************************************
* Free game engine : SNOW
*
* FileName: ComEventBus.h
* Summary: EventBus×é¼þ

* Author: maoyanwen
* Date: 2015/08/07 
*******************************************************/
#ifndef Snow_ComEventBus_h__
#define Snow_ComEventBus_h__

#include "Interface/IComponent.h"
#include "EventBus.h"

namespace Snow
{
	class ComEventBus : public EventBus, public IComponent
	{
	public:
		ComEventBus(IGameObject*pGameObject):IComponent(pGameObject){};

		virtual Result Init();
	};
}

#endif // Snow_ComEventBus_h__