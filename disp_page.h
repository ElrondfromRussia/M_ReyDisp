#ifndef DISP_PAGE_H
#define DISP_PAGE_H

#include <my_page.h>

class Disp_Page : public My_Page
{
public:
    Disp_Page(QWidget *parent = 0);
public slots:
    void add_item();
    void delete_item();
    void fill();
};

#endif // DISP_PAGE_H
