#include "../View/mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    s21::Notation no;
    s21::Controller cont(no);
    w.InputController(cont);

    w.show();
    return a.exec();
}
