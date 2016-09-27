/*******************************************************
* Free game engine : SNOW
*
* FileName: TypeDefine.h
* Summary: Type Define

* Author: maoyanwen
* Date: 2015/06/05 
*******************************************************/
#ifndef Snow_TypeDefine_h__
#define Snow_TypeDefine_h__

#include <unordered_map>
#include <unordered_set>

#ifdef _MSC_VER
#pragma warning(disable:4996)
#pragma warning(disable:4800)
#pragma warning(disable:4006)
#pragma warning(disable:4200)
#pragma warning(disable:4819)

#include <float.h>
#undef std_unordered_map
#undef std_unordered_set
#define std_unordered_map std::tr1::unordered_map
#define std_unordered_set std::tr1::unordered_set
#define std_unordered_multimap std::tr1::unordered_multimap

#define isnanf(x) (_isnan(x))
#define isinff(x) (_finite(x) == 0)

typedef signed char sint8;
typedef unsigned char uint8;
typedef signed short sint16;
typedef unsigned short uint16;
typedef __int32 sint32;
typedef unsigned __int32 uint32;
typedef __int64 sint64;
typedef unsigned __int64 uint64;
#else
#include <math.h>

#define std_unordered_map std::unordered_map
#define std_unordered_set std::unordered_set
#define std_unordered_multimap std::unordered_multimap

#define _countof(x) (sizeof(x)/sizeof(x[0]))

typedef signed char sint8;
typedef unsigned char uint8;
typedef signed short sint16;
typedef unsigned short uint16;
typedef int32_t sint32;
typedef uint32_t uint32;
typedef long long sint64;
typedef unsigned long long uint64;


#define __max(a,b)  (((a) > (b)) ? (a) : (b))
#define __min(a,b)  (((a) < (b)) ? (a) : (b))

#endif
using namespace std;

typedef sint32 Result;


#endif // Snow_TypeDefine_h__