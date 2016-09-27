#include "ModuleFactory.h"
#include "ModuleDatablock.h"
#include "ModuleSceneManager.h"
#include "ModuleEventBus.h"

void Snow::ModuleFactory::RegistCreateFunction( const char* clsName, CreateFunc func )
{
	m_Methods.insert(make_pair(clsName, func));
}

Snow::ModuleFactory::ModuleFactory()
{
	
}


Snow::IModule* Snow::ModuleFactory::CreateModule( const char* name )
{
	CreateFacFuncT::iterator it = m_Methods.find(name);
	if (it != m_Methods.end())
	{
		CreateFunc func = it->second;
		Snow::IModule* p = func(name);
		if (p)
		{
			p->Init();
		}
		return p;
	}
	return NULL;
}

bool Snow::ModuleFactory::Init()
{
	REGIST_MODULE(ModuleDatablock);
	REGIST_MODULE(ModuleSceneManager,"ModuleEventBus","ModuleDatablock");
	REGIST_MODULE(ModuleEventBus);
	return true;
}


