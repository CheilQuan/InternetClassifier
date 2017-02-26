#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QTabWidget>

class CClassifyWin;
class Ui_CMainWindow;
class CTabWidget;

class CMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    CMainWindow(QWidget *parent = 0);
    ~CMainWindow();
private:  //��ֹ�����͸�ֵ;
    CMainWindow(const CMainWindow &){}
    CMainWindow &operator=(const CMainWindow &){}

public:
    void initLocalVar();  //��ʼ����Ա����,������InitConnect()֮ǰ����;
    void initConnect() const;  //��ʼ���źźͲ۵�����;
    
    void initStatusBar();

public slots:
    void slot_clickClsBegin();
    void slot_clickRltShowProbablity();
    void slot_clickRltShowNum();
    void slot_exit();
private:
    Ui_CMainWindow *m_ui;
};

#endif // MAINWINDOW_H
