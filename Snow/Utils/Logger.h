/*******************************************************
* Copyright (c) 2014, QingYun All rights reserved.
* 
* FileName: Logger.h
* Summary: 

* Author: liuyudong
* Date: 2014/12/8 20:11
*******************************************************/
#ifndef __Logger_h__
#define __Logger_h__

#include "log4z.h"
namespace mars_logger
{
	//系统日志
	extern LoggerId g_objLoggerSystem;
	extern LoggerId g_objLoggerDebug;
	extern LoggerId g_objLoggerError;
	//异常日志
	extern LoggerId g_objLoggerFatal;
	extern LoggerId g_objLoggerLogic;
	//统计日志
	//extern LoggerId g_objLoggerAudit;
	extern LoggerId g_objLoggerMoney;
	//extern LoggerId g_objLoggerClient;
	extern LoggerId g_objLoggerProf;
	//模块日志
	extern LoggerId g_objLoggerModule;

	extern bool Init(const char* szCfgPath);
	extern void Fini();
}

#define gSystemStream(x)	{ LOG_INFO(mars_logger::g_objLoggerSystem, x); }
#define gDebugStream(x)		{ LOG_DEBUG(mars_logger::g_objLoggerDebug, x); }
#define gErrorStream(x)		{ LOG_ERROR(mars_logger::g_objLoggerError, x); }
#define gFatalStream(x)		{ LOG_FATAL(mars_logger::g_objLoggerFatal, x); }

#define gProfFormat(fmt, ...)	{ LOGFMT_INFO(mars_logger::g_objLoggerProf, fmt, ##__VA_ARGS__); }

#endif	// __Logger_h__
