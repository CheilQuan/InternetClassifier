#ifndef _FILEOPERATOR_H_
#define _FILEOPERATOR_H_

#include <fstream>
#include <iostream>
#include <vector>
#include <QObject>
#include "MacroDef.h"  
#include "DataStructDef.h"

typedef unsigned int uint;
typedef unsigned short ushort;

class CMyString;
class CStatisticBayes;

class CFileOperator : public QObject
{
  Q_OBJECT
public:
  CFileOperator(QObject *aParent = 0);
  ~CFileOperator(void);

private:
  CFileOperator(const CFileOperator &);
  CFileOperator &operator=(const CFileOperator &);

public:
  void statisticData();
  bool operateTrainingFile(ushort *aSrcArray, const int &aSize, const char *aFilePath = NULL); //aFilePathΪ�����ļ���·��,aSrcArrayΪ��ѡ������ֵ��aSizeΪ����ֵ����;

  bool operateClassifyFile(const char *aFilePath = NULL); //aFilePathΪ�����ļ���·��,aSrcArrayΪ��ѡ������ֵ��aSizeΪ����ֵ����;
  bool setAttriPosArray(std::ifstream &aMyFile, ushort *aSrcArray, const int &aSize);
  const std::vector<ushort> &getAttriPos();

public slots:
  void slot_operateFile(SDataPack aDataPack);

protected:
  bool getTrafficType(const char *aBuf, CMyString &aTrafficType) const;
  CMyString &sliceStr(const char *aSrc, CMyString &aDest, const char aChar, bool aIsNeedTheData);//aCharΪ�ָ���, aIsNeedTheDataΪ�Ƿ���Ҫ�����ݵı�־;
  EPickOutAttriResult pickOutAttriNum(const char *aStr, ushort &aTargetNum);  //ѡ����Ҫ����������λ��;
  ETrafficType str2Enum(const CMyString &aStr);

signals:
  void signal_operateFinished(EOperateFlag aFlag);

  DEFSETGET(PrePointer, char *, private); //m_prePointer���ڱ��浱ǰָ��λ��;
  DEFSETGET(StrBuf, char *, private); //m_StrBuf���ڻ�����ĵ��ж�ȡ��һ������;
  DEFSETGET(FilePath, char *, private);   //�ļ�·��;

private:
  static short m_AttriNum; //����ֵ�ĸ���;
  static std::vector<ushort> m_AttriPos; //�洢����ֵ��λ��;
};



#endif
