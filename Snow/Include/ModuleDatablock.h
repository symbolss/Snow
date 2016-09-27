/*******************************************************
* Free game engine : SNOW
*
* FileName: ModuleDatablock.h
* Summary: 数据配表模块

* Author: maoyanwen
* Date: 2015/06/27 
*******************************************************/
#ifndef Snow_ModuleDatablock_h__
#define Snow_ModuleDatablock_h__

#include "Interface/IModule.h"
#include "DataBlockDefine.h"

namespace Snow
{
	class ModuleDatablock : public Snow::IModule
	{
		DECLARE_MODULE(ModuleDatablock);

		virtual bool Init();

#define DATABLOCK_BEGIN			DATABLOCK_BEGIN_MOUDLE_DEFINE
#define DATABLOCK_PARAM			DATABLOCK_PARAM_MOUDLE_DEFINE
#define DATABLOCK_PARAM_STRING	DATABLOCK_PARAM_STRING_MOUDLE_DEFINE
#define DATABLOCK_PARAM_STL_SINGLE		DATABLOCK_PARAM_STL_SINGLE_MOUDLE_DEFINE
#define DATABLOCK_PARAM_USER	DATABLOCK_PARAM_USER_MOUDLE_DEFINE
#define DATABLOCK_END			DATABLOCK_END_MOUDLE_DEFINE

#include "DataBlockInclude.h"

#undef DATABLOCK_BEGIN
#undef DATABLOCK_PARAM
#undef DATABLOCK_PARAM_STRING
#undef DATABLOCK_PARAM_STL_SINGLE
#undef DATABLOCK_PARAM_USER
#undef DATABLOCK_END

	};
}

#endif // Snow_ModuleDatablock_h__