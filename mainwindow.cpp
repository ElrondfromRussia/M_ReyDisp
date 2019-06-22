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

    r_page = new Reestr_Page(this);
    d_page = new Disp_Page(this);
    d_page->hide_me();
    r_page->hide_me();

    m_page = r_page;
    m_page->show_me();

    setFixedSize(pix.size());
    setWindowIcon(QIcon(":/app_icon.png"));

    quitbtn= new QPushButton("");
    quitbtn->setIcon(QIcon(":/exit.png"));
    quitbtn->setFixedSize(20,20);
    QObject::connect(quitbtn, SIGNAL(clicked()), this, SLOT(hide()));
    delbtn= new QPushButton("");
    delbtn->setIcon(QIcon(":/del.png"));
    delbtn->setFixedSize(20,20);
    QObject::connect(delbtn, SIGNAL(clicked()), this, SLOT(delete_item()));
    addbtn= new QPushButton("");
    addbtn->setIcon(QIcon(":/add.png"));
    addbtn->setFixedSize(20,20);
    QObject::connect(addbtn, SIGNAL(clicked()), this, SLOT(add_item()));
    updbtn= new QPushButton("");
    updbtn->setIcon(QIcon(":/upd.png"));
    updbtn->setFixedSize(20,20);
    QObject::connect(updbtn, SIGNAL(clicked()), this, SLOT(fill()));
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

    bxlay = new QVBoxLayout();
    bxlay->addLayout(butlay);
    bxlay->addWidget(r_page);
    bxlay->addWidget(d_page);
    bxlay->setMargin(20);
    bxlay->setSpacing(0);

    setLayout(bxlay);
    bxlay->setGeometry(QRect(0,0, pix.size().width(), pix.size().height()));

    m_page->fill();

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

void MainWindow::show_reestr()
{
    r_page->show_me();
    d_page->hide_me();

    m_page = r_page;
    m_page->fill();

    if(mtimer.isActive())
        mtimer.stop();
}

void MainWindow::show_disp()
{
    d_page->show_me();
    r_page->hide_me();
    m_page = d_page;
    m_page->fill();

    mtimer.start();
}

void MainWindow::add_item()
{
    m_page->add_item();
}

void MainWindow::delete_item()
{
    m_page->delete_item();
}

void MainWindow::fill()
{
    m_page->fill();
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
    m_page->fill();
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
