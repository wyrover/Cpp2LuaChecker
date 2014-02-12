#pragma once

#include <string>
#include <vector>

#define INVALID_LINE_NO -1

typedef struct tagLine
{
	int lineNo;
	std::string text;

	tagLine() : lineNo(INVALID_LINE_NO) {}

	static std::string EMPTY_STRING;
} 
TLine, *LPLine;

std::string TLine::EMPTY_STRING = "";

class TDocument
{
public:
	TDocument();
	~TDocument();

public:
	const std::string& GetLine(int lineNo);
	int GetLineNo(const std::string text);

	void InsertLine(int lineNo, std::string text);
	int Size();

private:
	std::vector<TLine*> m_Lines;
};

class CFileProxy
{

public:
	CFileProxy(std::string filename);
	~CFileProxy(void);

public:
	int GetLineNo(const std::string text);
	const std::string& GetLine(int lineNo);

	void SeekToBegin();
	void SeekToNext();
	void SeekToEnd();
	bool IsEnd();
	const std::string GetCurrentLine();

private:
	BOOL Load(std::string filename);

private:
	TDocument m_Document;
	int m_iIndicator;	//指示器（即当前行号，从1开始）
};
