#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QWidget>
#include <list>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    setWindowTitle("Calculator");

    QPushButton *numbuttons[10];

    for (int i = 0; i < 10; ++i) {
      QString butName = "button_" + QString::number(i);
      numbuttons[i] = MainWindow::findChild<QPushButton *>(butName);
      connect(numbuttons[i], SIGNAL(released()), this, SLOT(NumPressed()));
    }
    connect(ui->button_plus, SIGNAL(released()), this, SLOT(MathPressed()));
    connect(ui->button_divide, SIGNAL(released()), this, SLOT(MathPressed()));
    connect(ui->button_minus, SIGNAL(released()), this, SLOT(MathPressed()));
    connect(ui->button_left_bracket, SIGNAL(released()), this, SLOT(MathPressed()));
    connect(ui->button_right_bracket, SIGNAL(released()), this, SLOT(MathPressed()));
    connect(ui->button_mod, SIGNAL(released()), this, SLOT(MathPressed()));
    connect(ui->button_multiply, SIGNAL(released()), this, SLOT(MathPressed()));
    connect(ui->button_power, SIGNAL(released()), this, SLOT(MathPressed()));
    connect(ui->button_dot, SIGNAL(released()), this, SLOT(MathPressed()));
    connect(ui->button_x, SIGNAL(released()), this, SLOT(MathPressed()));

    connect(ui->button_asin, SIGNAL(released()), this, SLOT(TrigPressed()));
    connect(ui->button_sin, SIGNAL(released()), this, SLOT(TrigPressed()));
    connect(ui->button_acos, SIGNAL(released()), this, SLOT(TrigPressed()));
    connect(ui->button_atan, SIGNAL(released()), this, SLOT(TrigPressed()));
    connect(ui->button_cos, SIGNAL(released()), this, SLOT(TrigPressed()));
    connect(ui->button_ln, SIGNAL(released()), this, SLOT(TrigPressed()));
    connect(ui->button_log, SIGNAL(released()), this, SLOT(TrigPressed()));
    connect(ui->button_sqrt, SIGNAL(released()), this, SLOT(TrigPressed()));
    connect(ui->button_tan, SIGNAL(released()), this, SLOT(TrigPressed()));

    connect(ui->button_ravno, SIGNAL(released()), this, SLOT(EqualPressed()));

    connect(ui->button_graph, SIGNAL(released()), this, SLOT(Graph()));
    connect(ui->button_AC, SIGNAL(released()), this, SLOT(ACPressed()));
}

MainWindow::~MainWindow()
{
  delete ui;
}

void MainWindow::NumPressed() {
  QPushButton *button = (QPushButton *)sender();
  QString numval = button->text();
  QString displayVal = ui->expression_line->text();
  if (displayVal == "" || displayVal == "0" || displayVal == "0.0") {
    ui->expression_line->setText(numval);
  } else {
    QString val = displayVal + numval;
    ui->expression_line->setText(val);
  }
}

void MainWindow::MathPressed() {
  QString displayVal = ui->expression_line->text();
  QPushButton *button = (QPushButton *)sender();
  QString butval = button->text();
  QString newval;
  if (butval == ".") {
    newval = displayVal + butval;
  } else {
    newval = displayVal + " " + butval + " ";
  }
  ui->expression_line->setText(newval);
}

void MainWindow::TrigPressed() {
  QPushButton *button = (QPushButton *)sender();
  QString butval = button->text();
  QString displayVal = ui->expression_line->text();
  ui->expression_line->setText(displayVal + " " + butval + "( ");
}

bool MainWindow::InsertExpression() {
    QString exec = ui->expression_line->text();
    QByteArray ba = exec.toLatin1();
    char *str = ba.data();
    return contr->expression_input(&str);
}

void MainWindow::EqualPressed() {
    if (!InsertExpression()) {
      QMessageBox::warning(this, "Внимание", "Выражение введено неправильно.");
      return;
    }
    double x = ui->x_line->text().toDouble();
    if (x == 0) {
      ui->x_line->setText("0");
    }
    double ans = contr->expression_output(x);
    ui->answerLine->setText(QString::number(ans));
}


void MainWindow::InputController(s21::Controller &co) {
    contr = &co;
}

void MainWindow::Graph() {
    QVector<double> x, y;
    ui->widget->clearGraphs();

    double xmin = ui->xmin_line->text().toDouble();
    double xmax = ui->xmax_line->text().toDouble();
    double ymin = ui->ymin_line->text().toDouble();
    double ymax = ui->ymax_line->text().toDouble();
    double h = (xmax - xmin)/500;

    if (!InsertExpression()) {
        QMessageBox::warning(this, "Внимание", "Выражение введено неправильно.");
        return;
    }
    ui->widget->xAxis->setRange(xmin, xmax);
    ui->widget->yAxis->setRange(ymin, ymax);
    for (double X = xmin; X <= xmax; X += h) {
      if (X <= xmax) {
        double ans = contr->expression_output(X);
        if (!std::isnan(ans) && !std::isinf(ans)) {
          x.push_back(X);
          y.push_back(ans);
        }
      }
     }
    ui->widget->addGraph();
    ui->widget->graph(0)->addData(x, y);
    ui->widget->replot();
}

void MainWindow::ACPressed() {
  ui->expression_line->setText("");
  ui->answerLine->setText("");
  ui->x_line->setText("0");
}

