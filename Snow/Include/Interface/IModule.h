/*******************************************************
* Copyright (c) 2014, QingYun All rights reserved.
* 
* FileName: IModule.h
* Summary: ģ��ӿ�

* Author: maoyanwen
* Date: 2015/06/01 
*******************************************************/
#ifndef IModule_h__
#define IModule_h__

#include "Interface/IInterface.h"

namespace Snow{
	class IModule : public IInterface
	{
	public:
		virtual const string& GetName() = 0;

		virtual bool Init() = 0;
	};
};


#endif // IModule_h__