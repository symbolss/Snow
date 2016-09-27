/*******************************************************
* Free game engine : SNOW
*
* FileName: EventBus.h
* Summary: EventBus

* Author: maoyanwen
* Date: 2015/06/05 
*******************************************************/
#ifndef Snow_EventBus_h__
#define Snow_EventBus_h__
#include "Define.h"
#include "Interface/IEvent.h"
#include "Interface/IComponent.h"
#include "Interface/IEventBus.h"
namespace Snow
{
	class EventBus : public IEventBus
	{
	public:
		Result PushEvent(Snow::IEvent* pEvent);

		Result SendEvent(Snow::IEvent* pEvent);

		Result DispatchEvent();

		Result Tick();
	};

	
}

#endif // Snow_EventBus_h__