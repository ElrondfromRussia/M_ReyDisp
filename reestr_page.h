#ifndef REESTR_PAGE_H
#define REESTR_PAGE_H

#include <my_page.h>


class Reestr_Page : public My_Page
{
public:
    Reestr_Page(QWidget *parent = 0);
public slots:
    void add_item();
    void delete_item();
    void fill();
};

#endif // REESTR_PAGE_H
