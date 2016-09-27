/*******************************************************
* Free game engine : SNOW
*
* FileName: Server.h
* Summary: Server

* Author: maoyanwen
* Date: 2015/06/29 
*******************************************************/
#ifndef Snow_Server_h__
#define Snow_Server_h__

#include "Interface/IModuleHost.h"
#include "Singleton.h"

namespace Snow
{
	class Server : public Singleton<Server>, public IModuleHost
	{
	public:
		virtual bool	LoadModule(string& name);
		bool			LoadModules();
		bool			Init();
	};
}

#endif // Snow_Server_h__