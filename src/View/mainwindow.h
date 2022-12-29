#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QWidget>
#include "../Build/qcustomplot.h"
#include "../Controller/Controller.h"
#include "../Model/Model.h"
#include <string>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void InputController(s21::Controller &co);


private:
    Ui::MainWindow *ui;
    s21::Controller * contr;

    bool InsertExpression();

private slots:
    void NumPressed();
    void EqualPressed();
    void MathPressed();
    void TrigPressed();
    void Graph();
    void ACPressed();
};

#endif // MAINWINDOW_H
