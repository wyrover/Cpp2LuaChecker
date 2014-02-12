#ifndef __SyntaxAnalysisHelper_H__
#define __SyntaxAnalysisHelper_H__

#include "FileProxy.h"
#include "StringUtil.h"
#include "tinyxml/tinyxml.h"

class CSyntaxAnalysisHelper
{
public:
	static void SeekOverComment(CFileProxy& pFileProxy)
	{
		bool bBlockComment = false;
		while ( !pFileProxy.IsEnd() )
		{
			const string& text = pFileProxy.GetCurrentLine();

			if ( StringUtil::StartWith(text, "//") )
			{
				pFileProxy.SeekToNext();
				continue;
			}

			if ( StringUtil::StartWith(text, "/*") )
			{
				bBlockComment = true;
				continue;
			}

			if ( StringUtil::NPos != StringUtil::Find(text, "*/") )
			{
				bBlockComment = false;
				continue;
			}

			break;
		}
	}

	static void SeekOverBlank(CFileProxy& pFileProxy)
	{
		while ( !pFileProxy.IsEnd() )
		{
			const string& text = pFileProxy.GetCurrentLine();

			if ( !StringUtil::IsBlank(text) )
			{			
				break;
			}
		}
	}

	static TiXmlElement* ParseStruct(CFileProxy& pFileProxy)
	{
		TiXmlElement* pStructElement = new TiXmlElement;
		while ( !pFileProxy.IsEnd() )
		{
			
		}
	}
};


#endif // __SyntaxAnalysisHelper_H__
