/********************************************************************
	created:	2014/2/10  16:05
	file base:	VrGrep
	file ext:	cpp
	author:		VyronLee
	
	purpose:	��grep���ߣ����ڲ���ƥ���ַ��������ļ�λ��
*********************************************************************/

#include "stdafx.h"
#include "VrGrep.h"
#include <fstream>
#include <windows.h>

#define FILE_NAME(fullName) \
	std::string(fullName.c_str(), \
	fullName.find_last_of('\\') == std::string::npos ? 0 : fullName.find_last_of('\\')+1, fullName.length())

#define FILE_DIRECTORY(fullName) \
	std::string(fullName.c_str(), 0, \
	fullName.find_last_of('\\') == std::string::npos ? 0 : fullName.find_last_of('\\')+1)

VrGrep::VrGrep()
{

}

VrGrep::~VrGrep()
{

}

SVrGrepResultList VrGrep::Find( std::string text, std::string path, std::ostream* pOut/*=NULL*/ )
{
	std::string fileName = FILE_NAME(path);
	std::string fileDirectory = FILE_DIRECTORY(path);

	return FindInDirectory(text, fileDirectory, fileName, pOut);
}

SVrGrepResultList VrGrep::FindInFile( std::string text, std::string fileName, std::ostream* pOut/*=NULL*/ )
{
	std::ifstream readFile;
	readFile.open(fileName.c_str(), std::ios::in);

	if (!readFile.is_open())
	{
		if (NULL!=pOut)
		{
			*pOut << "��Ч���ļ�·����" << fileName << std::endl;
		}
		return SVrGrepResultList();
	}

	SVrGrepResultList resultList;
	int lineNo = 0;
	while ( !readFile.eof() )
	{
		std::string lineText;
		getline(readFile, lineText);
		++lineNo;

		std::string::size_type pos = lineText.find(text);
		if (std::string::npos != pos)
		{
			SVrGrepResult result;
			result.lineNo = lineNo;
			result.fileName = FILE_NAME(fileName);
			result.fileDirectory = FILE_DIRECTORY(fileName);
			result.lineText = lineText;
			
			resultList.push_back(result);
		
			if (NULL!=pOut)
			{
				*pOut << "[" << result.fileName << ", ��" << lineNo << "] " << result.lineText << std::endl; 
			}
		}
	}

	return resultList;
}

SVrGrepResultList VrGrep::FindInDirectory( std::string text, std::string directory, std::string fileExp, std::ostream* pOut/*=NULL*/ )
{
	std::string fileFormat = directory + "\\" + fileExp;
	WIN32_FIND_DATA findFileData;
	HANDLE hFind = FindFirstFile( fileFormat.c_str(), &findFileData);

	SVrGrepResultList resultList;

	if (INVALID_HANDLE_VALUE==hFind)
	{
		return resultList;
	}

	do
	{
		if (!(findFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
		{
			SVrGrepResultList resultInFile = FindInFile(text, directory+"\\"+findFileData.cFileName, pOut);
			copy(resultInFile.begin(), resultInFile.end(), back_inserter(resultList)); 
		}
		else if (findFileData.cFileName[0]!='.')	//��ǰĿ¼��.����Ŀ¼(..)����
		{
			return FindInDirectory(text, findFileData.cFileName,"*.*", pOut);
		}
	}
	while(FindNextFile(hFind, &findFileData));

	FindClose(hFind);

	return resultList;
}

SVrGrepResult VrGrep::FindOne( std::string text, std::string path, std::ostream* pOut/*=NULL*/ )
{
	std::string fileName = FILE_NAME(path);
	std::string fileDirectory = FILE_DIRECTORY(path);

	return FindOneInDirectory(text, fileDirectory, fileName, pOut);
}

SVrGrepResult VrGrep::FindOneInDirectory( std::string text, std::string directory, std::string fileExp, std::ostream* pOut/*=NULL*/ )
{
	std::string fileFormat = directory + "\\" + fileExp;
	WIN32_FIND_DATA findFileData;
	HANDLE hFind = FindFirstFile( fileFormat.c_str(), &findFileData);

	SVrGrepResult result;

	if (INVALID_HANDLE_VALUE==hFind)
	{
		return result;
	}

	do
	{
		if (!(findFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
		{
			result = FindOneInFile(text, directory+"\\"+findFileData.cFileName, pOut);

			if ( result.lineNo != INVALID_LINE_NO )
			{
				return result;
			}
		}
		else if (findFileData.cFileName[0]!='.')	//��ǰĿ¼��.����Ŀ¼(..)����
		{
			return FindOneInDirectory(text, findFileData.cFileName,"*.*", pOut);
		}
	}
	while(FindNextFile(hFind, &findFileData));

	FindClose(hFind);

	return result;
}

SVrGrepResult VrGrep::FindOneInFile( std::string text, std::string fileName, std::ostream* pOut/*=NULL*/ )
{
	std::ifstream readFile;
	readFile.open(fileName.c_str(), std::ios::in);

	if (!readFile.is_open())
	{
		if (NULL!=pOut)
		{
			*pOut << "��Ч���ļ�·����" << fileName << std::endl;
		}
		return SVrGrepResult();
	}

	SVrGrepResult result;
	int lineNo = 0;
	while ( !readFile.eof() )
	{
		std::string lineText;
		getline(readFile, lineText);
		++lineNo;

		std::string::size_type pos = lineText.find(text);
		if (std::string::npos != pos)
		{
			result.lineNo = lineNo;
			result.fileName = FILE_NAME(fileName);
			result.fileDirectory = FILE_DIRECTORY(fileName);
			result.lineText = lineText;

			if (NULL!=pOut)
			{
				*pOut << "[" << result.fileName << ", ��" << lineNo << "] " << result.lineText << std::endl; 
			}

			return result;
		}
	}

	return result;
}