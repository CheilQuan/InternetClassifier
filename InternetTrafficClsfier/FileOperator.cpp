#include "FileOperator.h"
#include "StrOperator.h"
#include "ClassifyAlgorithm.h"
#include "MyString.h"
#include "debug_new.h"
#include <assert.h>

const CMyString INTERNET_TRAFFIC_TYPE[9] = {"WWW", "FTP", "MAIL", "P2P", 
                                            "ATTACK", "DATABASE", "SERVIES", 
                                            "INTERACTIVE", "MULTIMEDIA"};

std::vector<unsigned short> CFileOperator::m_AttriPos;
short CFileOperator::m_AttriNum = 0;
CFileOperator::CFileOperator(QObject *aParent)
  : m_PrePointer(NULL),
    m_StrBuf(new char[BUF_SIZE]),
    m_FilePath(NULL)
{
  qRegisterMetaType<SDataPack>("SDataPack");
  qRegisterMetaType<EOperateFlag>("EOperateFlag");
  memset(m_StrBuf, 0, BUF_SIZE);
  
}

CFileOperator::~CFileOperator(void)
{
  IF_NOT_NULL_DELETE_a(m_StrBuf);
  IF_NOT_NULL_DELETE_a(m_FilePath);
  IF_NOT_NULL_DELETE_a(m_PrePointer);
  CStatisticBayes::destroyInstance();
}

CMyString &CFileOperator::sliceStr(const char *aSrc, CMyString &aDest, const char aChar, bool aIsNeedTheData)
{
  if (aSrc == NULL)
  { return aDest;}

  m_PrePointer = const_cast<char *>(aSrc);
  int idx = 0;
  bool isFloat = false;
  if (aIsNeedTheData)
  {
    while ((*m_PrePointer) != aChar && (*m_PrePointer) != '\0')
    {
      if ((*m_PrePointer) == ' ') //ȥ���ո�;
      {
        m_PrePointer++;
        continue;
      }
      if ((*m_PrePointer) == '.') //����С����ʵ�������ͱ�����ɢ��;
      {
        for (int loop = 0; loop < idx; ++loop)  
        {
          if (aDest.getBuf()[loop] != '0')//С����ǰ�з���������ֱ�ӷ���;
          {
            return aDest;
          }
        }
        isFloat = true;
      }

      aDest.append(*m_PrePointer); //�浱ǰ�ַ�;
      if (isFloat && *m_PrePointer > '0' && *m_PrePointer <= '9')
      {
        return aDest; //С�������ֵ�һ��������,�ͷ���;
      }
      m_PrePointer++;
      idx++;
    }
  }
  else
  {
    while ((*m_PrePointer) != aChar && (*m_PrePointer) != '\0')
    {
      m_PrePointer++;
    }
  }

  if (*m_PrePointer == aChar)
  {
    m_PrePointer++;
  }

  return aDest;
}

bool CFileOperator::setAttriPosArray(std::ifstream &aMyFile, ushort *aSrcArray, const int &aSize)
{
  if (aSrcArray == NULL || aSize <= 0)
  {
    return false;
  }
  
  m_AttriNum = aSize;
  while ((*aSrcArray) == 0)
  {
    aSrcArray++;
  }

  ushort currentPos = 0;
  int savedNum = 0;
  m_AttriPos.clear();
  while (!aMyFile.eof())
  {
    memset(m_StrBuf, 0, BUF_SIZE);
    aMyFile.getline(m_StrBuf, BUF_SIZE);

    //����������ֵ;
    bool isPickOutAttri = false;
    if (m_StrBuf[0] == '@')
    {
      EPickOutAttriResult reslt = pickOutAttriNum(m_StrBuf, (*aSrcArray));
      if (EPOAR_IsTarget == reslt)
      {
        m_AttriPos.push_back(currentPos);
        ++aSrcArray;
        ++savedNum;
        ++currentPos;
        if (savedNum == aSize)  //��Ҫ���������ֵλ�ñ������;
        { return true;}
      }
      else if (EPOAR_IsNum == reslt)
      {
        ++currentPos;
      }
    }
  }
  return false;
}

EPickOutAttriResult CFileOperator::pickOutAttriNum(const char *aStr, ushort &aTargetNum)
{
  if (aStr == NULL)
  { return EPOAR_NotNum;}

  //����������ֵ,ȥ��@attribute,���º����ֵ;
  if (aStr[0] == '@')
  {
    int idx = 1;
    while ((aStr[idx] < '0' || aStr[idx] > '9') && aStr[idx] != '\0')
    {
      idx++;
    }
    if (aStr[idx] >= '0' && aStr[idx] <= '9')
    {
      int tempNum = CStrOperator::getInstance()->str2ushort(&aStr[idx]);
      if (tempNum > 0 && tempNum == aTargetNum)
      {
        return EPOAR_IsTarget;
      }
      else if (tempNum > 0)
      {
        return EPOAR_IsNum;
      }
    }
  }
  return EPOAR_NotNum;
}

const std::vector<unsigned short> &CFileOperator::getAttriPos()
{
  return m_AttriPos;
}

void CFileOperator::statisticData()
{

}

bool CFileOperator::operateTrainingFile(ushort *aSrcArray, const int &aSize, const char *aFilePath)
{
  const char *myFilePath = aFilePath ? aFilePath : m_FilePath; 
  if (myFilePath == NULL)
  { return false;}

  CStatisticBayes::getInstance()->clearTrainingData(); //ÿ�ν���ͳ������ǰ���������������ľ�����;

  std::ifstream myFile;
  myFile.open(myFilePath);
  if (!myFile.is_open())
  { return false;}
  
  if (!setAttriPosArray(myFile,aSrcArray, aSize))  //��������ֵ��λ��;
  { return false;}

  CStatisticBayes::getInstance()->mallocMemory4AllTypeAttri(aSize);    //Ϊ�������������ڴ�;
  std::vector<ushort>::iterator itor = m_AttriPos.begin();
  while (!myFile.eof())
  {
    memset(m_StrBuf, 0, BUF_SIZE);
    myFile.getline(m_StrBuf, BUF_SIZE);

    m_PrePointer = m_StrBuf;
    
    //����ֵ��ʼ�洢ͳ������;
    if (m_PrePointer[0] >= '0' && m_PrePointer[0] <= '9')
    {
      char *tempPtr = m_StrBuf; 
      CMyString tempTrafficType;
      while (!getTrafficType(tempPtr, tempTrafficType)) //��������ݸ�ʽ���󣬱����ƴ��;
      {
        char temBuf[BUF_SIZE] = {'\0'};
        myFile.getline(temBuf, BUF_SIZE);
        strcat_s(m_StrBuf, BUF_SIZE, temBuf);
        
        tempPtr = temBuf;
      }

      //��ʼͳ������;
      itor = m_AttriPos.begin();
      CMyString tempStr; //������ʱ�洢������ֵ��ı���;
      ushort idx = 0; //��Ӧ����ֵ�洢��λ��;
      ushort curAttriPos = 0; //��ǰ����ֵ��λ��;
      CStatisticBayes::getInstance()->statisticTrafficType(str2Enum(tempTrafficType));
      do  
      {
        tempStr.clearData();
        if (curAttriPos == *itor) //����Ҫ������;
        {
          sliceStr(m_PrePointer, tempStr, ',', true);
          ++itor;
          CStatisticBayes::getInstance()->statisticAllTypeAttri(str2Enum(tempTrafficType), idx, tempStr);
          ++idx;
        }
        else
          sliceStr(m_PrePointer, tempStr, ',', false);
        ++curAttriPos;
      } while (itor != m_AttriPos.end());  //ֱ��ͳ������������ֵ;
    }
  }//����ͳ�ƽ���;

  CStatisticBayes::getInstance()->calcStatisticRate();  //����ͳ�����ݵĸ���;

  m_PrePointer = NULL;
  myFile.close();
  return true;
}

bool CFileOperator::operateClassifyFile(const char *aFilePath /* = NULL */)
{
  if (m_AttriPos.empty())
  { return false;}
  
  const char *myFilePath = aFilePath ? aFilePath : m_FilePath; 
  if (myFilePath == NULL)
  { return false;}

  CStatisticBayes::getInstance()->clearClassifyData(); //ÿ�ν���ͳ������ǰ���������������ľ�����;

  std::ifstream myFile;
  myFile.open(myFilePath);
  if (!myFile.is_open())
  { return false;}

  std::vector<ushort>::iterator itor = m_AttriPos.begin();
  while (!myFile.eof())
  {
    memset(m_StrBuf, 0, BUF_SIZE);
    myFile.getline(m_StrBuf, BUF_SIZE);

    m_PrePointer = m_StrBuf;
  
    //����ֵ��ʼ�洢ͳ������;
    if (m_PrePointer[0] >= '0' && m_PrePointer[0] <= '9')
    {
      char *tempPtr = m_StrBuf; 
      CMyString tempTrafficType;
      while (!getTrafficType(tempPtr, tempTrafficType)) //��������ݸ�ʽ���󣬱����ƴ��;
      {
        char temBuf[BUF_SIZE] = {'\0'};
        myFile.getline(temBuf, BUF_SIZE);
        strcat_s(m_StrBuf, BUF_SIZE, temBuf);

        tempPtr = temBuf;
      }

      //��ʼ��ȡ��Ҫ������;
      itor = m_AttriPos.begin();
      ushort idx = 0; //��Ӧ����ֵ�洢��λ��;
      CMyString *tempDataArray = new CMyString[m_AttriNum];//������ʱ�洢������ֵ�����Ҫ�ı���;
      ushort curAttriPos = 0; //��ǰ����ֵ��λ��;
      do  
      {
        if (curAttriPos == *itor) //����Ҫ������;
        {
          sliceStr(m_PrePointer, tempDataArray[idx], ',', true);
          ++itor;
          ++idx;
        }
        else
          sliceStr(m_PrePointer, tempDataArray[idx], ',', false);
        ++curAttriPos;
      } while (itor != m_AttriPos.end());  //ֱ��ͳ������������ֵ;
      
      CStatisticBayes::getInstance()->classifyData(tempDataArray, m_AttriNum, str2Enum(tempTrafficType)); //��ø������ݵ���������;
      
      delete []tempDataArray;
    }  
  } //�ļ���ȡ����;

  m_PrePointer = NULL;
  myFile.close();
  
  CStatisticBayes::getInstance()->calcClassifyRate();  //����������������;

  return true;
}

bool CFileOperator::getTrafficType(const char *aBuf, CMyString &aTrafficType) const
{
  if (NULL == aBuf)
  { return false;}

  int continueCharNum = 0;    //��ȡ�������ַ�����(�����������������������);
  char tempChar[10] = {'\0'};
  while ((*aBuf) != '\0')
  {
    //�ڶ�������ΪP2P����������;
    if ((*aBuf) <= 'Z' && (*aBuf) >= 'A' || ((*aBuf) == '2' && continueCharNum == 1))
    {
      tempChar[continueCharNum] = *aBuf;
      ++continueCharNum;
    }
    else
    {
      continueCharNum = 0;
    }
    if (continueCharNum == 3)
    {
      aTrafficType = tempChar;
      return true;
    }
    aBuf++;
  }

  return false;
}

ETrafficType CFileOperator::str2Enum(const CMyString &aStr)
{
  for (int idx = 0; idx < 9; ++idx)
  {
    if (INTERNET_TRAFFIC_TYPE[idx] == aStr)
    {
      return static_cast<ETrafficType>(idx);
    }
  }

  return ETT_ERR_TYPE;  
}

void CFileOperator::slot_operateFile(SDataPack aDatPack)
{
  switch (aDatPack.aFlag)
  {
  case EOF_Training:
    if (aDatPack.aFilePath != NULL && aDatPack.aSrcArray != NULL)
    {
      operateTrainingFile(aDatPack.aSrcArray, aDatPack.aSrcArraySize, aDatPack.aFilePath);
      emit signal_operateFinished(EOF_TrainingFinished);
    }
    break;
  case EOF_Classify:
    if (aDatPack.aFilePath != NULL)
    {
      operateClassifyFile(aDatPack.aFilePath);
      emit signal_operateFinished(EOF_ClassifyFinished); 
    }
    break;
  default:
     emit signal_operateFinished(EOF_NULL);
     break;
  }
}