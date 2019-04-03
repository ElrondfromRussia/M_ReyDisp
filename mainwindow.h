#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QLabel>
#include <QPixmap>
#include <QPushButton>
#include <QBoxLayout>
#include <QMouseEvent>
#include <QComboBox>
#include <QSerialPortInfo>
#include <QTimer>
#include <QSystemTrayIcon>
#include <QMenu>
#include <QApplication>
#include <QSettings>
#include <QDir>
#include <QDebug>
#include <QListWidget>
#include <QFileDialog>
#include <QMap>
#include <QException>
#include <QMessageBox>
#include <QProcess>

#include <cstddef>

#define GET_ALL "tasklist"
#define ID_DEL "taskkill  /Pid "

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

public slots:
    void timerMainShot();
    void iconActivated(QSystemTrayIcon::ActivationReason reason);
    void delete_el();
    void add_someth();
    void fill_list();
    void show_reestr();
    void show_disp();

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
