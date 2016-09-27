#include "ModuleDatablock.h"

IMP_MODULE(Snow, ModuleDatablock);

bool Snow::ModuleDatablock::Init()
{
#define DATABLOCK_BEGIN			DATABLOCK_BEGIN_RUN
#define DATABLOCK_PARAM			DATABLOCK_PARAM_RUN
#define DATABLOCK_PARAM_STRING	DATABLOCK_PARAM_STRING_RUN
#define DATABLOCK_PARAM_STL_SINGLE		DATABLOCK_PARAM_STL_RUN_SINGLE
#define DATABLOCK_PARAM_USER	DATABLOCK_PARAM_USER_RUN
#define DATABLOCK_END			DATABLOCK_END_RUN

#include "DataBlockInclude.h"

#undef DATABLOCK_BEGIN
#undef DATABLOCK_PARAM
#undef DATABLOCK_PARAM_STRING
#undef DATABLOCK_PARAM_STL_SINGLE
#undef DATABLOCK_PARAM_USER
#undef DATABLOCK_END
	return true;
}

