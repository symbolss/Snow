#include "Interface/IEvent.h"

//���岿��
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
//	   sint32 id;				//����ID
//	   sint32 itemSpecies;	//��Ʒ����
//};
