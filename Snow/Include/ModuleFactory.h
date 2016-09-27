/*******************************************************
* Free game engine : SNOW
*
* FileName: ModuleFactory.h
* Summary: Ä£¿é¹¤³§

* Author: maoyanwen
* Date: 2015/06/27 
*******************************************************/
#ifndef Snow_ModuleFactory_h__
#define Snow_ModuleFactory_h__

#include "Interface/IModule.h"
#include "Singleton.h"

namespace Snow 
{
	typedef Snow::IModule* (*CreateFunc)(const char*);

	class ModuleFactory : public Snow::Singleton<ModuleFactory>
	{
		typedef std_unordered_map<string, CreateFunc> CreateFacFuncT;
	public:
		ModuleFactory();
		void				RegistCreateFunction(const char* clsName, CreateFunc func);
		Snow::IModule*		CreateModule(const char* name);
		bool				Init();
		
	private:
		CreateFacFuncT		m_Methods;
	};
}

#endif // Snow_ModuleFactory_h__