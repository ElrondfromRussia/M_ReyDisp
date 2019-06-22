#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include <my_page.h>
#include <reestr_page.h>
#include <disp_page.h>


namespace Ui {
class MainWindow;
}

class MainWindow : public QLabel
{
    Q_OBJECT
    QPoint m_ptPosition;
    QPushButton *quitbtn;
    QPushButton *delbtn;
    QPushButton *addbtn;
    QPushButton *updbtn;
    QPushButton *Rbtn;
    QPushButton *Dbtn;
    QVBoxLayout *bxlay;
    QHBoxLayout *butlay;
    QTimer mtimer;
    QSystemTrayIcon* trayIcon;
    QListWidget* mlist;
    QListWidget* dlist;
    QModelIndex curr_ind;
    QMap<QString, QString> progsmap;
    QMap<QString, QString> dispsmap;
    int prstate;

    My_Page* m_page;
    Reestr_Page* r_page;
    Disp_Page* d_page;

public slots:
    void timerMainShot();
    void iconActivated(QSystemTrayIcon::ActivationReason reason);
    void show_reestr();
    void show_disp();

    void add_item();
    void delete_item();
    void fill();

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    void closeEvent(QCloseEvent* event);
    virtual void mousePressEvent(QMouseEvent *pe)
    {
        m_ptPosition = pe->pos();
    }
    virtual void mouseMoveEvent(QMouseEvent *pe)
    {
        move(pe->globalPos() - m_ptPosition);
    }


};

#endif // MAINWINDOW_H
