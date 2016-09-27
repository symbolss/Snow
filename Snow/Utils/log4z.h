/*
 * Log4z License
 * -----------
 * 
 * Log4z is licensed under the terms of the MIT license reproduced below.
 * This means that Log4z is free software and can be used for both academic
 * and commercial purposes at absolutely no cost.
 * 
 * 
 * ===============================================================================
 * 
 * Copyright (C) 2010-2014 YaweiZhang <yawei_zhang@foxmail.com>.
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 * 
 * ===============================================================================
 * 
 * (end of COPYRIGHT)
 */


/*
 * AUTHORS:  YaweiZhang <yawei_zhang@foxmail.com>
 * VERSION:  2.8.0
 * PURPOSE:  A lightweight library for error reporting and logging to file and screen .
 * CREATION: 2010.10.4
 * LCHANGE:  2014.09.27
 * LICENSE:  Expat/MIT License, See Copyright Notice at the begin of this file.
 */


/*
 * contact me:
 * tencent qq group: 19811947
 * mail: yawei_zhang@foxmail.com
 */


/* 
 * UPDATES LOG
 * 
 * VERSION 0.1.0 <DATE: 2010.10.4>
 * 	create the first project.  
 * 	It support put log to screen and files, 
 * 	support log level, support one day one log file.
 * 	support multi-thread, cross-platform.
 * 
 * VERSION .... <DATE: ...>
 * 	...
 * 
 * VERSION 0.9.0 <DATE: 2012.12.24>
 * 	support config files.
 * 	support color text in screen.
 * 	support multiple output to different files.
 * 
 * VERSION 1.0.0 <DATE: 2012.12.29>
 * 	support comments in the config file.
 * 	add a advanced demo in the ./project
 * 	fix some details.
 * 
 * VERSION 1.0.1 <DATE: 2013.01.01>
 * 	change and add some Comments in the log4z
 * 	simplify the 'fast_test' demo projects.
 * 
 * VERSION 1.1.0 <DATE: 2013.01.24>
 * 	the method Start will wait for the logger thread started.
 * 	config and add method change. 
 * 	namespace change.
 * 
 * VERSION 1.1.1 <DATE: 2013.02.23>
 * 	add status info method.
 * 	optimize. 
 *
 * VERSION 1.2.0 <DATE: 2013.04.05>
 * 	add stress test demo
 *  rewrite Stream module,better performance. 
 * 
 * VERSION 1.2.1 <DATE: 2013.04.13>
 * 	fixed type name 'long' stream format on 64/32 operation system.
 *  logger will not loss any log on process normal exit.
 *
 * VERSION 2.0.0 <DATE: 2013.04.25>
 * 	new interface: 
 *      merge some Main interface and Dynamic interface
 *      add Change Logger Attribute method by thread-safe
 * 	new config design.
 * 	log file name append process id.
 *
 * VERSION 2.1 <DATE: 2013.05.22>
 * 	support binary text output 
 *  rewrite write file module, support vs2005 open Chinese characters path
 *
 * VERSION 2.2 <DATE: 2013.07.08>
 *	optimized binary stream output view
 * 	support wchar * string.
 *  
 * VERSION 2.3 <DATE: 2013.08.29>
 *  adjust output file named.
 *  support different month different directory.
 *  adjust some detail.
 * 
 * VERSION 2.4 <DATE: 2013.10.07>
 *  support rolling log file.
 *  support hot update configure
 *  used precision time in log.
 *  micro set default logger attribute
 *  fix tls bug in windows xp dll
 *
 * VERSION 2.5 <DATE: 2014.03.25>
 *  screen output can choice synchronous or not
 *  fix sometimes color will disorder on windows.
 *  eliminate some compiler warning
 *  fix sem_timewait in linux
 *  add format-style method at input log, cannot support vs2003 and VC6.
 *  fix WCHAR String cannot output
 *  optimize std::string, binary log input, and support std::wstring.
 *  clean code, better readability
 *  
 * VERSION 2.6 <DATE: 2014.08.19>
 *  add PrePushLog 
 *  better performance when log is filter out.
 *  interface replace std::string because it's in shared library is unsafe.
 *  add log level 'trace'
 * 
 * VERSION 2.6.1 <DATE: 2014.08.22>
 *  fix bug from defined _MSC_VER 
 *
 * VERSION 2.7 <DATE: 2014.09.21>
 *  compatible mac machine,  now  log4z can working in linux/windows/mac.
 *
 * VERSION 2.8 <DATE: 2014.09.27>
 *  support synchronous written to file and thread-safe
 *  
 */


#pragma once
#ifndef _ZSUMMER_LOG4Z_H_
#define _ZSUMMER_LOG4Z_H_

#include <string>
#include <sstream>
#include <errno.h>
#include <stdio.h>
#ifdef WIN32
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#endif

//! logger ID type. DO NOT TOUCH
typedef int LoggerId;

//! the invalid logger id. DO NOT TOUCH
const int LOG4Z_INVALID_LOGGER_ID = -1;

//! the main logger id. DO NOT TOUCH
//! can use this id to set the main logger's attribute.
//! example:
//! ILog4zManager::GetInstance()->SetLoggerLevel(LOG4Z_MAIN_LOGGER_ID, LOG_LEVEL_WARN);
//! ILog4zManager::GetInstance()->SetLoggerDisplay(LOG4Z_MAIN_LOGGER_ID, false);
const int LOG4Z_MAIN_LOGGER_ID = 0;

//! the main logger name. DO NOT TOUCH
const char*const LOG4Z_MAIN_LOGGER_NAME = "Main";

//! check VC VERSION. DO NOT TOUCH
//! format micro cannot support VC6 or VS2003, please use stream input log, like LOGI, LOGD, LOG_DEBUG, LOG_STREAM ...
#if _MSC_VER >= 1400 //MSVC >= VS2005
#define LOG4Z_FORMAT_INPUT_ENABLE
#endif

#ifndef WIN32
#define LOG4Z_FORMAT_INPUT_ENABLE
#endif

//! LOG Level
enum ENUM_LOG_LEVEL
{
	LOG_LEVEL_TRACE = 0,
	LOG_LEVEL_DEBUG,
	LOG_LEVEL_INFO,
	LOG_LEVEL_WARN,
	LOG_LEVEL_ERROR,
	LOG_LEVEL_ALARM,
	LOG_LEVEL_FATAL,
};

//////////////////////////////////////////////////////////////////////////
//! -----------------default logger config, can change on this.-----------
//////////////////////////////////////////////////////////////////////////
//! the max logger count.
const int LOG4Z_LOGGER_MAX = 10;
//! the max log content length.
const int LOG4Z_LOG_BUF_SIZE = 2048;

//! all logger synchronous output or not
const bool LOG4Z_ALL_SYNCHRONOUS_OUTPUT = false;
//! all logger write log to file or not
const bool LOG4Z_ALL_WRITE_TO_FILE = true;
//! all logger synchronous display to the windows debug output
const bool LOG4Z_ALL_DEBUGOUTPUT_DISPLAY = false;

//! default logger output file.
const char* const LOG4Z_DEFAULT_PATH = "./log/";
//! default log filter level
const int LOG4Z_DEFAULT_LEVEL = LOG_LEVEL_DEBUG;
//! default logger display
const bool LOG4Z_DEFAULT_DISPLAY = true;
//! default logger month dir used status
const bool LOG4Z_DEFAULT_MONTHDIR = false;
//! default logger output file limit size, unit M byte.
const int LOG4Z_DEFAULT_LIMITSIZE = 100;
//! default raw
const bool LOG4Z_DEFAULT_RAW = false;

///////////////////////////////////////////////////////////////////////////
//! -----------------------------------------------------------------------
//////////////////////////////////////////////////////////////////////////





#ifndef _ZSUMMER_BEGIN
#define _ZSUMMER_BEGIN namespace zsummer {
#endif  
#ifndef _ZSUMMER_LOG4Z_BEGIN
#define _ZSUMMER_LOG4Z_BEGIN namespace log4z {
#endif
_ZSUMMER_BEGIN
_ZSUMMER_LOG4Z_BEGIN




//! log4z class
class ILog4zManager
{
public:
	ILog4zManager(){};
	virtual ~ILog4zManager(){};
	virtual std::string GetExampleConfig() = 0;

	//! Log4z Singleton
	static ILog4zManager * GetInstance();

	//! Config or overwrite configure
	//! Needs to be called before ILog4zManager::Start,, OR Do not call.
	virtual bool Config(const char * strCfgPath) = 0;

	//! Create or overwrite logger, Total count limited by LOG4Z_LOGGER_MAX.
	//! Needs to be called before ILog4zManager::Start, OR Do not call.
	virtual LoggerId CreateLogger(const char* strName, 
		const char* strPath = LOG4Z_DEFAULT_PATH,
		int nLevel = LOG4Z_DEFAULT_LEVEL,
		bool display = LOG4Z_DEFAULT_DISPLAY,
		bool monthdir = LOG4Z_DEFAULT_MONTHDIR,
		unsigned int limitsize = LOG4Z_DEFAULT_LIMITSIZE /*million byte, rolling file*/,
		bool raw = LOG4Z_DEFAULT_RAW) = 0;

	//! Start Log Thread. This method can only be called once by one process.
	virtual bool Start() = 0;

	//! Default the method will be calling at process exit auto.
	//! Default no need to call and no recommended.
	virtual bool Stop() = 0;

	//! Find logger. thread safe.
	virtual LoggerId FindLogger(const char* strName) =0;

	//pre-check the log filter. if filter out return false. 
	virtual bool PrePushLog(LoggerId id, int level) = 0;
	//! Push log, thread safe.
	virtual bool PushLog(LoggerId id, int level, const char * log) = 0;

	//! Set logger's attribute, thread safe.
	virtual bool SetLoggerLevel(LoggerId nLoggerID, int nLevel) = 0;
	virtual bool SetLoggerDisplay(LoggerId nLoggerID, bool enable) = 0;
	virtual bool SetLoggerMonthdir(LoggerId nLoggerID, bool use) = 0;
	virtual bool SetLoggerLimitSize(LoggerId nLoggerID, unsigned int limitsize) = 0;
	//! Update logger's attribute from config file, thread safe.
	virtual bool UpdateConfig() = 0;

	//! Log4z status statistics, thread safe.
	virtual unsigned long long GetStatusTotalWriteCount() = 0;
	virtual unsigned long long GetStatusTotalWriteBytes() = 0;
	virtual unsigned long long GetStatusWaitingCount() = 0;
	virtual unsigned int GetStatusActiveLoggers() = 0;

};

#ifndef _ZSUMMER_END
#define _ZSUMMER_END }
#endif  
#ifndef _ZSUMMER_LOG4Z_END
#define _ZSUMMER_LOG4Z_END }
#endif

_ZSUMMER_LOG4Z_END
_ZSUMMER_END

//! base micro.
#define LOG_STREAM(id, level, log)\
{\
	if (zsummer::log4z::ILog4zManager::GetInstance()->PrePushLog(id,level)) \
	{\
		std::stringstream ss;\
		ss << log;\
		zsummer::log4z::ILog4zManager::GetInstance()->PushLog(id, level, ss.str().c_str());\
	}\
}

//! fast micro
#define LOG_TRACE(id, log) LOG_STREAM(id, LOG_LEVEL_TRACE, log)
#define LOG_DEBUG(id, log) LOG_STREAM(id, LOG_LEVEL_DEBUG, log)
#define LOG_INFO(id, log)  LOG_STREAM(id, LOG_LEVEL_INFO, log)
#define LOG_WARN(id, log)  LOG_STREAM(id, LOG_LEVEL_WARN, log)
#define LOG_ERROR(id, log) LOG_STREAM(id, LOG_LEVEL_ERROR, log)
#define LOG_ALARM(id, log) LOG_STREAM(id, LOG_LEVEL_ALARM, log)
#define LOG_FATAL(id, log) LOG_STREAM(id, LOG_LEVEL_FATAL, log)

//! super micro.
#define LOGT( log ) LOG_TRACE(LOG4Z_MAIN_LOGGER_ID, log )
#define LOGD( log ) LOG_DEBUG(LOG4Z_MAIN_LOGGER_ID, log )
#define LOGI( log ) LOG_INFO(LOG4Z_MAIN_LOGGER_ID, log )
#define LOGW( log ) LOG_WARN(LOG4Z_MAIN_LOGGER_ID, log )
#define LOGE( log ) LOG_ERROR(LOG4Z_MAIN_LOGGER_ID, log )
#define LOGA( log ) LOG_ALARM(LOG4Z_MAIN_LOGGER_ID, log )
#define LOGF( log ) LOG_FATAL(LOG4Z_MAIN_LOGGER_ID, log )


#ifdef WIN32
#define LOG_FORMAT(id, level, logformat, ...) \
{ \
	if (zsummer::log4z::ILog4zManager::GetInstance()->PrePushLog(id,level)) \
	{\
		char logbuf[LOG4Z_LOG_BUF_SIZE]; \
		_snprintf_s(logbuf, LOG4Z_LOG_BUF_SIZE, _TRUNCATE, logformat, ##__VA_ARGS__); \
		zsummer::log4z::ILog4zManager::GetInstance()->PushLog(id, level, logbuf); \
	}\
}
#else
#define LOG_FORMAT(id, level, logformat, ...) \
{ \
	if (zsummer::log4z::ILog4zManager::GetInstance()->PrePushLog(id,level)) \
	{\
		char logbuf[LOG4Z_LOG_BUF_SIZE]; \
		snprintf(logbuf, LOG4Z_LOG_BUF_SIZE,logformat, ##__VA_ARGS__); \
		zsummer::log4z::ILog4zManager::GetInstance()->PushLog(id, level, logbuf); \
	} \
}
#endif

//!format string
#define LOGFMT_TRACE(id, fmt, ...)  LOG_FORMAT(id, LOG_LEVEL_TRACE, fmt, ##__VA_ARGS__)
#define LOGFMT_DEBUG(id, fmt, ...)  LOG_FORMAT(id, LOG_LEVEL_DEBUG, fmt, ##__VA_ARGS__)
#define LOGFMT_INFO(id, fmt, ...)  LOG_FORMAT(id, LOG_LEVEL_INFO, fmt, ##__VA_ARGS__)
#define LOGFMT_WARN(id, fmt, ...)  LOG_FORMAT(id, LOG_LEVEL_WARN, fmt, ##__VA_ARGS__)
#define LOGFMT_ERROR(id, fmt, ...)  LOG_FORMAT(id, LOG_LEVEL_ERROR, fmt, ##__VA_ARGS__)
#define LOGFMT_ALARM(id, fmt, ...)  LOG_FORMAT(id, LOG_LEVEL_ALARM, fmt, ##__VA_ARGS__)
#define LOGFMT_FATAL(id, fmt, ...)  LOG_FORMAT(id, LOG_LEVEL_FATAL, fmt, ##__VA_ARGS__)

#endif





