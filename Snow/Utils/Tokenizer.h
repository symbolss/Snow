/*******************************************************
* Copyright (c) 2014, QingYun All rights reserved.
* 
* FileName: Tokenizer.h
* Summary: 

* Author: fengqk
* Date: 2014/06/15  19:47
*******************************************************/

#ifndef _mars_tokenizer_
#define _mars_tokenizer_

#include "Define.h"

namespace mars_utils
{
	void tokenize ( const std::string& str, std::vector<sint64>& result,
		const std::string& delimiters, const std::string& delimiters_preserve = "",
		const std::string& quote = "\"", const std::string& esc = "\\" );

	void tokenize ( const std::string& str, std::vector<sint32>& result,
		const std::string& delimiters, const std::string& delimiters_preserve = "",
		const std::string& quote = "\"", const std::string& esc = "\\" );

	void tokenize ( const std::string& str, std::vector<std::string>& result,
		const std::string& delimiters, const std::string& delimiters_preserve = "",
		const std::string& quote = "\"", const std::string& esc = "\\" );
}

#endif //_mars_tokenizer_
