#include "ConsoleColor.h"

namespace mars_utils
{
#ifdef WIN32
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <windows.h>
	static void  SetConsoleColor(WORD wAttribute)
	{
		HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(handle, wAttribute);
	}

	std::ostream& white(std::ostream& s)
	{
		SetConsoleColor(FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
		return s;
	}

	std::ostream& blue(std::ostream& s)
	{
		SetConsoleColor(FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
		return s;
	}

	std::ostream& red(std::ostream& s)
	{
		SetConsoleColor(FOREGROUND_RED | FOREGROUND_INTENSITY);
		return s;
	}

	std::ostream& green(std::ostream& s)
	{
		SetConsoleColor(FOREGROUND_GREEN | FOREGROUND_INTENSITY);
		return s;
	}

	std::ostream& yellow(std::ostream& s)
	{
		SetConsoleColor(FOREGROUND_RED| FOREGROUND_GREEN | FOREGROUND_INTENSITY);
		return s;
	}
#else
	std::ostream& white(std::ostream& s)
	{
		return s;
	}

	std::ostream& blue(std::ostream& s)
	{
		return s;
	}

	std::ostream& red(std::ostream& s)
	{
		return s;
	}

	std::ostream& green(std::ostream& s)
	{
		return s;
	}

	std::ostream& yellow(std::ostream& s)
	{
		return s;
	}
#endif
}
