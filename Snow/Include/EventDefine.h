#include "Interface/IEvent.h"

//定义部分
#define EVENT_BEGIN			EVENT_BEGIN_DEFINE
#define EVENT_PARAM			EVENT_PARAM_DEFINE
#define EVENT_END			EVENT_END_DEFINE

#include "EventInclude.h"

#undef EVENT_BEGIN
#undef EVENT_PARAM
#undef EVENT_END



//class EventTest : public Snow::IEvent
//{
//public:	
//	static uint16 GetEventID(){	return m_nEventID;	}
//private:
//	static uint16 m_nEventID;
//public:
//	   sint32 id;				//道具ID
//	   sint32 itemSpecies;	//物品种类
//};
