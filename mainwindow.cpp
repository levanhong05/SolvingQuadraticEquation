#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "quadraticequation.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btnClose_clicked()
{
    this->close();
}

void MainWindow::on_btnOK_clicked()
{
    QuadraticEquation *equation = new QuadraticEquation(ui->txtCoefficentA->text().toInt(),
            ui->txtCoefficentB->text().toInt(),
            ui->txtCoefficentC->text().toInt(),
            ui->txtPrimeP->text().toInt());
    equation->solvingQuadraticEquation();
}
