/*******************************************************
* Free game engine : SNOW
*
* FileName: Define.h
* Summary: 

* Author: maoyanwen
* Date: 2015/06/05 
*******************************************************/
#ifndef Snow_Define_h__
#define Snow_Define_h__

#ifndef _mars_def_
#define _mars_def_

#include <cassert>
#include <cstring>
#include <string>
#include <map>
#include <algorithm>
#include <list>
#include <vector>
#include <deque>
#include <queue>
#include <stack>
#include <iostream>
#include <functional>
#include <sstream>
#include <set>
#include <string>
#include "Logger.h"

using namespace std;

#include "Enum.h"
#include "TypeDefine.h"
#include "Macros.h"

#endif // _mars_def_



#define	MAX_ROLE_NAME_LEN	(32)

template<typename T, typename P1 = const char*, typename P2 = P1, typename P3 = P1, typename P4 = P1, typename P5 = P1>
struct moudle_helper
{
	moudle_helper(){

	};

	moudle_helper(P1 param1){
		T::SetRequire(param1);
	};

	moudle_helper(P1 param1, P2 param2){
		T::SetRequire(param1);
		T::SetRequire(param2);
	};

	moudle_helper(P1 param1, P2 param2, P3 param3){
		T::SetRequire(param1);
		T::SetRequire(param2);
		T::SetRequire(param3);
	};

	moudle_helper(P1 param1, P2 param2, P3 param3, P4 param4){
		T::SetRequire(param1);
		T::SetRequire(param2);
		T::SetRequire(param3);
		T::SetRequire(param4);
	};

	moudle_helper(P1 param1, P2 param2, P3 param3, P4 param4, P5 param5){
		T::SetRequire(param1);
		T::SetRequire(param2);
		T::SetRequire(param3);
		T::SetRequire(param4);
		T::SetRequire(param5);
	};
};

#endif // Snow_Define_h__
