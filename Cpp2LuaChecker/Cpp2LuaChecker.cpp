// Cpp2LuaChecker.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "VrGrep.h"
#include <iostream>
#include <fstream>


int _tmain(int argc, _TCHAR* argv[])
{
	VrGrep grep;
	SVrGrepResult result = grep.FindOne("Actor", "D:\\NProject\\trunk\\Bin\\Client\\Data\\UI\\lua\\Country*.*", &std::cout);

	system("pause");

	return 0;
}

