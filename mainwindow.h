#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWebEngineView>

class QLineEdit;
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    QLineEdit *lineEditURL;
    QWebEngineView *webEngineView;

public slots:
    void goSlot();
    void goBackwardSlot();
    void goForwardSlot();
    void goHomeSlot();

};
#endif // MAINWINDOW_H
