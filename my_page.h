#ifndef MY_PAGE_H
#define MY_PAGE_H

#include <global.h>

class My_Page : public QListWidget
{
    Q_OBJECT
public:
    My_Page(QWidget *parent = 0);

    void hide_me();
    void show_me();

public slots:
    virtual void add_item(){}
    virtual void delete_item(){}
    virtual void fill(){}

public:
    QMap<QString, QString> itemsmap;
};

#endif // MY_PAGE_H
