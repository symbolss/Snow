/*******************************************************
* Copyright (c) 2014, QingYun All rights reserved.
* 
* FileName: CommonMacros.h
* Summary

* Author: yunmiao
* Date: 2014-5-23 14:49
*******************************************************/

#ifndef CommonMacros_h__
#define CommonMacros_h__

#ifdef _DEBUG
#define mars_assert(a) { bool v = (a); if(!v) { gFatalStream( __FILE__ << "," << __LINE__ << ":" << #a ); assert(a); return ; } } 
#define mars_assertn(a) { bool v = (a); if(!v) { gFatalStream( __FILE__ << "," << __LINE__ << ":" << #a ); assert(a); return 0; } } 
#define mars_assertf(a) { bool v = (a); if(!v) { gFatalStream( __FILE__ << "," << __LINE__ << ":" << #a ); assert(a); return -1; } } 
#define mars_assertr(a,rr) { bool v = (a); if(!v) { gFatalStream( __FILE__ << "," << __LINE__ << ":" << #a ); assert(a); return rr; } } 
#define mars_asserte(a) { bool v = (a); if(!v) {  gFatalStream( __FILE__ << "," << __LINE__ << ":" << #a ); assert(a); } } 
#define mars_assertop(a,op) { bool v = (a); if(!v) {  gFatalStream( __FILE__ << "," << __LINE__ << ":" << #a ); assert(a); op; } } 
#else
#define mars_assert(a) { bool v = (a); if(!v) { gFatalStream( __FILE__ << "," << __LINE__ << ":" << #a ); return ; } } 
#define mars_assertn(a) { bool v = (a); if(!v) { gFatalStream( __FILE__ << "," << __LINE__ << ":" << #a ); return 0; } } 
#define mars_assertf(a) { bool v = (a); if(!v) { gFatalStream( __FILE__ << "," << __LINE__ << ":" << #a ); return -1; } } 
#define mars_assertr(a,rr) { bool v = (a); if(!v) { gFatalStream( __FILE__ << "," << __LINE__ << ":" << #a ); return rr; } } 
#define mars_asserte(a) { bool v = (a); if(!v) { gFatalStream( __FILE__ << "," << __LINE__ << ":" << #a ); } } 
#define mars_assertop(a,op) { bool v = (a); if(!v) {  gFatalStream( __FILE__ << "," << __LINE__ << ":" << #a ); op; } } 
#endif


#define bit_get(flag, bit)	((flag & (1 << (bit - 1))) != 0)
#define bit_or(flag, bit)	(flag = flag | (1 << (bit - 1)))
#define bit_not(flag, bit)	(flag = flag & ~(1 << (bit - 1)))

#define SAFE_FREE(p)                { if(p) { free (p); (p) = NULL; } }
#define SAFE_DELETE(p)              { if(p) { delete (p); (p) = NULL; } }
#define SAFE_DELETE_ARRAY(p)        { if(p) { delete[] (p); (p) = NULL; } }
#define SAFE_RELEASE(p)             { if(p) { (p)->Release(); (p) = NULL; } }

#define NET_MSG_STRUCT_DEF(type)                        struct _##type


#define  REGIST_MODULE(cls,...)	{\
	ModuleFactory::Instance()->RegistCreateFunction(#cls, &(cls::CreateModule##cls));\
	cls::SetName(#cls);\
	moudle_helper<cls>(##__VA_ARGS__);\
										}\


#define  DECLARE_MODULE(cls)	public:\
										static Snow::IModule* CreateModule##cls(const char* clsName);\
										static void  SetName(char* pName){		m_Name = pName; }\
										static void	 SetRequire(const char* pReq1);\
										virtual const std::string& GetName(){	return m_Name; }\
									protected:\
										static std::string				m_Name;\
									public:\
										static vector<std::string>		m_Requires;\

#define  IMP_MODULE(ns,cls)		std::string	 ns::cls::m_Name = "";\
								vector<std::string>	ns::cls::m_Requires;\
								Snow::IModule* ns::cls::CreateModule##cls(const char* clsName)\
								{\
									return new cls;\
								}\
								void	ns::cls::SetRequire(const char* pReq1)\
								{\
									if (pReq1)\
									{\
										ns::cls::m_Requires.push_back(pReq1);\
									}\
								}\

#define  LOAD_MODULE(cls) {\
								for(vector<string>::iterator it = cls::m_Requires.begin(); it != cls::m_Requires.end(); ++it)\
								{\
									if(!LoadModule(*it))return false;\
								}\
								if(!LoadModule(string(#cls)))return false;\
						  }\


#define MSG_HANDLE_DEFINITION(type, pServer) _##type *pPack = (_##type *)pMsg->m_szData;\
    EventNetMsg Msg;\
    if (Msg.InitFromMsgType(type)){\
    _##type *pStruct = (_##type *)Msg.GetBody();\
    memcpy(pStruct, pPack, sizeof(_##type));\
    Msg.m_pSrcSocket = pSocket;\
    Msg.SendTo(pServer);\
    }

#define UNPACK_MSG(type)	CommonThreadData* pTData = (CommonThreadData *) pData;\
						if(pTData == NULL)return;\
						_##type* pPack = (_##type*)pTData->GetMsg()->m_szData;\
						if(pPack == NULL)return;\
						sint64 n8roleID = pTData->GetMsg()->m_i8Guid;



#define UNPACK_DB_MSG(type)	CommonThreadData* pTData = (CommonThreadData *) pData;\
					if(pTData == NULL)return;\
					 __DB_##type* pPack = ( __DB_##type*)pTData->GetMsg()->m_szData;\
					 if(pPack == NULL)return;\
					 pPack->m_i4SrvID = pTData->GetMsg()->m_i4SrvID;

					

#define CHECK_VARI_MSG(type, substruct, size)	{\
	const sint64 nValidSize = pTData->GetMsg()->m_i2DataSize - sint64(sizeof(NET_MSG_STRUCT_DEF(type)));\
	const sint64 nUserSize = sint64(sizeof(substruct)) * size;\
	if(nUserSize != nValidSize) return;\
												}

#define NEW_MSG_DEFINITION_F(type)	EventNetMsg Msg;\
									mars_assertf(Msg.InitFromMsgType(type));\
									_##type* pStruct = (_##type*)Msg.GetBody();\
									mars_assertf(pStruct);

#define NEW_MSG_DEFINITION_R(type)	EventNetMsg Msg;\
									mars_assertr(Msg.InitFromMsgType(type),false);\
									_##type* pStruct = (_##type*)Msg.GetBody();\
									mars_assertr(pStruct, false);

#define NEW_MSG_DEFINITION(type)	EventNetMsg Msg;\
									mars_assert(Msg.InitFromMsgType(type));\
									_##type* pStruct = (_##type*)Msg.GetBody();\
									mars_assert(pStruct);

#define VARI_MSG_DEFINITION_F(type, size)	EventNetMsg Msg;\
											mars_assertf(Msg.InitFromMsgType0(type, size));\
											_##type* pStruct = (_##type*)Msg.GetBody();\
											mars_assertf(pStruct);

#define VARI_MSG_DEFINITION(type, size)		EventNetMsg Msg;\
											mars_assert(Msg.InitFromMsgType0(type, size));\
											_##type* pStruct = (_##type*)Msg.GetBody();\
											mars_assert(pStruct);

#define VARI_MSG_DEFINITION_R(type, size)	EventNetMsg Msg;\
											mars_assertr(Msg.InitFromMsgType0(type, size), false);\
											_##type* pStruct = (_##type*)Msg.GetBody();\
											mars_assertr(pStruct, false);

#define FUNC_BEGIN_TIME()		sint64 nBegin = mars_time::clib_timestamp(); \
{

#define FUNC_END_TIME(name)		sint64 nEnd = mars_time::clib_timestamp();\
	sint64 difftime = nEnd - nBegin;\
	if (difftime >= 5) \
	{ \
		gDebugStream(#name<<" run totaltime="<<difftime);\
	}\
}

#define CHECK_USER_INFO(roleGuid,userState) User* pUser = GGameUserManager::Instance()->GetUser(roleGuid); \
	if (NULL == pUser) \
	{\
		NEW_MSG_DEFINITION(SC_CommonError);\
		pStruct->m_i4resultCode = -1;\
		Msg.SendTo(pTData->GetSocket());\
		gErrorStream("Req Info Fail,NULL == pUser,guid="<<roleGuid);\
		return;\
	}\
	if (pUser->GetUserStatus() != userState)\
	{\
		NEW_MSG_DEFINITION(SC_CommonError);\
		pStruct->m_i4resultCode = -1;\
		Msg.SendTo(pTData->GetSocket());\
		gErrorStream("Req Info Fail,status error="<<userState<<",current status="<<pUser->GetUserStatus()<<",guid="<<roleGuid);\
		return;\
	}

#define G_GET_MODULE(type)  type* pModule = dynamic_cast<type*>(GetThread()->GetModule<type>());\
										if (!pModule)\
										{\
											return;\
										}\

#define G_GET_MODULE_FROM_THREAD(type, thread)  type* pModule = dynamic_cast<type*>(thread->GetModule<type>());\
										if (!pModule)\
										{\
											return;\
										}\

#define G_GET_MODULE_FROM_THREAD_WITH_RETURN(type, thread, ret)  type* pModule = dynamic_cast<type*>(thread->GetModule<type>());\
										if (!pModule)\
										{\
											return ret;\
										}\

#define G_GET_MODULE_WITH_RETURN(type, ret)  type* pModule = dynamic_cast<type*>(GetThread()->GetModule<type>());\
										if (!pModule)\
										{\
											return ret;\
										}\


												/*-------------------------------------------Define部分开始-------------------------------------------*/
#define DATABLOCK_BEGIN_DEFINE(cls, filename) \
												class cls\
	{\
	public:\
	cls(){};

#define DATABLOCK_PARAM_DEFINE(type, field) \
	type field;

#define DATABLOCK_PARAM_STRING_DEFINE(type, field, length) \
	type field;

#define DATABLOCK_PARAM_STL_DEFINE_SINGLE(stltemplate,type, field) \
	stltemplate<type>	field;

#define DATABLOCK_PARAM_USER_DEFINE(type, field) \
	type field;

#define DATABLOCK_END_DEFINE(cls,callback) \
	};\
												class cls##Mng \
	{\
	public:\
	cls##Mng(){};\
	cls*	GetDataById(uint32 id);\
	bool	AddData(uint32 id, cls* record);\
	int		GetCount(){ return _DataSet.size();} \
	std_unordered_map<uint32, cls*>&	GetAllData(){return _DataSet;} \
	bool Load(const char* file);\
	private:\
	std_unordered_map<uint32, cls*> _DataSet;\
	};\

												/*-------------------------------------------Define部分结束-------------------------------------------*/


												/*---------------------------------------------IMP部分开始---------------------------------------------*/
#define DATABLOCK_BEGIN_IMP(cls, filename) \
	cls* cls##Mng::GetDataById(uint32 id)\
	{\
	std_unordered_map<uint32, cls*>::iterator it = _DataSet.find(id);\
	if (it != _DataSet.end())\
		{\
		return it->second;\
	}\
	return NULL;\
	}\
	bool cls##Mng::AddData(uint32 id, cls* record)\
	{\
	if (NULL == record)\
		{\
		return false;\
	}\
	return _DataSet.insert(make_pair(record->id, record)).second;\
	}\
	bool cls##Mng::Load(const char* file)\
	{\
	gDebugStream("Load Table Begin, FileName=" << filename);\
	DataBlockHelper::Instance()->Clear();\
	if(!DataBlockHelper::Instance()->OpenFile(filename))\
		{\
		gErrorStream("Can not open table file : " << filename);\
		return false;\
	}\
	if(!DataBlockHelper::Instance()->ParseHead())\
		{\
		gErrorStream("Can not parse table head! file : " << filename);\
		return false;\
	}\
	register const char* pMem = DataBlockHelper::Instance()->pMemory;\
	char szLine[MAX_LINE_BYTES] = {0};\
	uint32 nLine = 0;\
	while(1)\
		{\
		nLine++;\
		cls* record = new cls();\
		pMem = DataBlockHelper::Instance()->_GetLineFromMemory(szLine,MAX_LINE_BYTES, pMem, DataBlockHelper::Instance()->pEnd);\
		if(!pMem) break;\
		const char* pLine = szLine;\
		vector< std::string > vRet;\
		DataBlockHelper::Instance()->_ConvertStringToVector(pLine, vRet, "\t", true, false);\
		if(vRet.empty()) continue;\
		if(vRet.size() < DataBlockHelper::Instance()->vTitle.size())\
			{\
			uint32 nSubNum = (uint32)(DataBlockHelper::Instance()->vTitle.size() - vRet.size());\
			for(uint32 i = 0; i < nSubNum; i++)\
				{\
				vRet.push_back("");\
	}\
	}\
	if(vRet[0].empty()) \
			{\
			gErrorStream("The first field is blank! file = " << filename << "data line = " << nLine);\
			continue;\
	}

#define DATABLOCK_PARAM_IMP(type, field) \
	record->field = 0;\
	for(register uint32 i = 0; i < DataBlockHelper::Instance()->vTitle.size(); i++)\
	{\
		if (std::string(#field) == DataBlockHelper::Instance()->vTitle[i])\
		{\
			if (!DataBlockHelper::Instance()->TypeMatch(#type, DataBlockHelper::Instance()->vFieldsType[i]))\
			{\
				gErrorStream("Field type not match. field = " << #field << "file type = " << #type << "table type = " << DataBlockHelper::Instance()->vFieldsType[i]);\
				return false;\
			}\
			record ->field = mars_utils::Convertor<const char*, type>(vRet[i].c_str());\
		}\
	}

#define DATABLOCK_PARAM_STRING_IMP(type, field, length) \
	record ->field = NULL;\
	for(register uint32 i = 0; i < DataBlockHelper::Instance()->vTitle.size(); i++)\
			{\
			if (mars_utils::strcmp(#field, DataBlockHelper::Instance()->vTitle[i].c_str()) == 0)\
				{\
				if (!DataBlockHelper::Instance()->TypeMatch(#type, DataBlockHelper::Instance()->vFieldsType[i]))\
					{\
					gErrorStream("Field type not match.  field = " << #field << "file type = " << #type << "table type = " << DataBlockHelper::Instance()->vFieldsType[i]);\
					return false;\
	}\
	switch(DataBlockHelper::Instance()->vFieldsType[i])\
					{\
	case Field_Type::T_STRING:\
						{\
						if (vRet[i].size() > length)\
								{\
								gErrorStream("Table data field is too long, length = " << vRet[i].size() << "limit = " << length);\
								return false;\
	}\
	record ->field = (type)(new char[vRet[i].size() + 1]);\
	mars_utils::mystrncpy(record ->field, vRet[i].c_str(),vRet[i].size() + 1);\
	}\
	break;\
	default:\
						{\
						gErrorStream("Field not find string type. field=" <<#field<< "file type=" <<#type<< "table type=" << DataBlockHelper::Instance()->vFieldsType[i]);\
						return false;\
	}\
	}\
	break;\
	}\
	}

#define DATABLOCK_PARAM_STL_IMP_SINGLE(stltemplate,type, field) 

#define DATABLOCK_PARAM_USER_IMP(type, field)

#define DATABLOCK_END_IMP(cls, callback) \
	if(callback(record))\
		{\
		AddData(record->id, record);\
		}\
		else \
		{\
		gDebugStream("Load Table callback fail, FileName="<<#cls);\
		return false;\
		}\
	};\
	gDebugStream("Load Table End, FileName="<<#cls<<",totalCount="<< GetCount());\
	return true;\
	}
												/*---------------------------------------------IMP部分结束---------------------------------------------*/


												/*---------------------------------------------Run部分开始---------------------------------------------*/
#define DATABLOCK_BEGIN_RUN(cls, filename) \
	if (!Get##cls().Load(filename))\
	{\
	gErrorStream("Load Table="<<filename<<" is Fali!!");\
	return false;\
	}

#define DATABLOCK_PARAM_RUN(type,field)

#define DATABLOCK_PARAM_STRING_RUN(type,field, len)

#define DATABLOCK_PARAM_STL_RUN_SINGLE(stltemplate,type,field)

#define DATABLOCK_PARAM_USER_RUN(type, field)

#define DATABLOCK_END_RUN(cls,callback)
												/*---------------------------------------------Run部分结束---------------------------------------------*/			

	/*---------------------------------------------MoudleDefine部分开始---------------------------------------------*/
#define DATABLOCK_BEGIN_MOUDLE_DEFINE(cls, filename) \
	cls##Mng m_##cls;\
	cls##Mng& Get##cls(){return m_##cls;}

#define DATABLOCK_PARAM_MOUDLE_DEFINE(type,field)

#define DATABLOCK_PARAM_STRING_MOUDLE_DEFINE(type,field, len)

#define DATABLOCK_PARAM_STL_SINGLE_MOUDLE_DEFINE(stltemplate,type,field)

#define DATABLOCK_PARAM_USER_MOUDLE_DEFINE(type, field)

#define DATABLOCK_END_MOUDLE_DEFINE(cls,callback)
	/*---------------------------------------------MoudleDefine部分结束---------------------------------------------*/		

	/*---------------------------------------------EventDefine部分开始---------------------------------------------*/		
#define EVENT_BEGIN_DEFINE(cls,eventid) class cls : public Snow::IEvent\
										{\
										public:\
											static uint16 m_nEventID;\
											virtual uint16 GetEventID();

#define EVENT_PARAM_DEFINE(type, field) type field;

#define EVENT_END_DEFINE(type) };

	/*---------------------------------------------EventDefine部分结束---------------------------------------------*/	
	/*---------------------------------------------EventImp部分开始---------------------------------------------*/		
#define EVENT_BEGIN_IMP(cls,eventid) uint16 cls::m_nEventID = eventid;\
									 uint16 cls::GetEventID()\
									 {\
										return cls::m_nEventID;\
									 }\

#define EVENT_PARAM_IMP(type, field)

#define EVENT_END_IMP(type)
		

	/*---------------------------------------------EventImp部分结束---------------------------------------------*/	


#define CREATE_COMPONENT(cls) \
{\
	cls* p = new cls(this);\
	Result ret = p->Init();\
	if (R_OK != ret)\
	{\
		gErrorStream("Component Init Error Com = " << #cls << "].");\
		return ret;\
	}\
	ret = AddComponent(p);\
	if (R_OK != ret)\
	{\
		gErrorStream("Add Component Error Com = " << #cls << "].");\
		return ret;\
	}\
}\

#endif // CommonMacros_h__