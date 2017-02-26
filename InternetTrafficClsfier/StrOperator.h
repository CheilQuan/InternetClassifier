#ifndef _STROPERATOR_H_
#define _STROPERATOR_H_

#include "DataStructDef.h"
#include "SingleTon.h"
/*****************************
��˵�����ַ��������ࣨ�����ࣩ;

*****************************/
class CStrOperator : public CSingleTon<CStrOperator>
{
public:
  CStrOperator(void);
  ~CStrOperator(void);
  
  int str2int(const char *aStr);
  float str2float(const char *aStr);
  bool str2bool(const char *aStr);
  unsigned short str2ushort(const char *aStr);

};


#endif
