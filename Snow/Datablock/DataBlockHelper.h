
#ifndef __DATABLOCK_HELPER_H_
#define __DATABLOCK_HELPER_H_
#include "Utils.h"
#include "Singleton.h"
#include "Define.h"
#include <stdlib.h>

#define MAX_LINE_BYTES (1024*64)

class DataBlockHelper : public Snow::Singleton<DataBlockHelper>
{
public:
	DataBlockHelper():pMemory(NULL),pBuffer(NULL),pEnd(NULL){};

	bool OpenFile(const char* filename);
	bool ParseHead();
	const char* _GetLineFromMemory(char* pStringBuf, sint32 nBufSize, const char* pMemory, const char* pDeadEnd);
	uint32 _ConvertStringToVector(const char* strStrINTgSource, vector< std::string >& vRet, const char* szKey, bool bOneOfKey, bool bIgnoreEmpty);
	bool TypeMatch(const char* file_type, Field_Type table_type );
	void Clear();

	char* pMemory;
	char* pBuffer;
	char* pEnd;
	vector< string > vTitle;
	vector< Field_Type > vFieldsType;

public:
	static bool DefaultCallBack(void* record);
};
#endif