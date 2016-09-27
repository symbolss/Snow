#include "Logger.h"

using namespace zsummer::log4z;
namespace mars_logger
{
	LoggerId g_objLoggerSystem;
	LoggerId g_objLoggerDebug;
	LoggerId g_objLoggerError;
	LoggerId g_objLoggerFatal;

	bool Init( const char* szCfgPath )
	{
		if(!ILog4zManager::GetInstance()->Config(szCfgPath))
		{
			return false;
		}
		g_objLoggerSystem = ILog4zManager::GetInstance()->FindLogger("system"); 
		g_objLoggerDebug = ILog4zManager::GetInstance()->FindLogger("debug"); 			
		g_objLoggerError = ILog4zManager::GetInstance()->FindLogger("error");
		g_objLoggerFatal = ILog4zManager::GetInstance()->FindLogger("fatal");
		return ILog4zManager::GetInstance()->Start();
	}

	void Fini()
	{
		ILog4zManager::GetInstance()->Stop();
	}
}
