/*******************************************************
* Free game engine : SNOW
*
* FileName: ModuleEventBus.h
* Summary: 事件队列组件

* Author: maoyanwen
* Date: 2015/08/27 
*******************************************************/
#ifndef Snow_ModuleEventBus_h__
#define Snow_ModuleEventBus_h__
#include "Interface/IModule.h"
#include "EventBus.h"
namespace Snow
{
	class ModuleEventBus : public EventBus, public IModule
	{
	public:
		DECLARE_MODULE(ModuleEventBus);

		virtual bool Init();
	};
}

#endif // Snow_ModuleEventBus_h__
