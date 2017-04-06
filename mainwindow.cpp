#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "aboutdialog.h"
#include "quadraticequation.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->lblError->setVisible(false);
    setWindowFlags(Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btnClose_clicked()
{
    this->close();
}

bool MainWindow::isPrime(int p)
{
    if (p < 2) {
        return false;
    } else if (p > 2) {
        if (p % 2 == 0) {
            return false;
        }

        int sqrtNum = sqrt((float)p);

        for (int i = 3; i < sqrtNum; i += 2) {
            if (p % i == 0) {
                return false;
            }
        }
    }

    return true;
}

void MainWindow::on_btnOK_clicked()
{
    ui->txtResult->clear();

    if (ui->txtPrimeP->text() == "") {
        ui->lblError->setVisible(true);
        ui->txtPrimeP->setStyleSheet(("QLineEdit{background: #ff5555;}"));
        ui->lblError->setText(tr("The integer p is not empty."));
        ui->txtPrimeP->setFocus();
        return;
    } else {
        if (!isPrime(ui->txtPrimeP->text().toInt())) {
            ui->lblError->setVisible(true);
            ui->txtPrimeP->setStyleSheet(("QLineEdit{background: #ff5555;}"));
            ui->lblError->setText(tr("The integer p must be the prime."));
            ui->txtPrimeP->setFocus();
            return;
        } else {
            ui->txtPrimeP->setStyleSheet(("QLineEdit{background: white;}"));
            ui->lblError->setVisible(false);
        }
    }

    QuadraticEquation *equation = new QuadraticEquation(ui->txtCoefficentA->text().toInt(),
            ui->txtCoefficentB->text().toInt(),
            ui->txtCoefficentC->text().toInt(),
            ui->txtPrimeP->text().toInt());
    connect(equation, SIGNAL(emitResult(QString)), this, SLOT(onResultChanged(QString)));
    equation->solvingQuadraticEquation();
}

void MainWindow::onResultChanged(QString result)
{
    ui->txtResult->append(result + "\n");
}

void MainWindow::on_txtPrimeP_editingFinished()
{
    if (ui->txtPrimeP->text() == "") {
        ui->lblError->setVisible(true);
        ui->txtPrimeP->setStyleSheet(("QLineEdit{background: #ff5555;}"));
        ui->lblError->setText(tr("The integer p is not empty."));
        ui->txtPrimeP->setFocus();
    } else {
        if (!isPrime(ui->txtPrimeP->text().toInt())) {
            ui->lblError->setVisible(true);
            ui->txtPrimeP->setStyleSheet(("QLineEdit{background: #ff5555;}"));
            ui->lblError->setText(tr("The integer p must be the prime."));
            ui->txtPrimeP->setFocus();
        } else {
            ui->txtPrimeP->setStyleSheet(("QLineEdit{background: white;}"));
            ui->lblError->setVisible(false);
        }
    }
}

void MainWindow::on_actionAbout_triggered()
{
    AboutDialog *about = new AboutDialog(this);
    about->show();
}

void MainWindow::on_txtPrimeP_textChanged(const QString &arg1)
{
    Q_UNUSED(arg1);
    ui->txtPrimeP->setToolTip(tr("The integer p must be the prime."));
}
