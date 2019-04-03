#include "mainwindow.h"
#include <QStringListModel>
#include <QListWidgetItem>

MainWindow::MainWindow(QWidget *parent) :
    QLabel(parent)
{
    setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);
    QPixmap pix(":/m_reestr.png");
    setPixmap(pix);

    prstate = 1;

    setFixedSize(pix.size());
    setWindowIcon(QIcon(":/app_icon.png"));

    quitbtn= new QPushButton("");
    quitbtn->setIcon(QIcon(":/exit.png"));
    quitbtn->setFixedSize(20,20);
    QObject::connect(quitbtn, SIGNAL(clicked()), this, SLOT(hide()));
    delbtn= new QPushButton("");
    delbtn->setIcon(QIcon(":/del.png"));
    delbtn->setFixedSize(20,20);
    QObject::connect(delbtn, SIGNAL(clicked()), this, SLOT(delete_el()));
    addbtn= new QPushButton("");
    addbtn->setIcon(QIcon(":/add.png"));
    addbtn->setFixedSize(20,20);
    QObject::connect(addbtn, SIGNAL(clicked()), this, SLOT(add_someth()));
    updbtn= new QPushButton("");
    updbtn->setIcon(QIcon(":/upd.png"));
    updbtn->setFixedSize(20,20);
    QObject::connect(updbtn, SIGNAL(clicked()), this, SLOT(fill_list()));
    Rbtn= new QPushButton("");
    Rbtn->setIcon(QIcon(":/rstr.png"));
    Rbtn->setFixedSize(20,20);
    QObject::connect(Rbtn, SIGNAL(clicked()), this, SLOT(show_reestr()));
    Dbtn= new QPushButton("");
    Dbtn->setIcon(QIcon(":/disp.png"));
    Dbtn->setFixedSize(20,20);
    QObject::connect(Dbtn, SIGNAL(clicked()), this, SLOT(show_disp()));

    butlay = new QHBoxLayout();
    butlay->setMargin(0);
    butlay->setSpacing(5);
    butlay->addWidget(quitbtn);
    butlay->addWidget(addbtn);
    butlay->addWidget(delbtn);
    butlay->addWidget(updbtn);
    butlay->addWidget(Rbtn);
    butlay->addWidget(Dbtn);

    mlist = new QListWidget(this);
    mlist->setFixedSize(180,140);
    mlist->setSelectionMode(QAbstractItemView::SingleSelection);
    mlist->setVisible(true);
    mlist->setFont(QFont("Times", 12, 1));

    dlist = new QListWidget(this);
    dlist->setFixedSize(180,140);
    dlist->setSelectionMode(QAbstractItemView::SingleSelection);
    dlist->setVisible(false);
    dlist->setFont(QFont("Times", 12, 1));

    bxlay = new QVBoxLayout();
    bxlay->addLayout(butlay);
    bxlay->addWidget(mlist);
    bxlay->addWidget(dlist);
    bxlay->setMargin(20);
    bxlay->setSpacing(0);

    setLayout(bxlay);
    bxlay->setGeometry(QRect(0,0, pix.size().width(), pix.size().height()));
    fill_list();

    mtimer.setInterval(10000);
    connect(&mtimer, &QTimer::timeout, this, &MainWindow::timerMainShot);

    trayIcon = new QSystemTrayIcon(this);
    trayIcon->setIcon(QIcon(":/app_icon.png"));
    trayIcon->setToolTip("M_Reestr");

    QMenu *menu = new QMenu(this);
    QAction *viewO = new QAction("Open", this);
    QAction *viewQ = new QAction("Quit", this);

    QObject::connect(viewO,  SIGNAL(triggered()), this, SLOT(show()));
    QObject::connect(viewQ,  SIGNAL(triggered()), this, SLOT(close()));

    menu->addAction(viewO);
    menu->addAction(viewQ);

    trayIcon->setContextMenu(menu);
    trayIcon->show();
    QObject::connect(trayIcon,  SIGNAL(activated(QSystemTrayIcon::ActivationReason)), this, SLOT(iconActivated(QSystemTrayIcon::ActivationReason)));
}

MainWindow::~MainWindow()
{

}

void MainWindow::fill_list()
{
    if(prstate == 1)
    {
        mlist->clear();
        progsmap.clear();
        QStringList list;
        QSettings settings("HKEY_CURRENT_USER\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run", QSettings::NativeFormat);
        foreach(QString st, settings.allKeys())
        {
            list.append(st);
            progsmap.insert(progsmap.begin() + progsmap.size(), st,
                            "HKEY_CURRENT_USER\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run");
        }
        QSettings settings1("HKEY_LOCAL_MACHINE\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run", QSettings::NativeFormat);
        foreach(QString st, settings1.allKeys())
        {
            list.append(st);
            progsmap.insert(progsmap.begin() + progsmap.size(), st,
                            "HKEY_LOCAL_MACHINE\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run");
        }
        mlist->insertItems(0, list);
        mlist->sortItems();
    }
    else
    {
        dlist->clear();
        dispsmap.clear();

        QProcess* proc = new QProcess();
        proc->start(GET_ALL);
        proc->waitForFinished();
        QString str(proc->readAllStandardOutput());
        QStringList list;
        QStringList listres;
        list.append(str.split("\r"));
        if(list.size() > 6)
        {
            list.removeAt(0);
            list.removeAt(0);
            list.removeAt(0);
            list.removeAt(0);
            list.removeAt(0);
            list.removeAt(list.size() - 1);
        }

        foreach(QString sss,  list)
        {
            QStringList buf;
            sss.remove("\n");
            buf.append(sss.split(QRegularExpression("\\s+")));
            listres.append(QString(buf.at(0)));
            dispsmap.insert(dispsmap.begin() + dispsmap.size(), buf.at(0), buf.at(1));
        }

        dlist->insertItems(0, listres);
    }
}

void MainWindow::show_reestr()
{
    prstate = 1;
    mlist->setVisible(true);
    dlist->setVisible(false);
    fill_list();

    if(mtimer.isActive())
        mtimer.stop();
}

void MainWindow::show_disp()
{
    prstate = 2;
    mlist->setVisible(false);
    dlist->setVisible(true);
    fill_list();

    mtimer.start();
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    if(this->isVisible())
    {
        event->ignore();
        this->hide();
        QSystemTrayIcon::MessageIcon icon = QSystemTrayIcon::MessageIcon(QSystemTrayIcon::Information);
        trayIcon->showMessage("M_R_Cleaner", "Click trey to open again", icon, 2000);
    }
}

void MainWindow::timerMainShot()
{
    fill_list();
}

void MainWindow::iconActivated(QSystemTrayIcon::ActivationReason reason)
{
    switch (reason) {
    case QSystemTrayIcon::Trigger:
        if(!this->isVisible())
        {
            this->show();
        }
        else
        {
            this->hide();
        }
        break;
    default:
        break;
    }
}

void MainWindow::delete_el()
{
    if(prstate == 1)
    {
        if(mlist->selectedItems().isEmpty())
            return;
        else
        {
            try
            {
#ifdef Q_OS_WIN32     
                QString name_res = mlist->selectedItems().at(0)->text();
                QSettings settings(progsmap.value(name_res), QSettings::NativeFormat);
                settings.remove(name_res);
                settings.sync();
                fill_list();
#endif
            }
            catch(QException e)
            {
                QMessageBox::warning(this, tr("Error"),
                                     tr("Error! Error! Error!"));
            }
        }
    }
    else
    {
        if(dlist->selectedItems().isEmpty())
            return;
        else
        {
            try
            {
#ifdef Q_OS_WIN32
                QString str = dispsmap.value(dlist->selectedItems().at(0)->text());
                str = ID_DEL + str;
                QProcess* proc = new QProcess();
                proc->start(str);
                proc->waitForFinished();
                qDebug() << str;
                QString res(proc->readAllStandardError());
                qDebug() << res;
#endif
            }
            catch(QException e)
            {
                QMessageBox::warning(this, tr("Error"),
                                     tr("Error! Error! Error!"));
            }
        }
    }
}

void MainWindow::add_someth()
{
    if(prstate == 1)
    {
        try
        {
            QString name_res = QFileDialog::getOpenFileName(this, tr("What"), "", tr("*.exe"));
            QString res = name_res.right(name_res.length() - name_res.lastIndexOf("/") - 1);
            res = res.replace(".exe", "");
#ifdef Q_OS_WIN32
            QSettings settings("HKEY_CURRENT_USER\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run", QSettings::NativeFormat);
            settings.setValue(res, QDir::toNativeSeparators(name_res));
            settings.sync();
            fill_list();
#endif
        }
        catch(QException ex)
        {
            QMessageBox::warning(this, tr("Error"),
                                 tr("Error! Error! Error!"));
        }
    }
    else
    {

    }
}
