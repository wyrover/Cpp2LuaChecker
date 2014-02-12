#pragma once

#include <ostream>
#include <vector>
#include <string>

#define INVALID_LINE_NO -1

typedef struct tagVrGrepResult
{
	int lineNo;					//�кţ�-1��ʾ���Ҳ���
	std::string lineText;		//��Ӧ���ı�
	std::string fileName;		//��Ӧ�ļ���
	std::string fileDirectory;	//��Ӧ�ļ�Ŀ¼

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
	// Parameter: std::string text	�������ı������ִ�Сд��ȫƥ��
	// Parameter: std::string path	����·����֧��ͨ��
	// Parameter: std::ostream * pOut	���������Ϣ
	// Purpose: ����������ı���ָ��·���в���ƥ�����������ƥ�����б�
	//************************************
	SVrGrepResultList Find(std::string text, std::string path, std::ostream* pOut=NULL);	

	//************************************
	// Method:    FindOne
	// FullName:  VrGrep::FindOne
	// Access:    public 
	// Returns:   SVrGrepResult
	// Qualifier:
	// Parameter: std::string text	�������ı������ִ�Сд��ȫƥ��
	// Parameter: std::string path  ����·����֧��ͨ��
	// Parameter: std::ostream * pOut	���������Ϣ
	// Purpose: ����������ı���ָ��·���в���ƥ����ҵ���ֹͣ�������׸�ƥ����
	//************************************
	SVrGrepResult FindOne(std::string text, std::string path, std::ostream* pOut=NULL);

private:
	//************************************
	// Method:    FindInDirectory
	// FullName:  VrGrep::FindInDirectory
	// Access:    private 
	// Returns:   SVrGrepResultList
	// Qualifier:
	// Parameter: std::string text	�������ı������ִ�Сд��ȫƥ��
	// Parameter: std::string directory	����Ŀ¼
	// Parameter: std::string fileRegExp	���ҵ��ļ�ͨ���ַ���
	// Parameter: std::ostream * pOut	���������Ϣ
	//************************************
	SVrGrepResultList FindInDirectory(std::string text, std::string directory, std::string fileExp, std::ostream* pOut=NULL);


	//************************************
	// Method:    FindInFile
	// FullName:  VrGrep::FindInFile
	// Access:    private 
	// Returns:   SVrGrepResultList
	// Qualifier:
	// Parameter: std::string text �������ı������ִ�Сд��ȫƥ��
	// Parameter: std::string fileName	�ļ�·����
	// Parameter: std::ostream * pOut	���������Ϣ
	//************************************
	SVrGrepResultList FindInFile(std::string text, std::string fileName, std::ostream* pOut=NULL);

	//************************************
	// Method:    FindInDirectory
	// FullName:  VrGrep::FindInDirectory
	// Access:    private 
	// Returns:   SVrGrepResultList
	// Qualifier:
	// Parameter: std::string text	�������ı������ִ�Сд��ȫƥ��
	// Parameter: std::string directory	����Ŀ¼
	// Parameter: std::string fileRegExp	���ҵ��ļ�ͨ���ַ���
	// Parameter: std::ostream * pOut	���������Ϣ
	//************************************
	SVrGrepResult FindOneInDirectory(std::string text, std::string directory, std::string fileExp, std::ostream* pOut=NULL);

	//************************************
	// Method:    FindInFile
	// FullName:  VrGrep::FindInFile
	// Access:    private 
	// Returns:   SVrGrepResultList
	// Qualifier:
	// Parameter: std::string text �������ı������ִ�Сд��ȫƥ��
	// Parameter: std::string fileName	�ļ�·����
	// Parameter: std::ostream * pOut	���������Ϣ
	//************************************
	SVrGrepResult FindOneInFile(std::string text, std::string fileName, std::ostream* pOut=NULL);
};