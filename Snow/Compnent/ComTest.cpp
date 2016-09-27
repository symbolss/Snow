#include "Component/ComTest.h"

Result Snow::ComTest::Init()
{
	
	IEventBus* pEventBus = NULL;
	Result ret = QueryInterface(&pEventBus);
	if (ret != R_OK)
	{
		gErrorStream("Query Interface EventBus Error!");
		return ret;
	}

	pEventBus->RegisterHandler(&(ComTest::TestProcess), this);
	return R_OK;
}

Result Snow::ComTest::TestProcess( EventTest* evt, void* data )
{
	ComTest* p = static_cast<ComTest*>(data);
	return R_OK;
}
