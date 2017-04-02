#ifndef QUADRATICEQUATION_H
#define QUADRATICEQUATION_H

#include <QObject>

class QuadraticEquation : public QObject
{
    Q_OBJECT
public:
    explicit QuadraticEquation();
    QuadraticEquation(int a, int b, int c, int p);
    ~QuadraticEquation();

    void solvingQuadraticEquation();

private:
    int modulo(int a, int b);

    QString compareString(int a, QString string = "");
    int convertStringToInteger(QString a, int p);

    QString multiplication(QString a, QString b);
    int multiplyNumber(int a, int b, int p);
    int power(int a, int b, int p);

    int bezout_ND(int a, int p);
    int findEquation(int p);
    void dissect(int &s, int &l, int p);

    void solvingSimpleEquation(int b, int c, int p);

private:
    int _coefficientA;
    int _coefficientB;
    int _coefficientC;

    int _primeP;

};

#endif // QUADRATICEQUATION_H
