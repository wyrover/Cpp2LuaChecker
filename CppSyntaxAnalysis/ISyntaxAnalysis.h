#ifndef __ISYNTAXANALYSIS_H__
#define __ISYNTAXANALYSIS_H__

#include <string>
#include "tinyxml/tinyxml.h"

class ISyntaxAnalysis
{
public:
	virtual TiXmlDocument* ParseHeader(std::string headerfile) = NULL;
	virtual TiXmlElement* GetFunctionInLine(std::string line) = NULL;
};


#endif