#include "SnowServer.h"
#include "Interface/IModule.h"
#include "ModuleDatablock.h"
#include "ModuleEventBus.h"
#include "EventDefine.h"
#include "GameObject/User.h"
#include "Interface/IEventBus.h"

#include <stdlib.h>

int main()
{
	SnowServer::Instance()->Init();
	SnowServer::Instance()->LoadModules();

	sint64 aaa = mars_utils::Convertor<const char*, sint64>("3534523234423");

	Snow::ModuleDatablock* p = SnowServer::Instance()->GetModule<Snow::ModuleDatablock>();
	if (p)
	{
		TableItem* pItem = p->GetTableItem().GetDataById(1);
		int a = 0;
	}

	EventTest test;
	test.id = 100;

	Snow::User u;
	u.Init();

	Snow::IEventBus* pBus = NULL;
	if (u.QueryInterface(&pBus) != R_OK)
	{
		return -1;
	}
	pBus->PushEvent(&test);
	pBus->SendEvent(&test);


	Snow::ModuleEventBus* pEventBus = SnowServer::Instance()->GetModule<Snow::ModuleEventBus>();
	if (pEventBus)
	{
		pEventBus->SendEvent(&test);
	}

	return 0;

}
