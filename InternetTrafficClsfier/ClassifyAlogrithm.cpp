#include "ClassifyAlgorithm.h"
#include "Container.h"
#include "debug_new.h"
#include "MyString.h"
#include <assert.h>

CStatisticBayes::CStatisticBayes(void)
  : m_AllTypeAttri(NULL),
    m_AllTypeAttriRate(NULL)
{

}

CStatisticBayes::~CStatisticBayes(void)
{
  if (m_AllTypeAttri == NULL)
  {
    return;
  }
  clearTrainingData();  
}

void CStatisticBayes::calcStatisticRate()
{
  calcTrainingRate();
}

void CStatisticBayes::calcTrainingRate()  
{
  for (int trafficType = 0; trafficType <= ETT_ALL_TYPE; ++trafficType)
  {
    float totalTrafficNum = m_TrafficType[ETT_ALL_TYPE];
    float targetNum = m_TrafficType[trafficType];
    float resultRate = calcProbablity(totalTrafficNum, targetNum);

    m_TrafficTypeRate[trafficType] = resultRate;
    totalTrafficNum = m_TrafficType[trafficType];
    for (int attriIdx = 0; attriIdx < m_AttriNum; ++attriIdx)
    {
      std::map<CMyString, unsigned int>::iterator itor 
           = m_AllTypeAttri[trafficType][attriIdx]->getMyData()->begin();
      for (; itor !=m_AllTypeAttri[trafficType][attriIdx]->getMyData()->end(); ++itor)
      {
         resultRate = calcProbablity(totalTrafficNum, itor->second);
         m_AllTypeAttriRate[trafficType][attriIdx]->insert(itor->first, resultRate);
      }
    }
  }
}

void CStatisticBayes::classifyData(const CMyString *aDataArray, int aArraySize, const ETrafficType aTrafficType)
{
  if (NULL == aDataArray || 0 == aArraySize || aTrafficType > ETT_ALL_TYPE)
  { return;}

  float MaxProbablity = 0.0f;       //�����������;
  int ClassifyResult = ETT_ERR_TYPE;  //������;
  //��ʼ����;
  for (int TrafficTypeIdx = 0; TrafficTypeIdx < ETT_ALL_TYPE; ++TrafficTypeIdx)
  { 
    double tempProbablity = m_TrafficTypeRate[TrafficTypeIdx]; //���ڼ��������ʵ���ʱ����;
    for (int AttriIdx = 0; AttriIdx < m_AttriNum; ++AttriIdx)
    {
      tempProbablity *= m_AllTypeAttriRate[TrafficTypeIdx][AttriIdx]->find(aDataArray[AttriIdx]);
      if (tempProbablity == 0.0f)
      { continue;}
    }
    if (tempProbablity > MaxProbablity)
    {
      MaxProbablity = tempProbablity;
      ClassifyResult = TrafficTypeIdx;
    }
  }
  
  //�����������ʼ�洢;
  m_ClassifyResultArray[aTrafficType][ClassifyResult] += 1; //ԭʼ����aTrafficType�ֵ��������ClassifyResult������;
  m_ClassifyResultArray[aTrafficType][ETT_ALL_TYPE] += 1;   //ԭʼ��������;
}


bool CStatisticBayes::statisticAllTypeAttri(const ETrafficType aTrafficType, const uint &aAttri, const CMyString &aKey)
{
  if (aKey.getStrSize() == 0 && aAttri >= m_AttriNum)
  {
    return false;
  }

  m_AllTypeAttri[aTrafficType][aAttri]->insert(aKey, 1);
  
  return true;
}

bool CStatisticBayes::statisticTrafficType(const ETrafficType aTrafficType)

{
  if (aTrafficType >= ETT_ALL_TYPE)
  { return false;}

  m_TrafficType[ETT_ALL_TYPE] += 1;
  m_TrafficType[aTrafficType] += 1;

  return true;
}

void CStatisticBayes::mallocMemory4AllTypeAttri(const int aSize)
{
  assert(aSize > 0);
  clearTrainingData();
  //m_AllTypeAttri[��������][����][���Եķ���ֵ]; 
  //m_AllTypeAttriRate[��������][����][���Եķ���ֵ�ĸ���]; 
  m_AttriNum = aSize;
  m_AllTypeAttri = new CContainer<CMyString, uint> **[ETT_ALL_TYPE + 1];
  m_AllTypeAttriRate = new CContainer<CMyString, float> **[ETT_ALL_TYPE + 1];

  for (int EttIdx = 0; EttIdx <= ETT_ALL_TYPE; ++EttIdx)
  {
    m_AllTypeAttri[EttIdx] = new CContainer<CMyString, uint>*[aSize];
    m_AllTypeAttriRate[EttIdx] = new CContainer<CMyString, float>*[aSize];
    for (int idx = 0; idx < aSize; ++idx)
    {
      ETrafficType loop = static_cast<ETrafficType>(idx);
      m_AllTypeAttri[EttIdx][loop] = new CContainer<CMyString, uint>;
      m_AllTypeAttriRate[EttIdx][loop] = new CContainer<CMyString, float>;
    }
  }
}

//��ȡ���Ա�����Ľӿں���;

CContainer<CMyString, float> ***CStatisticBayes::getAllTypeAttriRate() const
{
  return m_AllTypeAttriRate;
}

CContainer<CMyString, uint> ***CStatisticBayes::getAllTypeAttri() const
{
  return m_AllTypeAttri;
}

//��������������;
void CStatisticBayes::clearAll()
{
  if (m_AttriNum != 0)
  {
    clearClassifyData();
  }
  if (!m_isClassifyResultEmpty)
  {
    clearTrainingData();
  }
}
void CStatisticBayes::clearTrainingData()
{
  if (m_AllTypeAttri == NULL)
  {
    return;
  }
  for (int EttIdx= 0; EttIdx <= ETT_ALL_TYPE; ++EttIdx)
  {
    m_TrafficType[EttIdx] = 0;
    m_TrafficTypeRate[EttIdx] = 0;
    for (int idx = 0; idx < m_AttriNum; ++idx)
    {
      delete m_AllTypeAttri[EttIdx][idx];
      delete m_AllTypeAttriRate[EttIdx][idx];
    }
    delete []m_AllTypeAttri[EttIdx];
    delete []m_AllTypeAttriRate[EttIdx];
  }
  delete []m_AllTypeAttri;
  delete []m_AllTypeAttriRate;

  m_AllTypeAttri = NULL;
  m_AllTypeAttriRate = NULL;
}
