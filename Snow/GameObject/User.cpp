#include "GameObject/User.h"
#include "Component/ComEventBus.h"
#include "Component/ComTest.h"

Result Snow::User::InitComponents()
{
	CREATE_COMPONENT(ComEventBus);
	CREATE_COMPONENT(ComTest);
	return R_OK;
}

Result Snow::User::Init()
{
	Result ret = IGameObject::Init();
	if (ret != R_OK)
	{
		return ret;
	}

	return R_OK;
}


