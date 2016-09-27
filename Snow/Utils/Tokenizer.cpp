/************************************************************************
The zlib/libpng License

Copyright (c) 2006 Joerg Wiedenmann

This software is provided 'as-is', without any express or implied warranty.
In no event will the authors be held liable for any damages arising from
the use of this software.

Perquest is granted to anyone to use this software for any purpose,
including commercial applications, and to alter it and redistribute it
freely, subject to the following restrictions:

1. The origin of this software must not be misrepresented;
you must not claim that you wrote the original software.
If you use this software in a product, an acknowledgment
in the product documentation would be appreciated but is
not required.

2. Altered source versions must be plainly marked as such,
and must not be misrepresented as being the original software.

3. This notice may not be removed or altered from any source distribution.

***********************************************************************/

#include "Tokenizer.h"
#include "Utils.h"

namespace mars_utils
{

	void tokenize ( const std::string& str, std::vector<sint64>& result,
		const std::string& delimiters, const std::string& delimiters_preserve,
		const std::string& quote, const std::string& esc )
	{
		std::vector<std::string> vecstr;
		tokenize(str,vecstr,delimiters,delimiters_preserve,quote,esc);

		for (size_t i = 0; i < vecstr.size(); ++i)
		{
			std::string& str = vecstr[i];
			result.push_back(atol(str.c_str()));
		}
	}

	void tokenize ( const std::string& str, std::vector<sint32>& result,
		const std::string& delimiters, const std::string& delimiters_preserve,
		const std::string& quote, const std::string& esc )
	{
		std::vector<std::string> vecstr;
		tokenize(str,vecstr,delimiters,delimiters_preserve,quote,esc);

		for (size_t i = 0; i < vecstr.size(); ++i)
		{
			std::string& str = vecstr[i];
			result.push_back(atoi(str.c_str()));
		}
	}

	void tokenize ( const std::string& str, std::vector<std::string>& result,
				   const std::string& delimiters, const std::string& delimiters_preserve,
				   const std::string& quote, const std::string& esc )
	{
		// clear the std::vector
		if ( false == result.empty() )
		{
			result.clear();
		}

		std::string::size_type pos = 0; // the current position (char) in the std::string
		char ch = 0; // buffer for the current character
		char delimiter = 0;    // the buffer for the delimiter char which
								// will be added to the tokens if the delimiter
								// is preserved
		char current_quote = 0; // the char of the current open quote
		bool quoted = false; // indicator if there is an open quote
		std::string token;  // std::string buffer for the token
		bool token_complete = false; // indicates if the current token is
									 // read to be added to the result std::vector
		std::string::size_type len = str.length();  // length of the input-std::string

		// for every char in the input-std::string
		while ( len > pos )
		{
			// get the character of the std::string and reset the delimiter buffer
			ch = str.at(pos);
			delimiter = 0;

			// assume ch isn't a delimiter
			bool add_char = true;

			// check ...

			// ... if the delimiter is an escaped character
			bool escaped = false; // indicates if the next char is protected
			if ( false == esc.empty() ) // check if esc-chars are  provided
			{
				if ( std::string::npos != esc.find_first_of(ch) )
				{
					// get the escaped char
					++pos;
					if ( pos < len ) // if there are more chars left
					{
						// get the next one
						ch = str.at(pos);

						// add the escaped character to the token
						add_char = true;
					}
					else // cannot get any more characters
					{
						// don't add the esc-char
						add_char = false;
					}

					// ignore the remaining delimiter checks
					escaped = true;
				}
			}

			// ... if the delimiter is a quote
			if ( false == quote.empty() && false == escaped )
			{
				// if quote chars are provided and the char isn't protected
				if ( std::string::npos != quote.find_first_of(ch) )
				{
					// if not quoted, set state to open quote and set
					// the quote character
					if ( false == quoted )
					{
						quoted = true;
						current_quote = ch;

						// don't add the quote-char to the token
						add_char = false;
					}
					else // if quote is open already
					{
						// check if it is the matching character to close it
						if ( current_quote == ch )
						{
							if(token.length() == 0)
								token.push_back('\0');

							// close quote and reset the quote character
							quoted = false;
							current_quote = 0;

							// don't add the quote-char to the token
							add_char = false;
						}
					} // else
				}
			}

			// ... if the delimiter isn't preserved
			if ( false == delimiters.empty() && false == escaped &&
				 false == quoted )
			{
				// if a delimiter is provided and the char isn't protected by
				// quote or escape char
				if ( std::string::npos != delimiters.find_first_of(ch) )
				{
					// if ch is a delimiter and the token std::string isn't empty
					// the token is complete
					if ( false == token.empty() ) // BUGFIX: 2006-03-04
					{
						token_complete = true;
					}

					// don't add the delimiter to the token
					add_char = false;
				}
			}

			// ... if the delimiter is preserved - add it as a token
			bool add_delimiter = false;
			if ( false == delimiters_preserve.empty() && false == escaped &&
				 false == quoted )
			{
				// if a delimiter which will be preserved is provided and the
				// char isn't protected by quote or escape char
				if ( std::string::npos != delimiters_preserve.find_first_of(ch) )
				{
					// if ch is a delimiter and the token std::string isn't empty
					// the token is complete
					if ( false == token.empty() ) // BUGFIX: 2006-03-04
					{
						token_complete = true;
					}

					// don't add the delimiter to the token
					add_char = false;

					// add the delimiter
					delimiter = ch;
					add_delimiter = true;
				}
			}


			// add the character to the token
			if ( true == add_char )
			{
				// add the current char
				token.push_back( ch );
			}

			// add the token if it is complete
			if ( true == token_complete && false == token.empty() )
			{
				// add the token std::string
				result.push_back( token );

				// clear the contents
				token.clear();

				// build the next token
				token_complete = false;
			}

			// add the delimiter
			if ( true == add_delimiter )
			{
				// the next token is the delimiter
				std::string delim_token;
				delim_token.push_back( delimiter );
				result.push_back( delim_token );

				// REMOVED: 2006-03-04, Bugfix
			}

			// repeat for the next character
			++pos;
		} // while

		// add the final token
		if ( false == token.empty() )
		{
			result.push_back( token );
		}
	}
}
