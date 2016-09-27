/*******************************************************
* Copyright (c) 2014, QingYun All rights reserved.
* 
* FileName: CommonEnum.h
* Summary: 
		公共枚举定义
* Author: lzc
* Date: 2015/03/20  17:13
*******************************************************/

#ifndef CommonEnum_h__
#define CommonEnum_h__

//字段数据类型
typedef enum _Field_Type{
	T_INT		= 0,	//整数
	T_FLOAT		= 1,	//浮点数
	T_STRING	= 2,	//字符串
	T_BOOL		= 3,	//布尔	
}Field_Type;

/*
	服务器类型定义
*/
enum SeverType
{
	Server_None = -1,
	Data_Type,		//data	server
	Game_Type,		//game	server
	Client_Type,	//客户端，目前机器人使用
	Sever_Max,
};

enum FunctionRet
{
	R_FAIL = -1,					//失败
	R_OK,							//成功
	R_INTERFACE_NOT_FOUND,			//找不到interface
};

#endif // CommonEnum_h__


