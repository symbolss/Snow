/*******************************************************
* Free game engine : SNOW
*
* FileName: ModuleSceneManager.h
* Summary: ≥°æ∞π‹¿Ì∆˜

* Author: maoyanwen
* Date: 2015/08/05 
*******************************************************/
#ifndef Snow_ModuleSceneManager_h__
#define Snow_ModuleSceneManager_h__
#include "Interface/IModule.h"
namespace Snow
{
	class ModuleSceneManager : public Snow::IModule
	{
		DECLARE_MODULE(ModuleSceneManager);

		virtual bool Init();
	};
}

#endif // Snow_ModuleSceneManager_h__
