/********************************************************************
	created:	2014/2/12  15:57
	file base:	SyntaxAnalysis
	file ext:	cpp
	author:		VyronLee
	
	purpose:	C++头文件语法分析器，主要用于提取头文件中包含的
				结构体(struct)，类(class)以及全局函数
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
	//构建只包含头文件名字信息的xml文本
	TiXmlDocument* headerDoc = CreateDocumentFrame(headerfile);

	//开始解析语法
	CFileProxy fileProxy(headerfile);
	bool bInComment = false;
	
	for (fileProxy.SeekToBegin(); !fileProxy.IsEnd(); fileProxy.SeekToNext())
	{
		//跳过注释块
		CSyntaxAnalysisHelper::SeekOverComment(fileProxy);

		//跳过空行
		CSyntaxAnalysisHelper::SeekOverBlank(fileProxy);

		//取得当前行
		string line = fileProxy.GetCurrentLine();

		//暂时不处理不相关语法
		if ( IsSyntaxIgnore(line) )
			continue;

		//提取结构体（结构体定义时往往前面会有typedef，这种情况留后处理）
		if ( StringUtil::StartWith(line, "struct") )
		{
			headerDoc->LinkEndChild(CSyntaxAnalysisHelper::ParseStruct(fileProxy));
		}

		//提取类
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
	if ( StringUtil::StartWith(line, "#")	//宏定义暂时都不处理了
		|| StringUtil::StartWith(line, "using namespace ")
		)
	{
		return TRUE;
	}
	return FALSE;
}