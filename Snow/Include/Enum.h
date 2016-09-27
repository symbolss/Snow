/*******************************************************
* Copyright (c) 2014, QingYun All rights reserved.
* 
* FileName: CommonEnum.h
* Summary: 
		����ö�ٶ���
* Author: lzc
* Date: 2015/03/20  17:13
*******************************************************/

#ifndef CommonEnum_h__
#define CommonEnum_h__

//�ֶ���������
typedef enum _Field_Type{
	T_INT		= 0,	//����
	T_FLOAT		= 1,	//������
	T_STRING	= 2,	//�ַ���
	T_BOOL		= 3,	//����	
}Field_Type;

/*
	���������Ͷ���
*/
enum SeverType
{
	Server_None = -1,
	Data_Type,		//data	server
	Game_Type,		//game	server
	Client_Type,	//�ͻ��ˣ�Ŀǰ������ʹ��
	Sever_Max,
};

enum FunctionRet
{
	R_FAIL = -1,					//ʧ��
	R_OK,							//�ɹ�
	R_INTERFACE_NOT_FOUND,			//�Ҳ���interface
};

#endif // CommonEnum_h__


