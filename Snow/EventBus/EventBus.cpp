#include "EventBus.h"


Result Snow::EventBus::PushEvent( Snow::IEvent* pEvent )
{
	sint32 nSize = sizeof(*pEvent);
	void* p = (void*)malloc(nSize);
	memcpy(p, pEvent, nSize);

	IEvent* pE = (IEvent*)p;
	return R_OK;
}

Result Snow::EventBus::SendEvent( Snow::IEvent* pEvent )
{
	auto range = m_pHandlers.equal_range(pEvent->GetEventID());
	for (auto it = range.first; it != range.second; ++it) {
		if (it->second.handler)
		{
			(it->second.handler)(pEvent, it->second.data);
		}
	}	
	return R_OK;
}

Result Snow::EventBus::DispatchEvent()
{
	return R_OK;
}

Result Snow::EventBus::Tick()
{
	return R_OK;
}
