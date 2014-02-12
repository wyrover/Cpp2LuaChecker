/********************************************************************
	created:	2014/2/12  15:57
	file base:	StringUtil
	file ext:	h
	author:		VyronLee
	
	purpose:	×Ö·û´®¹¤¾ß¼¯
*********************************************************************/

#ifndef __StringUtil_H__
#define __StringUtil_H__

#include <string>
using namespace std;

class StringUtil
{
public:
	static string::size_type NPos;

public:
	static BOOL StartWith(const char* src,const char* dst)
	{
		while ( *src != '\0' && *dst != '\0'&& *src++ == *dst++){}
		return *dst == '\0';
	}

	static BOOL StartWith(const string& src, const string& dst)
	{
		return StartWith(src.c_str(), dst.c_str());
	}

	static BOOL EndWith(const char* src, const char* dst)
	{
		int dtSrc = Size(src);
		int dtDst = Size(dst);

		while ( *(src+dtSrc) == *(dst+dtDst) && --dtSrc>0 && --dtDst>0) {}
		
		return dtSrc>=0 && dtDst<0;
	}

	static BOOL EndWith(const string& src, const string& dst)
	{
		return EndWith(src.c_str(), dst.c_str());
	}

	static int Size(const char* str)
	{
		int size=0;
		while ( *str++ != '\0' )
			++size;
		return size;
	}

	static string Left(const string& src, const string& endstr)
	{
		string::size_type pos = src.rfind(endstr);
		string::size_type endpos = pos==string::npos ? src.length()-1 : pos-1;
		return string(src, 0, endpos+1);
	}

	static string Right(const string&src, const string& startstr)
	{
		string::size_type pos = src.find(startstr);
		string::size_type startpos = pos==string::npos ? 0 : pos+startstr.length();
		return string(src, startpos, src.length()-startpos);
	}

	static BOOL IsBlank(const string& str)
	{
		for ( string::size_type i=0; i<str.length(); ++i )
		{
			if ( !IsBlank(str[i])  )
			{
				return FALSE;
			}
		}
		return TRUE;
	}

	static BOOL IsBlank(const char& ch)
	{
		return ch == ' ' || ch == '\t' || ch == '\n'; 
	}

	static int Find(const string& src, const string& dst)
	{
		return src.find(dst);
	}

	static int ReverseFind(const string& src, const string& dst)
	{
		return src.rfind(dst);
	}
};

string::size_type StringUtil::NPos = string::npos;

#endif // __StringUtil_H__