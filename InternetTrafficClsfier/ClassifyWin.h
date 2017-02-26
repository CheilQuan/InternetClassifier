#ifndef CLASSIFYWIN_H
#define CLASSIFYWIN_H

#include "FileOperator.h"
#include "DataStructDef.h"
#include <QWidget>
#include <QButtonGroup>
#include <QCheckBox>
#include <QLineEdit>
#include <QMovie>
#include <QLabel>
        
class Ui_CClassifyWin;
class CWaitDialog;
class CClassifyWin : public QWidget
{
    Q_OBJECT

public:
    explicit CClassifyWin(QWidget *parent = 0);
    ~CClassifyWin();

    bool showPathInLineEdit(QLineEdit *aLineEdit, const char *aPath);

public slots:
    void slot_clickedCheckBox() const;

    void slot_openTrainingSet(bool);
    void slot_openClassifySet(bool);
    void slot_beginClassify(bool);
    void slot_beginTraining(bool);
    void slot_operateFinished(EOperateFlag aFlag);

private:
    void findOutAllCheckedBox();     //�ҳ����еı���ѡ��CheckBox������¼���ǵ����Ժ�;
    bool recordChoosedCheckBox(/*const */QCheckBox *checkBox, int &idx);  //���ָ��CheckBox�Ƿ񱻹�ѡ,����ѡ���¼��������;
    void addAllCheckBox2Group() const;  //�����е�����CheckBox���뵽ButtonGroup�У�����Ե���¼����в���;
    bool savePath(QLineEdit *aLineEdit);
   
    char *QString2ToStr(QString &aQStr) ;

    void test(); //���ڲ���ĳЩ����
signals:
    void signal_SendData(SDataPack aDataPack);   //�������ݰ����ź�;
private:
    Ui_CClassifyWin *m_Ui;
    QButtonGroup *m_CheckBoxGroup;
    
    DEFSETGET(AllCheckedBox, unsigned short *, private); //��ѡ��checkbox�����;
    DEFSETGET(CheckedBoxNum, unsigned short, private);   //���еĹ�ѡ��checkBox����;
    DEFSETGET(FileOperator, CFileOperator *, private);
    
    bool m_IsTrained; //��־�Ƿ��Ѿ�ѵ������;
    char *m_destPath;   //��ʱ������Ҫ���ݵ�·��;
    QThread *m_WorkThread;    //���ݴ����߳�;
    CWaitDialog *m_waitDialog;  //�ȴ���ʾ��;
};

#endif // CLASSIFYWIN_H
