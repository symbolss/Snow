/*******************************************************
* Free game engine : SNOW
*
* FileName: IEvent.h
* Summary: Event

* Author: maoyanwen
* Date: 2015/06/05 
*******************************************************/
#ifndef Snow_IEvent_h__
#define Snow_IEvent_h__

#include "Interface/IInterface.h"

namespace Snow
{
	struct IEvent : public IInterface
	{
		virtual uint16 GetEventID() = 0;
	};
}

#endif // Snow_IEvent_h__