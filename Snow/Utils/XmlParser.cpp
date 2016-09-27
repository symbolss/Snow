/*******************************************************
* Copyright (c) 2014, QingYun All rights reserved.
* 
* FileName: XmlParser.cpp
* Summary: 

* Author: fengqk
* Date: 2014/06/15  19:51
*******************************************************/
#include "XmlParser.h"

namespace mars_utils
{

	XmlParser::XmlParser()
	{
	}

	XmlParser::~XmlParser()
	{
	}


	int XmlParser::LoadFromFile(const std::string& file)
	{
		TiXmlDocument doc(file.c_str());
		mars_assertf(doc.LoadFile(TIXML_ENCODING_UTF8));

		MyTiVisitor myVisitor;
		mars_assertf(doc.Accept(&myVisitor));

		m_mapValues = myVisitor.m_params.m_mapValues;

		return 0;
	}

	std::string XmlParser::GetValue(const std::string& path,const std::string& defaultValue)
	{
		CollectionMapValuesT::iterator iter = m_mapValues.find(path);
		if(iter == m_mapValues.end())
			return defaultValue;

		ListValuesT& values = iter->second;
		if (values.empty())
		{
			return defaultValue;
		}
		
		return iter->second.front();
	}

	ListValuesT* XmlParser::GetValues( const std::string& path)
	{
		CollectionMapValuesT::iterator iter = m_mapValues.find(path);
		if(iter == m_mapValues.end())
		{
			return NULL;
		}
		return &iter->second;
	}

	int XmlParser::CleanUp()
	{
		m_mapValues.clear();
		return 0;
	}


	bool MyTiVisitor::VisitEnter( const TiXmlElement& element, const TiXmlAttribute* firstAttribute )
	{
		m_params.m_vParents.push_back(element.Value());
		return true;
	}


	bool MyTiVisitor::VisitExit( const TiXmlElement& element )
	{
		m_params.m_vParents.pop_back();
		return true;
	}

	bool MyTiVisitor::Visit( const TiXmlText& text )
	{
		std::string key;
		std::string val(text.Value());

		key = m_params.GetParents();
		m_params.m_mapValues[key].push_back(val);

		return true;
	}

}
