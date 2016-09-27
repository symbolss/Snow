#include "Server.h"
#include "ModuleFactory.h"
#include "ModuleDatablock.h"
#include "ModuleSceneManager.h"

bool Snow::Server::LoadModule( string& name )
{
	if (FindModule(name))
	{
		return true;
	}

	IModule* p = ModuleFactory::Instance()->CreateModule(name.c_str());
	if (!p)
	{
		return false;
	}
	AddModule(p);

	return true;
}

bool Snow::Server::LoadModules()
{
	LOAD_MODULE(ModuleSceneManager);
	LOAD_MODULE(ModuleDatablock);
	return true;
}

bool Snow::Server::Init()
{
	return ModuleFactory::Instance()->Init();
}

