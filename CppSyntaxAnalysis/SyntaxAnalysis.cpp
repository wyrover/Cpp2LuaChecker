/********************************************************************
	created:	2014/2/12  15:57
	file base:	SyntaxAnalysis
	file ext:	cpp
	author:		VyronLee
	
	purpose:	C++ͷ�ļ��﷨����������Ҫ������ȡͷ�ļ��а�����
				�ṹ��(struct)����(class)�Լ�ȫ�ֺ���
*********************************************************************/

#include "StdAfx.h"

#include "SyntaxAnalysis.h"
#include "KeyDef.h"
#include "StringUtil.h"
#include "FileProxy.h"
#include "SyntaxAnalysisHelper.h"

using namespace std;

CSyntaxAnalysis::CSyntaxAnalysis(void)
{
}

CSyntaxAnalysis::~CSyntaxAnalysis(void)
{
}

TiXmlDocument* CSyntaxAnalysis::ParseHeader( std::string headerfile )
{
	//����ֻ����ͷ�ļ�������Ϣ��xml�ı�
	TiXmlDocument* headerDoc = CreateDocumentFrame(headerfile);

	//��ʼ�����﷨
	CFileProxy fileProxy(headerfile);
	bool bInComment = false;
	
	for (fileProxy.SeekToBegin(); !fileProxy.IsEnd(); fileProxy.SeekToNext())
	{
		//����ע�Ϳ�
		CSyntaxAnalysisHelper::SeekOverComment(fileProxy);

		//��������
		CSyntaxAnalysisHelper::SeekOverBlank(fileProxy);

		//ȡ�õ�ǰ��
		string line = fileProxy.GetCurrentLine();

		//��ʱ����������﷨
		if ( IsSyntaxIgnore(line) )
			continue;

		//��ȡ�ṹ�壨�ṹ�嶨��ʱ����ǰ�����typedef���������������
		if ( StringUtil::StartWith(line, "struct") )
		{
			headerDoc->LinkEndChild(CSyntaxAnalysisHelper::ParseStruct(fileProxy));
		}

		//��ȡ��
		if ( StringUtil::StartWith(line, "class"))
		{

		}

	}
}

TiXmlElement* CSyntaxAnalysis::GetFunctionInLine( std::string line )
{
	
}

TiXmlDocument* CSyntaxAnalysis::CreateDocumentFrame( std::string headerfile )
{
	string headerName = StringUtil::Right(headerfile, "\\");

	TiXmlElement* rootElement = new TiXmlElement("header");
	rootElement->SetAttribute("name", headerName.c_str());
	
	TiXmlDocument* headerDoc = new TiXmlDocument;
	headerDoc->LinkEndChild(rootElement);
	
	return headerDoc;
}

BOOL CSyntaxAnalysis::IsSyntaxIgnore( std::string line )
{
	if ( StringUtil::StartWith(line, "#")	//�궨����ʱ����������
		|| StringUtil::StartWith(line, "using namespace ")
		)
	{
		return TRUE;
	}
	return FALSE;
}