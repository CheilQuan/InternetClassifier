#ifndef _MYSTRING_H_
#define _MYSTRING_H_
#include "MacroDef.h"

const int MAX_STR_LEN = 1000;  //string����󻺴��С;
const int PRIMER_STR_LEN = 8;  //��ʼ�ַ�������;
class CMyString
{
public:
  CMyString();
  CMyString(const char *aStr);
  CMyString(const CMyString &aStr);
  ~CMyString(void);
  
  bool operator()(const CMyString &aStr1, const CMyString &aStr2) const;
  bool operator<(const CMyString &aStr) const;
  CMyString &operator=(const CMyString &aStr);
  CMyString &operator=(const char *aStr);
  bool operator==(const char *aStr) const;
  bool operator==(const CMyString &aStr) const;
  bool append(const char *aStr);  //���ַ�������׷���ַ�;
  bool append(const char aChar);
  int calcStrValue(const char *aStr = NULL) const;   //����str����ֵ;
//  int calcStrValue(const CMyString &aStr) const;
  void clearData(); //���m_Data���������;
  bool empty() const;
private:
  bool covery(const char *aStr);  //�����ַ���������ǰ���ַ���;
  char *resizeBuf(const int &aNeedStrLen);  //���·���m_Buf�Ĵ�С;
  
  DEFSETGET(BufSize, int, private); //string����ܿռ��С;
  DEFSETGET(StrSize, int, private); //string���ѱ�����ַ�����С;
  DEFSETGET(Buf, char *, private);  //string��Ļ����ַ����Ŀռ�;
};


#endif
