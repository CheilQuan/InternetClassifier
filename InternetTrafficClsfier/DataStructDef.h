#ifndef _DATASTRUCTDE_H_
#define _DATASTRUCTDE_H_
#include <string>
/*****************ö�ٶ���*****************/
enum ECheckBoxOrderNum    //CheckBox�����ö��;
{
  ECBON_CheckBox0 = 4,
  ECBON_CheckBox11 = 8,
  ECBON_CheckBox2 = 50,
  ECBON_CheckBox10 = 60,
  ECBON_CheckBox3 = 72,
  ECBON_CheckBox4 = 91,
  ECBON_CheckBox15 = 170,
  ECBON_CheckBox16 = 190,
  ECBON_CheckBox5 = 108,
  ECBON_CheckBox13 = 210,
  ECBON_CheckBox6 = 113,
  ECBON_CheckBox12 = 220,
  ECBON_CheckBox7 = 155,
  ECBON_CheckBox14 = 230,
  ECBON_CheckBox8 = 202,
  ECBON_CheckBox9 = 250,
};

//WWW,FTP-PASV,SERVICES,INTERACTIVE,MAIL,
//  FTP-CONTROL,DATABASE,P2P,FTP-DATA;
enum ETrafficType   //����������������;
{
  ETT_WWW,          //WWW�����ݰ�;
  ETT_FTP,          //FTP��;
  ETT_MAIL,         //MAIL����;
  ETT_P2P,          //P2P����;
  ETT_ATTACK,       //ATTACK����;
  ETT_DATABASE,     //DATABASE����;
  ETT_SERVICES,     //SERVICES����;
  ETT_INTERACTIVE,  //INTERACTIVE����;
  ETT_MULTIMEDIA,   //MULTIMEDIA����;
  ETT_ERR_TYPE,     //��������;
  ETT_ALL_TYPE,     //������������;
};

enum EPickOutAttriResult  //��ѡ����ֵ�Ľ��;
{
  EPOAR_IsNum,  //�����������ֵ��������Ҫ������ֵ;
  EPOAR_IsTarget, //�������������Ҫ���ҵ�����ֵ;
  EPOAR_NotNum, //����Ĳ�����ֵ;
};

enum EFileReadResult    //��ȡ�ļ��Ľ������;
{
  EFRR_ReadFileSucceed,       //��ȡ�ɹ�;
  EFRR_FilePathIsNull,        //�ļ�·��Ϊ��;
  EFRR_OpenFileFailed,        //���ļ�ʧ��;
  EFRR_NoNecessaryAttri,      //��������Ϊ��;
};

enum EOperateFlag  //��ǲ������ͣ������ļ���ѵ���ļ���;
{
  EOF_Training,   //ѵ�����;
  EOF_Classify,   //������;
  EOF_TrainingFinished, //ѵ������;
  EOF_ClassifyFinished, //�������;
  EOF_NULL, //������;
};

/*****************��������*****************/
const short ATTRI_CHECKBOX_NUM = 16;    //�������Ե�checkbox����;
const int BUF_SIZE = 2048;   //��ȡ�ļ��Ļ����С;
const int TRAFFIC_TYPE_NUM_O = ETT_ALL_TYPE + 1;  //��������ԭʼ��������;
const int TRAFFIC_TYPE_NUM_C = ETT_ALL_TYPE + 1;  //����������������������;
const std::string MY_VERSION = "1.1.160116.beta"; //�򵥰汾��ʶ(ϵͳ�ܹ��䶯.����ģ�����.bug�޸�������ĳ���䶯����.����);

/*****************�ṹ�嶨��***************/
typedef struct _SDataPack
{
  EOperateFlag aFlag;    //���ݰ�����;
  unsigned short *aSrcArray;    //������;
  int aSrcArraySize;      //�������С;
  char *aFilePath;    //�����ļ�·��;

  _SDataPack()
  {
    aFlag = EOF_NULL;
    aSrcArray = 0;
    aSrcArraySize = 0;
    aFilePath = 0;
  }
}SDataPack;

#endif