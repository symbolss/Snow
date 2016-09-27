/*******************************************************
* Copyright (c) 2014, QingYun All rights reserved.
* 
* FileName: Random.h
* Summary: 

* Author: fengqk
* Date: 2014/06/15  19:46
*******************************************************/

#ifndef _mars_random_
#define _mars_random_

#ifdef _MSC_VER
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <windows.h>
#include <wincrypt.h>
#endif

#include "Define.h"

namespace mars_utils
{
#ifdef _MSC_VER
	class RandomGenerator
	{
	public:
		RandomGenerator();
		~RandomGenerator();
	public:
		sint64 Gen();
	private:
		HCRYPTPROV m_hProv;
	};
#else
	class RandomGenerator
	{
	public:
		RandomGenerator();
		~RandomGenerator();
	public:
		sint64 Gen();
	private:
		FILE* m_pFile;
	};
#endif

	extern RandomGenerator g_objRandomGenerator;
}

#endif //_mars_random_
