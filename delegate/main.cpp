#include "widget.h"

#include <QApplication>
#include <QWidget>
#include <QListWidget>
#include <QPushButton>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    Widget w;
//    w.show();
    QWidget w;
    QListWidget listWidget(&w);
    listWidget.resize(400,300);
    for(int var = 1; var <= 100; ++var)
        listWidget.addItem(QString::number(var)+" Item");

    QPushButton b("Change", &w);
    b.move(400,500);
    QObject::connect(&b, &QPushButton::clicked, [&]()
    {
        QListWidgetItem *itm = listWidget.currentItem();
        itm->setText("Change");
        itm->setForeground(Qt::red);
        itm->setBackground(Qt::yellow);
    });

    w.resize(500,600);
    w.show();
    return a.exec();
}
