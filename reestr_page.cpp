#include <reestr_page.h>

Reestr_Page::Reestr_Page(QWidget *parent):
    My_Page(parent)
{
    fill();
}

void Reestr_Page::add_item()
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
        fill();
#endif
    }
    catch(QException ex)
    {
        QMessageBox::warning(this, tr("Error"),
                             tr("Error! Error! Error!"));
    }
}

void Reestr_Page::delete_item()
{
    if(selectedItems().isEmpty())
        return;
    else
    {
        try
        {
#ifdef Q_OS_WIN32
            QString name_res = selectedItems().at(0)->text();
            QSettings settings(itemsmap.value(name_res), QSettings::NativeFormat);
            settings.remove(name_res);
            settings.sync();
            fill();
#endif
        }
        catch(QException e)
        {
            QMessageBox::warning(this, tr("Error"),
                                 tr("Error! Error! Error!"));
        }
    }
}

void Reestr_Page::fill()
{
    clear();
    itemsmap.clear();
    QStringList list;
    QSettings settings("HKEY_CURRENT_USER\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run", QSettings::NativeFormat);
    foreach(QString st, settings.allKeys())
    {
        list.append(st);
        itemsmap.insert(itemsmap.begin() + itemsmap.size(), st,
                        "HKEY_CURRENT_USER\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run");
    }
    QSettings settings1("HKEY_LOCAL_MACHINE\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run", QSettings::NativeFormat);
    foreach(QString st, settings1.allKeys())
    {
        list.append(st);
        itemsmap.insert(itemsmap.begin() + itemsmap.size(), st,
                        "HKEY_LOCAL_MACHINE\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run");
    }
    insertItems(0, list);
    sortItems();
}

