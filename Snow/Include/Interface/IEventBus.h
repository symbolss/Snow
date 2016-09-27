/*******************************************************
* Free game engine : SNOW
*
* FileName: IEventBus.h
* Summary: 消息队列

* Author: maoyanwen
* Date: 2015/06/05 
*******************************************************/
#ifndef Snow_IEventBus_h__
#define Snow_IEventBus_h__

#include "Interface/IEvent.h"
#include "Interface/IComponent.h"

namespace Snow
{
	typedef Result (*fpEventHandler)(Snow::IEvent* pEvent, void* data);
	struct EventHandlerData
	{
		fpEventHandler	handler;
		void*			data;

		EventHandlerData()
		{
			memset(this, 0, sizeof(*this));
		}
	};
	typedef std_unordered_multimap<uint16, EventHandlerData> EventHandler;

	class IEventBus : public IInterface
	{
	public:

		template<class T>
		Result RegisterHandler(Result (*func)(T*, void*), void* data)
		{
			if (!func || !data)
			{
				return R_FAIL;
			}
			fpEventHandler p = reinterpret_cast<fpEventHandler>(func);
			//已经存在
			auto range = m_pHandlers.equal_range(T::m_nEventID);
			for (auto it = range.first; it != range.second; ++it) {
				if (it->second.handler == p)
				{
					return R_OK;
				}
			}

			EventHandlerData handlerdata;
			handlerdata.handler = p;
			handlerdata.data = data;
			m_pHandlers.insert(make_pair(T::m_nEventID, handlerdata));
			return R_OK;
		};

		template<class T>
		Result UnregisterHandler(Result *func(T*, void*))
		{
			fpEventHandler p = reinterpret_cast<fpEventHandler>(func);
			auto range = m_pHandlers.equal_range(T::m_nEventID);
			for (auto it = range.first; it != range.second; ++it) {
				if (it->second.handler == p)
				{
					m_pHandlers.erase(it);
					return R_OK;
				}
			}

			return R_OK
		};

		virtual Result PushEvent(IEvent* pEvent) = 0;

		virtual Result SendEvent(IEvent* pEvent) = 0;

		virtual Result DispatchEvent() = 0;

		virtual Result Tick() = 0;

	protected:
		EventHandler	m_pHandlers;
	};
}

#endif // Snow_IEventBus_h__