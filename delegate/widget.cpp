#include "widget.h"
#include "delegate.h"

#include <QTableView>
#include <QStandardItemModel>

Widget::Widget(QWidget *parent) : QWidget{parent}
{
    resize(500,500);
    QStandardItemModel *model = new QStandardItemModel(4, 2, this);
    Delegate *delegate = new Delegate(this);

    for(int row = 0; row < 4; ++row)
    {
        for(int column = 0; column < 2; ++column)
        {
            QModelIndex index = model->index(row, column, QModelIndex());
            model->setData(index, row+column*2);
        }
    }

    QTableView *tableView = new QTableView(this);
    tableView->setModel(model);
    tableView->setItemDelegate(delegate);                                   //입력값의 범위가 한정됨(0~100)
}
