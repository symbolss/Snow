/*******************************************************
* Copyright (c) 2014, QingYun All rights reserved.
* 
* FileName: XmlParser.h
* Summary: 

* Author: fengqk
* Date: 2014/06/15  19:47
*******************************************************/

#ifndef _mars_xml_parser_
#define _mars_xml_parser_

#include "Define.h"
#include "tinyxml.h"

namespace mars_utils
{
	typedef std::list<std::string> ListValuesT;
	typedef std::map<std::string,ListValuesT> CollectionMapValuesT;

	struct XmlParseParams
	{
		std::vector<std::string> m_vParents;
		CollectionMapValuesT m_mapValues;

		std::string GetParents()
		{
			std::string result;
			result.reserve(512);
			for(size_t i = 0; i < m_vParents.size(); ++i)
				result.append("/").append(m_vParents[i]);
			return result;
		}
	};

	class MyTiVisitor: public TiXmlVisitor
	{
	public:
		virtual ~MyTiVisitor() {}
		/// Visit an element.
		virtual bool VisitEnter( const TiXmlElement& element, const TiXmlAttribute* firstAttribute );
		/// Visit an element.
		virtual bool VisitExit( const TiXmlElement& element );
		/// Visit a text node
		virtual bool Visit( const TiXmlText& text );

		XmlParseParams m_params;
	};

	class XmlParser
	{
	public:
		XmlParser();
		~XmlParser();
	public:
		int CleanUp();
		int LoadFromFile(const std::string& file);
		int LoadFromStream(std::istream& stream);
		int LoadFromString(const std::string& text);
	public:
		std::string GetValue(const std::string& path,const std::string& defaultValue = "");
		ListValuesT* GetValues(const std::string& path);
	public:	
		CollectionMapValuesT m_mapValues;
	};
}

#endif //_mars_xml_parser_
