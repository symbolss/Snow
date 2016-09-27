#include "DataBlockHelper.h"
#include "DataBlockDefine.h"
#include "Define.h"
#include "Tokenizer.h"
#include "XmlParser.h"
#include "Utils.h"
uint32 DataBlockHelper::_ConvertStringToVector( const char* strStrINTgSource, vector< std::string >& vRet, const char* szKey, bool bOneOfKey, bool bIgnoreEmpty )
{
	vRet.clear();

	std::string strSrc = strStrINTgSource;
	if(strSrc.empty())
	{
		return 0;
	}

	std::string::size_type nLeft = 0;
	std::string::size_type nRight;
	if(bOneOfKey)
	{
		nRight = strSrc.find_first_of(szKey);
	}
	else
	{
		nRight = strSrc.find(szKey);
	}

	if(nRight == std::string::npos)
	{
		nRight = strSrc.length();
	}

	std::string strItem;
	while(1)
	{
		if (nRight > nLeft || !bIgnoreEmpty)
		{
			strItem = strSrc.substr(nLeft, nRight-nLeft);
			vRet.push_back(strItem);
		}

		if(nRight == strSrc.length())
		{
			break;
		}

		nLeft = nRight + (bOneOfKey ? 1 : strlen(szKey));

		if(bOneOfKey)
		{
			nRight = strSrc.find_first_of(szKey, nLeft);
		}
		else
		{
			nRight = strSrc.find(szKey, nLeft);
		}

		if(nRight == std::string::npos)
		{
			nRight = strSrc.length();
		}
	}
	return (uint32)vRet.size();
}

const char* DataBlockHelper::_GetLineFromMemory( char* pStringBuf, sint32 nBufSize, const char* pMemory, const char* pDeadEnd )
{
	//寻找下一个换行符
	register const char* pMem = pMemory;
	if(pMem >= pDeadEnd || *pMem==0) return 0;

	while(pMem < pDeadEnd && pMem - pMemory + 1 < nBufSize && 
		*pMem != 0 && *pMem != '\r' && *pMem != '\n') *(pStringBuf++) = *(pMem++);
	//add 'null' end
	*pStringBuf = 0;

	//skip all next \r and \n
	while(pMem < pDeadEnd && *pMem != 0 && (*pMem=='\r' || *pMem=='\n')) pMem++;

	return pMem;
}

bool DataBlockHelper::ParseHead()
{
	//----------------------------------------------------
	//分析列数和类型
	vector< char > vLineBuf;
	vLineBuf.resize(MAX_LINE_BYTES, 0);	
	char* szLine = &(vLineBuf[0]);

	//读第一行,解析字段名
	pMemory = const_cast<char*>(_GetLineFromMemory(szLine, MAX_LINE_BYTES, pMemory, pEnd));
	if(NULL == pMemory) return false;
	_ConvertStringToVector(szLine, vTitle, "\t", true, true);
	if(vTitle.empty()) return false;

	//建立字段类型列表
	vector<std::string> tmp;
	pMemory = const_cast<char*>(_GetLineFromMemory(szLine, MAX_LINE_BYTES, pMemory, pEnd));
	if(NULL == pMemory) return false;
	_ConvertStringToVector(szLine, tmp, "\t", true, true);
	if(tmp.empty()) return false;
	if (vTitle.size() != tmp.size())
	{
		return false;
	}
	uint32 nFieldsNum = vTitle.size();
	vFieldsType.resize(nFieldsNum);
	for(uint32 i = 0; i<nFieldsNum; i++) 
	{
		transform(tmp[i].begin(), tmp[i].end(), tmp[i].begin(), ::toupper);
		if(tmp[i] == string("INT"))
		{
			vFieldsType[i] = Field_Type::T_INT;
		}
		else if((tmp[i] ==  string("FLOAT")) || (tmp[i] ==  string("DOUBLE")))
		{
			vFieldsType[i] = Field_Type::T_FLOAT;
		}
		else if(tmp[i] ==  string("STRING")) 
		{
			vFieldsType[i] = Field_Type::T_STRING;
		}
		else if((tmp[i] ==  string("BOOL")) || (tmp[i] ==  string("BOOLEAN"))) 
		{
			vFieldsType[i] = Field_Type::T_BOOL;
		}
		else
		{
			return false;
		}
	}

	//读出注释行,按照这个方式是从第四行开始就是数据，如果有变化可以在此处修改
	pMemory = const_cast<char*>(_GetLineFromMemory(szLine, MAX_LINE_BYTES, pMemory, pEnd));
	if(NULL == pMemory) 
	{
		gErrorStream("Table file with out any content.");
		return false;
	}
	return true;
}

bool DataBlockHelper::OpenFile(const char* filename )
{
	FILE* fp = fopen(filename, "rb");
	if(NULL == fp) return false;

	fseek(fp, 0, SEEK_END);
	uint32 nFileSize = ftell(fp);
	fseek(fp, 0, SEEK_SET);

	//读入内存
	if (!(pBuffer = new char[nFileSize+1]))
	{
		fclose(fp);
		return false;
	}
	pMemory = pBuffer;
	pEnd = pMemory+nFileSize+1;
	fread(pMemory, 1, nFileSize, fp);
	pMemory[nFileSize] = 0;
	fclose(fp); fp=0;
	return true;
}

bool DataBlockHelper::TypeMatch(const char* file_type, Field_Type table_type )
{
	if (!file_type)
	{
		return false;
	}
	std::string tmp(file_type);
	transform(tmp.begin(), tmp.end(), tmp.begin(), ::tolower);
	switch(table_type)
	{
	case T_INT:
		if (tmp.find_first_of(string("int")) != string::npos)
		{
			return true;
		}
		break;
	case T_FLOAT:
		if (tmp.find_first_of(string("float")) != string::npos)
		{
			return true;
		}
		break;
	case T_STRING:
		if (tmp.find_first_of(string("string")) != string::npos || tmp.find_first_of(string("char")) == string::npos)
		{
			return true;
		}
		break;
	case T_BOOL:
		if (tmp.find_first_of(string("bool")) != string::npos)
		{
			return true;
		}
		break;
	default:
		return false;
	}
	return false;
}

void DataBlockHelper::Clear()
{
	if (pBuffer)
	{
		delete[] pBuffer;
	}
	pMemory = NULL;
	pBuffer = NULL;
	pEnd = NULL;
	vTitle.clear();
	vFieldsType.clear();
}

bool DataBlockHelper::DefaultCallBack( void* record )
{
	return true;
}
