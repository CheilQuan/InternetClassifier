#ifndef _BAYESALGORITHM_H_
#define _BAYESALGORITHM_H_

#include "DataStructDef.h"
#include "MacroDef.h"

typedef unsigned int uint;

class CBayesAlgorithm 
{
public:
  CBayesAlgorithm(void);
  ~CBayesAlgorithm(void);
 
  virtual void clearTrainingData() = 0;

  float calcProbablity(const float &aTatalNum, const float &aTargetNum); //������ʣ�aTargetNum/aTatalNum��;
  void calcClassifyRate();  //�������ɹ�����;
  
  void clearClassifyData();
  float getTrafficTypeRate(int aX) const;
  uint getClassifyResultArray(int aX, int aY) const;
  uint getTrafficType(int aX) const;
  void setClassifyResultRateArray(const int &aX, const int &aY, const float &aProbablity);
  float getClassifyResultRateArray(int aX, int aY) const;

  static int getClassifyTimes();

protected:
  uint m_TrafficType[ETT_ALL_TYPE + 1];  //ͳ�Ƹ�����������������������;
  float m_TrafficTypeRate[ETT_ALL_TYPE + 1]; //ͳ�Ƹ������������������ĸ��ʵ�����;
  uint m_ClassifyResultArray[TRAFFIC_TYPE_NUM_O][TRAFFIC_TYPE_NUM_C]; //��������ԭʼ���ͷ��ൽ�����͵��������������;
  float m_ClassifyResultRateArray[TRAFFIC_TYPE_NUM_O][TRAFFIC_TYPE_NUM_C];  //��������ԭʼ���ͷ��ൽ�����͵ĸ��ʣ��������;

  DEFSETGET(AttriNum, int, protected); //��������;
  DEFSETGET(isClassifyResultEmpty, bool, protected);   //�������Ƿ�Ϊ��;

  static int m_ClassifyTimes;   //��ǵ�ǰ�ǵڼ��η���Ľ��;
};

#endif