#include "disp_page.h"

Disp_Page::Disp_Page(QWidget *parent):
    My_Page(parent)
{
    fill();
}

void Disp_Page::add_item()
{
    //потом добавить запуск из cmd
}

void Disp_Page::delete_item()
{
    qDebug() << "HERE";
    if(selectedItems().isEmpty())
    {
        qDebug() << "NO ELS";
        return;
    }
    else
    {
        try
        {
#ifdef Q_OS_WIN32
            QString str = itemsmap.value(selectedItems().at(0)->text());
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

void Disp_Page::fill()
{
    clear();
    itemsmap.clear();

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
        itemsmap.insert(itemsmap.begin() + itemsmap.size(), buf.at(0), buf.at(1));
    }

    insertItems(0, listres);
}
