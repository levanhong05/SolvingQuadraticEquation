#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui
{
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_btnClose_clicked();

    void on_btnOK_clicked();

    void on_txtPrimeP_editingFinished();

    void on_actionAbout_triggered();

    void on_txtPrimeP_textChanged(const QString &arg1);

public slots:
    void onResultChanged(QString result);

private:
    bool isPrime(int p);

private:
    Ui::MainWindow *ui;

};

#endif // MAINWINDOW_H
