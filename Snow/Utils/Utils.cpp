/*******************************************************
* Copyright (c) 2014, QingYun All rights reserved.
* 
* FileName: Utils.cpp
* Summary: 

* Author: fengqk
* Date: 2014/06/15  19:51
*******************************************************/

#include "Utils.h"
#include "Random.h"
#include "Define.h"

#ifdef _MSC_VER
	#include <string.h>
#else
	#include <cstring>
#endif

#ifdef WIN32
#include <io.h>
#include <shlwapi.h>
#pragma comment(lib, "shlwapi")
#else
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <dirent.h>
#include <fcntl.h>
#endif

namespace mars_utils
{
	int strcmp(const char* str1,const char* str2)
	{
		return ::strcmp(str1,str2);
	}

	int stricmp(const char* str1,const char* str2)
	{
#ifdef _MSC_VER
		return ::_stricmp(str1,str2);	
#else
		return ::strcasecmp(str1,str2);
#endif
	}

	sint64 atoi(const char* str,int base)
	{
		if(str == NULL)
			return 0LL;
#ifdef _MSC_VER
		return (sint64)::_strtoi64(str,NULL,base);
#else
		return (sint64)::strtoll(str,NULL,base);
#endif
	}

	sint32 atoi(const char* str)
	{
		if(str == NULL)
			return 0;

#ifdef _MSC_VER
		return (sint32)_atoi64(str);
#else
		return (sint32)::atoll(str);
#endif
	}

	double atof(const char* str)
	{
		if(str == NULL)
			return 0.f;

		return ::atof(str);
	}

	void itoa(char* str,sint64 val)
	{
		std::stringstream ss;
		ss << val;
		::strcpy(str,ss.str().c_str());
	}

	void ftoa(char* str,double val)
	{
		std::stringstream ss;
		ss << val;
		::strcpy(str,ss.str().c_str());
	}

	char* mystrncpy(char* dst,const char* src,size_t len)
	{
		mars_assertr(dst && src && len >= 1, NULL);

#ifdef _MSC_VER
		char* ret = ::strncpy(dst,src,len);
		dst[len - 1] = '\0';
		return ret;
#else
		char* ret = ::strncpy(dst,src,len);
		dst[len - 1] = '\0';
		return ret;
#endif
	}

	char* strncat( char* dest,const char* src,size_t destlen )
	{
		return ::strncat(dest,src,destlen);
	}

	int floatcmp(double value1,double value2)
	{
		const double fEpsilon = 0.01f;
		double fDelta = fabs(value1-value2);

		if (fDelta > fEpsilon)
			return 1;
		else
			return 0;
	}

	sint64 random()
	{
		return g_objRandomGenerator.Gen();
	}

	int random(int start,int end)
	{
		if(start == end)
			return start;
		unsigned int r = random() % 0xffffffff;
		return (r % abs(end - start)) + start;
	}

	double random(double start,double end)
	{
		unsigned int r = random() % 0xffffffff;
		double d = (double)r / (double)0xffffffff;
		return (double)(start + fabs(end - start) * d);
	}

	bool isbetween( double start,double end,double value )
	{
		if(start > end)
			std::swap(start,end);
		return value >= start && value <= end;
	}

	double clamp( double ho,double lo,double value )
	{
		if(value < lo)
			return lo;
		else if(value >= ho)
			return ho;
		return value;
	}

	int clamp( int ho,int lo,int value )
	{
		if(value < lo)
			return lo;
		else if(value >= ho)
			return ho;
		return value;
	}

	double frand()
	{
		return (double)::rand() / ((double)RAND_MAX);
	}

	extern sint64 atol( const char* str )
	{
		if(str == NULL)
			return 0;

#ifdef _MSC_VER
		return (sint64)_atoi64(str);
#else
		return (sint64)::atoll(str);
#endif
	}

	bool illegal_char(char c)
	{
		if( (c >= 48 && c <=57) //数字
			|| (c >= 65 && c <= 90)  //大写字母
			|| (c >= 97 && c <= 122)) //小写字母
			return false;
		return true;
	}

	bool has_illegal_char(unsigned char* str, int len)
	{
		int i = -1, k = 1;
		while(i < len)
		{
			i += k;
			if(str[i] == '\0')
				break;

			if(str[i] < 0x80) // ascii 0-127位字符
			{
				if (illegal_char(str[i]))
					return true;
				k = 1; // 0-127位占一字节
			}
			else if(str[i] < 0xE0)
			{
				//return true;
				k = 2;
			}
			else if(str[i] < 0xF0)
			{
				if(str[i] < 0xE4)//查表去
					return true;
				k = 3;
			}
			else
			{
				//unsigned short a = (str[i] | 0x7);
				//unsigned short b = (str[i+1] | 0x3F);
				//unsigned short c = (str[i+2] | 0x3F);
				//unsigned short d = (str[i+3] | 0x3F);
				if(str[i] > 0xF0 || str[i+1] > 0x89)//要改就改吧
					return true;
				if(str[i+1] == 0x89) {
					if(str[i+2] > 0xBE)
						return true;
					if(str[i+2] == 0xBE) {
						if(str[i+3] > 0xA5)
							return true;
					}
				}
				k = 4;
			}
		}
		return false;
	}

	extern bool checkName( const char* szName )
	{
		int len = strlen(szName) ;
		if (len > MAX_ROLE_NAME_LEN)
		{
			return true;
		}
		unsigned char str[MAX_ROLE_NAME_LEN] = {0};
		for (int i = 0; i < len; ++i)
		{
			str[i] = (unsigned char)*(szName+i);
		}
		return 	has_illegal_char(str, len);
	}

	void ltob( sint64 val, sint8* abytes, size_t size )
	{
		mars_assert(size == 8);

		abytes[0] = (sint8) (0xFF & (val >> 56));
		abytes[1] = (sint8) (0xFF & (val >> 48));
		abytes[2] = (sint8) (0xFF & (val >> 40));
		abytes[3] = (sint8) (0xFF & (val >> 32));
		abytes[4] = (sint8) (0xFF & (val >> 24));
		abytes[5] = (sint8) (0xFF & (val >> 16));
		abytes[6] = (sint8) (0xFF & (val >> 8));
		abytes[7] = (sint8) (0xFF & (val >> 0));
	}

	sint64 btol( sint8* abytes, size_t size )
	{
		mars_assertr(size == 8, 0LL);

		sint64 val = 0;
		val |= (sint64)(abytes[0]) << 56;
		val |= (sint64)(abytes[1]) << 48;
		val |= (sint64)(abytes[2]) << 40;
		val |= (sint64)(abytes[3]) << 32;
		val |= (sint64)(abytes[4]) << 24;
		val |= (sint64)(abytes[5]) << 16;
		val |= (sint64)(abytes[6]) << 8;
		val |= (sint64)(abytes[7]) << 0;
		return val;
	}

	extern void fixpath( std::string &path )
	{
		if (path.empty())
		{
			return;
		}
		for (std::string::iterator iter = path.begin(); iter != path.end(); ++iter)
		{
			if (*iter == '\\')
			{
				*iter = '/';
			}
		}
		if (path.at(path.length()-1) != '/')
		{
			path.append("/");
		}
	}

	extern bool isdirectory( std::string path )
	{
#ifdef WIN32
		return PathIsDirectoryA(path.c_str()) ? true : false;
#else
		DIR * pdir = opendir(path.c_str());
		if (pdir == NULL)
		{
			return false;
		}
		else
		{
			closedir(pdir);
			pdir = NULL;
			return true;
		}
#endif
	}

	extern bool create_recurdir( std::string path )
	{
		if (path.length() == 0) return true;
		fixpath(path);

		std::string::size_type pos = path.find('/');
		while (pos != std::string::npos)
		{
			std::string cur = path.substr(0, pos-0);
			if (cur.length() > 0 && !isdirectory(cur))
			{
				bool ret = false;
#ifdef WIN32
				ret = CreateDirectoryA(cur.c_str(), NULL) ? true : false;
#else
				ret = (mkdir(cur.c_str(), S_IRWXU|S_IRWXG|S_IRWXO) == 0);
#endif
				if (!ret)
				{
					return false;
				}
			}
			pos = path.find('/', pos+1);
		}

		return true;
	}

	// 替换字符串中特征字符串为指定字符串
	int replaceStr(char *sSrc, char *sMatchStr, char *sReplaceStr)
	{
		int  StringLen;
		char caNewString[1024];

		char *FindPos = strstr(sSrc, sMatchStr);
		if( (!FindPos) || (!sMatchStr) )
			return -1;

		while( FindPos )
		{
			memset(caNewString, 0, sizeof(caNewString));
			StringLen = FindPos - sSrc;
			mars_utils::mystrncpy(caNewString, sSrc, StringLen);
			strcat(caNewString, sReplaceStr);
			strcat(caNewString, FindPos + strlen(sMatchStr));
			strcpy(sSrc, caNewString);

			FindPos = strstr(sSrc, sMatchStr);
		}

		return 0;
	}

	void replaceChar(char *str, char m, char r)
	{
		if (NULL == str)
		{
			return;
		}
		char* p = str;
		while (*p != '\0')
		{
			if (*p == m)
			{
				*p= r;
			}
			p ++;
		}
	}

	static int matchhere(const char *regexp, const char *text);

	static int matchstar(int c, const char *regexp, const char *text) {// matchstar: search for c*regexp at beginning of text
		do {// a * matches zero or more instances
			if (matchhere(regexp, text)) return 1;
		} while (*text != '\0' && (*text++ == c || c == '.'));
		return 0;
	}
	static int matchhere(const char *regexp, const char *text) {// matchhere: search for regexp at beginning of text
		if (regexp[0] == '\0') return 1;
		if (regexp[1] == '*') return matchstar(regexp[0], regexp+2, text);
		if (regexp[0] == '$' && regexp[1] == '\0') return *text == '\0';
		if (*text!='\0' && (regexp[0]=='.' || regexp[0]==*text)) return matchhere(regexp+1, text+1);
		return 0;
	}

	int match(const char *regexp, const char *text) {// match: search for regexp anywhere in text
		if (regexp[0] == '^') return matchhere(regexp+1, text);
		do {// must look even if string is empty
			if (matchhere(regexp, text)) return 1;
		} while (*text++ != '\0');
		return 0;
	}

}
