/********************************************************************
	created:	2014/2/12  17:00
	file base:	FileProxy
	file ext:	cpp
	author:		VyronLee
	
	purpose:	文件读取代理，用于快速读取文件以及取得行号对应文本，
				或者根据文本取得行号；同时可用于遍历文本
*********************************************************************/
#include "StdAfx.h"
#include "FileProxy.h"
#include <fstream>
using namespace std;


////////////////////////////////////
///////		CFileProxy		////////
////////////////////////////////////

CFileProxy::CFileProxy( std::string filename )
:m_iIndicator(1)
{
	Load(filename);
}

CFileProxy::~CFileProxy(void)
{
}

BOOL CFileProxy::Load( std::string filename )
{
	ifstream readfile(filename.c_str());

	if ( !readfile.is_open() )
	{
		return FALSE;
	}

	int lineNo = 0;
	string text;
	while ( !readfile.eof() )
	{
		getline(readfile, text);
		lineNo++;

		m_Document.InsertLine(lineNo, text);
	}

	return TRUE;
}

int CFileProxy::GetLineNo( const std::string text )
{
	return m_Document.GetLineNo(text);
}

const std::string& CFileProxy::GetLine( int lineNo )
{
	return m_Document.GetLine(lineNo);
}

void CFileProxy::SeekToBegin()
{
	m_iIndicator = 1;
}

void CFileProxy::SeekToNext()
{
	m_iIndicator = m_iIndicator+1>m_Document.Size()?m_Document.Size():m_iIndicator+1;
}

void CFileProxy::SeekToEnd()
{
	m_iIndicator = m_Document.Size();	
}

const std::string CFileProxy::GetCurrentLine()
{
	return m_Document.GetLine(m_iIndicator);
}

bool CFileProxy::IsEnd()
{
	return m_iIndicator > m_Document.Size();
}

////////////////////////////////////
/////		TDocument		////////
////////////////////////////////////

TDocument::TDocument()
{

}

TDocument::~TDocument()
{
	for ( std::vector<TLine*>::iterator itLine=m_Lines.begin(); itLine!=m_Lines.end(); ++itLine )
	{
		delete *itLine;
	}
	m_Lines.clear();
}

const std::string& TDocument::GetLine( int lineNo )
{
	if ( lineNo<0 || lineNo>=(int)m_Lines.size() )
	{
		return TLine::EMPTY_STRING;
	}
	return m_Lines[lineNo]->text;
}

int TDocument::GetLineNo( const std::string text )
{
	for ( std::vector<TLine*>::iterator itLine=m_Lines.begin(); itLine!=m_Lines.end(); ++itLine )
	{
		if ( (*itLine)->text == text )
		{
			return (*itLine)->lineNo;
		}
	}
	return INVALID_LINE_NO;
}

void TDocument::InsertLine( int lineNo, std::string text )
{
	LPLine line = new TLine;
	line->lineNo = lineNo;
	line->text = text;

	m_Lines.push_back(line);
}

int TDocument::Size()
{
	return m_Lines.size();
}