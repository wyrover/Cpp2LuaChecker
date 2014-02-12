#pragma once
#include "isyntaxanalysis.h"

class CSyntaxAnalysis :
	public ISyntaxAnalysis
{
public:
	CSyntaxAnalysis(void);
	~CSyntaxAnalysis(void);

public:
	virtual TiXmlDocument* ParseHeader(std::string headerfile);
	virtual TiXmlElement* GetFunctionInLine(std::string line);
	

private:
	TiXmlDocument* CreateDocumentFrame(std::string headerfile);
	BOOL IsSyntaxIgnore(std::string line);

};
