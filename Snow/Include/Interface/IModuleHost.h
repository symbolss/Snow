/*******************************************************
* Copyright (c) 2014, QingYun All rights reserved.
* 
* FileName: IModuleHost.h
* Summary: Ä£¿éËÞÖ÷

* Author: maoyanwen
* Date: 2015/06/01 
*******************************************************/
#ifndef IModuleHost_h__
#define IModuleHost_h__
#include "IModule.h"

namespace Snow
{
	class IModuleHost : public IInterface
	{
	public:
		void			AddModule(IModule* pModule){	m_Modules.push_back(pModule);	}

		template<typename T>
		T*		GetModule(); 

		virtual bool	LoadModule(string& name) = 0;

		bool			FindModule(string& name)
		{
			for (size_t i = 0; i < m_Modules.size(); ++i)
			{
				if (m_Modules[i]->GetName() == name)
				{
					return true;
				}
			}
			return false;
		}

		
	protected:
		vector<IModule*>	m_Modules;
		
	};

	template<typename T>
	T* IModuleHost::GetModule()
	{
		for (size_t i = 0; i < m_Modules.size(); ++i)
		{
			if (typeid(T) == typeid(*(m_Modules[i])))
			{
				return dynamic_cast<T*>(m_Modules[i]);
			}
		}
		return NULL;
	}


};
#endif // IModuleHost_h__
