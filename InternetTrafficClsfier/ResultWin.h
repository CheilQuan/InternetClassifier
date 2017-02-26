#ifndef RESULTWIN_H
#define RESULTWIN_H

#include <QWidget>
#include "ui_ResultWin.h"

class CResultWin : public QWidget
{
    Q_OBJECT
public:
  enum EShowResultType //������ʾ�������͵Ľ��;
  {
    ESRT_Probablity,  //������;
    ESRT_Number,      //��ֵ��;
  };
public:
    CResultWin(EShowResultType aType = ESRT_Probablity, QWidget *parent = 0);
    ~CResultWin();

    void showClassifyResult(EShowResultType aType);
    void showProbablity(int &aColumn, int &aRow);
    void showNumber(int &aColumn, int &aRow);

private:
    Ui::CResultWin ui;
};

#endif // RESULTWIN_H
