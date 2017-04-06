#include "aboutdialog.h"
#include "ui_aboutdialog.h"

AboutDialog::AboutDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AboutDialog)
{
    ui->setupUi(this);
    ui->lblWarningLicense->setAlignment(Qt::AlignJustify);
    setFixedSize(size());
}

AboutDialog::~AboutDialog()
{
    delete ui;
}
