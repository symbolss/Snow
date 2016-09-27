#include "EventDefine.h"
//实现部分
#define EVENT_BEGIN			EVENT_BEGIN_IMP
#define EVENT_PARAM			EVENT_PARAM_IMP
#define EVENT_END			EVENT_END_IMP

#include "EventInclude.h"

#undef EVENT_BEGIN
#undef EVENT_PARAM
#undef EVENT_END

//uint16 EventTest::m_nEventID = 222;	
			