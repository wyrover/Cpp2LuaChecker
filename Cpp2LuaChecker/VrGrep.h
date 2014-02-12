#pragma once

#include <ostream>
#include <vector>
#include <string>

#define INVALID_LINE_NO -1

typedef struct tagVrGrepResult
{
	int lineNo;					//行号，-1表示查找不到
	std::string lineText;		//对应行文本
	std::string fileName;		//对应文件名
	std::string fileDirectory;	//对应文件目录

	tagVrGrepResult() : lineNo(INVALID_LINE_NO) {};
} 
SVrGrepResult, *LPVrGrepResult;


typedef std::vector<SVrGrepResult> SVrGrepResultList;

class VrGrep
{
public:
	VrGrep();
	~VrGrep();

public:
	//************************************
	// Method:    Find
	// FullName:  VrGrep::Find
	// Access:    public 
	// Returns:   SVrGrepResultList
	// Qualifier:
	// Parameter: std::string text	待查找文本，区分大小写，全匹配
	// Parameter: std::string path	查找路径，支持通配
	// Parameter: std::ostream * pOut	输出查找信息
	// Purpose: 根据输入的文本在指定路径中查找匹配项，返回所有匹配项列表
	//************************************
	SVrGrepResultList Find(std::string text, std::string path, std::ostream* pOut=NULL);	

	//************************************
	// Method:    FindOne
	// FullName:  VrGrep::FindOne
	// Access:    public 
	// Returns:   SVrGrepResult
	// Qualifier:
	// Parameter: std::string text	待查找文本，区分大小写，全匹配
	// Parameter: std::string path  查找路径，支持通配
	// Parameter: std::ostream * pOut	输出查找信息
	// Purpose: 根据输入的文本在指定路径中查找匹配项，找到即停止，返回首个匹配项
	//************************************
	SVrGrepResult FindOne(std::string text, std::string path, std::ostream* pOut=NULL);

private:
	//************************************
	// Method:    FindInDirectory
	// FullName:  VrGrep::FindInDirectory
	// Access:    private 
	// Returns:   SVrGrepResultList
	// Qualifier:
	// Parameter: std::string text	待查找文本，区分大小写，全匹配
	// Parameter: std::string directory	查找目录
	// Parameter: std::string fileRegExp	查找的文件通配字符串
	// Parameter: std::ostream * pOut	输出查找信息
	//************************************
	SVrGrepResultList FindInDirectory(std::string text, std::string directory, std::string fileExp, std::ostream* pOut=NULL);


	//************************************
	// Method:    FindInFile
	// FullName:  VrGrep::FindInFile
	// Access:    private 
	// Returns:   SVrGrepResultList
	// Qualifier:
	// Parameter: std::string text 待查找文本，区分大小写，全匹配
	// Parameter: std::string fileName	文件路径名
	// Parameter: std::ostream * pOut	输出查找信息
	//************************************
	SVrGrepResultList FindInFile(std::string text, std::string fileName, std::ostream* pOut=NULL);

	//************************************
	// Method:    FindInDirectory
	// FullName:  VrGrep::FindInDirectory
	// Access:    private 
	// Returns:   SVrGrepResultList
	// Qualifier:
	// Parameter: std::string text	待查找文本，区分大小写，全匹配
	// Parameter: std::string directory	查找目录
	// Parameter: std::string fileRegExp	查找的文件通配字符串
	// Parameter: std::ostream * pOut	输出查找信息
	//************************************
	SVrGrepResult FindOneInDirectory(std::string text, std::string directory, std::string fileExp, std::ostream* pOut=NULL);

	//************************************
	// Method:    FindInFile
	// FullName:  VrGrep::FindInFile
	// Access:    private 
	// Returns:   SVrGrepResultList
	// Qualifier:
	// Parameter: std::string text 待查找文本，区分大小写，全匹配
	// Parameter: std::string fileName	文件路径名
	// Parameter: std::ostream * pOut	输出查找信息
	//************************************
	SVrGrepResult FindOneInFile(std::string text, std::string fileName, std::ostream* pOut=NULL);
};