#include "my_page.h"

My_Page::My_Page(QWidget *parent)
    : QListWidget(parent)
{
    setFixedSize(180,140);
    setSelectionMode(QAbstractItemView::SingleSelection);
    setVisible(true);
    setFont(QFont("Times", 12, 1));
}

void My_Page::hide_me()
{
    setVisible(false);
}

void My_Page::show_me()
{
    setVisible(true);
}

