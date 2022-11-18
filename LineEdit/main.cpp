#include <QApplication>
#include <QLineEdit>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QLineEdit * lineEdit = new QLineEdit();
    lineEdit->setEchoMode(QLineEdit::PasswordEchoOnEdit);
    lineEdit->setInputMask("999.000.000.000");
    lineEdit->setPlaceholderText("input the number");
    lineEdit->show();
    return a.exec();
}
