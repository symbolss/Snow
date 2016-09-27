/*******************************************************
* Copyright (c) 2014, QingYun All rights reserved.
* 
* FileName: ConsoleColor.h
* Summary: 

* Author: liuyudong
* Date: 2014/10/16 11:33
*******************************************************/
#ifndef __ConsoleColor_h__
#define __ConsoleColor_h__

#include <iostream>
namespace mars_utils
{
	extern  std::ostream& white(std::ostream& s);
	extern  std::ostream& blue(std::ostream& s);
	extern  std::ostream& red(std::ostream& s);
	extern  std::ostream& green(std::ostream& s);
	extern  std::ostream& yellow(std::ostream& s);
}
#endif	// __ConsoleColor_h__
