/*******************************************************
* Copyright (c) 2014, QingYun All rights reserved.
* 
* FileName: Utils.h
* Summary: 

* Author: fengqk
* Date: 2014/06/15  19:47
*******************************************************/

#ifndef _mars_utils_
#define _mars_utils_

#include "Define.h"

namespace mars_utils
{
	#define TEN_THOUSAND (10000)
	template<class Container>
	void set_diff(Container& set,const Container& del,Container& out)
	{
		for(typename Container::iterator iter = set.begin(); iter != set.end(); ++iter)
		{
			if(::std::find(del.begin(),del.end(),*iter) == del.end())
				out.push_back(*iter);
		}
	}

	extern int		strcmp(const char* str1,const char* str2);
	extern int		stricmp(const char* str1,const char* str2);
	extern sint32 	atoi(const char* str);
	extern sint64 	atoi(const char* str,int base);
	extern sint64	atol(const char* str);
	extern double 	atof(const char* str);
	extern void 	itoa(char* str,sint64 val);
	extern void 	ftoa(char* str,double val);
	extern char* 	mystrncpy(char* dst,const char* src,size_t len);
	extern char*	strncat(char* dest,const char* src,size_t destlen);
	extern int		floatcmp(double value1,double value2);
	extern sint64	random();
	extern int 		random(int start,int end);
	extern double 	random(double start,double end);
	extern bool		isbetween(double start,double end,double value);
	extern double	clamp(double ho,double lo,double value);
	extern int		clamp(int ho,int lo,int value);
	extern double   frand();
	extern void		ltob(sint64 val, sint8* abytes, size_t size);
	extern sint64	btol(sint8* abytes, size_t size);
	extern void		fixpath(std::string &path);
	extern bool		isdirectory(std::string path);
	extern bool		create_recurdir(std::string path);

	template<class T>
	std::string		tostring(const T& data)
	{
		std::stringstream ss;
		ss << data;
		return ss.str();
	}

	template<class T1,class T2>
	T2 Convertor(T1 inparam)
	{
		stringstream s(inparam);
		T2 ouparam;
		s >> ouparam;
		return ouparam;
	}

	extern bool		checkName(const char* szName);
	extern bool		illegal_char(char c);
	extern bool		has_illegal_char(unsigned char* str, int len);
	extern int		replaceStr(char *sSrc, char *sMatchStr, char *sReplaceStr);
	extern void		replaceChar(char *str, char m, char r);
	extern int		match(const char *regexp, const char* text);
}

#endif //_mars_utils_
