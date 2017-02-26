#ifndef _CLASSIFYALOGRITHM_H_
#define _CLASSIFYALOGRITHM_H_

#include <vector>
#include "SingleTon.h"
#include "BayesAlgorithm.h"

class CMyString;
template<class Key, class Value> class CContainer;

/******************************************
��˵����ͳ�Ʒ���Ҷ˹�㷨�࣬ͳ�����ݰ��и������������͡������Ͷ�Ӧ�����Ե�ֵ�ȣ�Ȼ�����ڼ���������ķ���;
*******************************************/
class CStatisticBayes : public CSingleTon<CStatisticBayes>, public CBayesAlgorithm
{
public:
  CStatisticBayes(void);
  ~CStatisticBayes(void);

private:
  CStatisticBayes(const CStatisticBayes &){}
  CStatisticBayes &operator=(const CStatisticBayes &){}

public:
  void calcStatisticRate();
  void calcTrainingRate();    //����ʹ��ͳ�Ʒ��õ������ݵĸ���;
  void classifyData(const CMyString *aDataArray, int aArraySize, const ETrafficType aTrafficType);  //ʹ��ͳ�Ʒ�����;
  bool statisticAllTypeAttri(const ETrafficType aTrafficType, const uint &aAttri, const CMyString &aKey);   //ͳ�Ƹ������������͵Ķ�Ӧ���Ը�ֵ���ִ���;
  bool statisticTrafficType(const ETrafficType aTrafficType); //ͳ������������������;
  void mallocMemory4AllTypeAttri(const int aSize);

 CContainer<CMyString, float> ***getAllTypeAttriRate() const;
  CContainer<CMyString, uint> ***getAllTypeAttri() const;
  
  //��������������;
  void clearAll();
  void clearTrainingData();

private:
  CContainer<CMyString, uint> ***m_AllTypeAttri; //ͳ�����������������͸��Զ�Ӧ�ĸ����Ե�ֵ����;
  CContainer<CMyString, float> ***m_AllTypeAttriRate; //ͳ�����������������͸��Զ�Ӧ�ĸ����Ե�ֵ�����ĸ���;
};

/******************************************
��˵������̬�ֲ�����Ҷ˹�㷨�࣬ͳ�����ݰ��и������������������������Ͷ�Ӧ�����Ե�ֵ�ĳ��ִ����ľ�ֵ������ȣ�Ȼ�����ڼ���������ķ���;
*******************************************/
class CGuassianBayes : public CSingleTon<CGuassianBayes>, public CBayesAlgorithm
{
public:
protected:
private:
};




#endif
