#include "quadraticequation.h"

#include <QDebug>

QuadraticEquation::QuadraticEquation()
{
    _coefficientA = 0;
    _coefficientB = 0;
    _coefficientC = 0;
    _primeP = 2;
}

QuadraticEquation::QuadraticEquation(int a, int b, int c, int p)
{
    _coefficientA = a;
    _coefficientB = b;
    _coefficientC = c;
    _primeP = p;
}

QuadraticEquation::~QuadraticEquation()
{
}

int QuadraticEquation::modulo(int a, int b)
{
    if ((a >= 0 && b >= 0) || (a < 0 && b < 0)) {
        return a % b;
    } else {
        if (b < 0) {
            a = -a;
            b = -b;
        }

        return (a % b) + b;
    }
}

QString QuadraticEquation::compareString(int a, QString string)
{
    if (a / 10 == 0) {
        string = string + char(a % 10 + '0');
    } else {
        string = compareString(a / 10, string) + char(a % 10 + '0');
    }

    return string;
}

int QuadraticEquation::convertStringToInteger(QString a, int p)
{
    int so = 0;

    for (int i = 0; i < a.length(); i++) {
        so = modulo((so * 10 + a[i].digitValue() - '0'), p);
    }

    return so;
}

QString QuadraticEquation::multiplication(QString a, QString b)
{
    QString result = "";
    int n = a.length();
    int m = b.length();
    int len = n + m - 1;
    int nho = 0;

    for (int i = len; i >= 0; i--) {
        int tmp = 0;

        for (int j = n - 1; j >= 0; j--)
            if (i - j <= m && i - j >= 1) {
                int a1 = a[j].digitValue() - '0';
                int b1 = b[i - j - 1].digitValue() - '0';
                tmp += a1 * b1;
            }

        tmp += nho;
        nho = tmp / 10;
        result = QString(tmp % 10 + '0') + result;
    }

    while (result.length() > 1 && result[0] == '0') {
        result.remove(0, 1);
    }

    return result;
}

int QuadraticEquation::multiplyNumber(int a, int b, int p)
{
    QString a1 = compareString(a);
    QString b1 = compareString(b);
    QString multi = multiplication(a1, b1);

    return convertStringToInteger(multi, p);
}

int QuadraticEquation::power(int a, int b, int p)
{
    if (b == 0) {
        return 1;
    }

    if (b == 1) {
        return modulo(a, p);
    } else {
        int l = b / 2;
        int r = b - l;
        int tinh = power(a, l, p);

        if (l == r) {
            return multiplyNumber(tinh, tinh, p);
        } else {
            return multiplyNumber(tinh, multiplyNumber(tinh, a, p), p);
        }
    }
}

int QuadraticEquation::bezout_ND(int a, int p)
{
    int x1 = 0, x2 = 1, y1 = 1, y2 = 0, x = 0, y = 0, r = 0, q = 0;

    if (a == 0) {
        return 0;
    }

    while (a > 0) {
        q = p / a;
        r = p - a * q;
        x = x2 - x1 * q;
        y = y2 - y1 * q;

        p = a;
        a = r;

        x2 = x1;
        x1 = x;
        y2 = y1;
        y1 = y;
    }

    return y2;
}

void QuadraticEquation::solvingSimpleEquation(int b, int c, int p)
{
    b = modulo(b, p);
    c = modulo(-c, p);
    int dao_b = modulo(bezout_ND(b, p), p);

    emit emitResult(tr("Nghiệm phương trình là: ") + QString::number(multiplyNumber(c, dao_b, p)));
}

int QuadraticEquation::findEquation(int p)
{
    int i = 1;

    while (power(i, (p - 1) / 2, p) == 1) {
        i++;
    }

    return i;
}

void QuadraticEquation::dissect(int &s, int &l, int p)
{
    s = 0;
    p = p - 1;

    while (p % 2 == 0) {
        s = s + 1;
        p = p / 2;
    }

    l = p;
}

void QuadraticEquation::solvingQuadraticEquation()
{
    _coefficientA = _coefficientA % _primeP;
    _coefficientB = _coefficientB % _primeP;
    _coefficientC = _coefficientC % _primeP;

    if (_coefficientA == 0) {
        if (_coefficientB == 0) {
            if (_coefficientC == 0) {
                emit emitResult(tr("Phương trình có vô số nghiệm"));
            } else {
                emit emitResult(tr("Phương trình vô nghiệm"));
            }
        } else {
            solvingSimpleEquation(_coefficientB, _coefficientC, _primeP);
        }
    } else {
        int d = modulo(multiplyNumber(_coefficientB, _coefficientB, _primeP) - multiplyNumber(multiplyNumber(4, _coefficientA, _primeP), _coefficientC, _primeP), _primeP);

        if (power(d, (_primeP - 1) / 2, _primeP) == _primeP - 1) {
            emit emitResult(tr("Phương trình vô nghiệm"));
        } else {
            int n = findEquation(_primeP);
            int s, l;
            dissect(s, l, _primeP);
            int k = 1, r;

            for (int i = 1; i <= s - 1; i++) {
                r = multiplyNumber(power(d, l, _primeP), power(k, 2, _primeP), _primeP);
                r = power(r, power(2, s - i - 1, _primeP), _primeP);

                if (r == _primeP - 1) {
                    k = multiplyNumber(k, power(n, (_primeP - 1) / power(2, s - i + 1, _primeP), _primeP), _primeP);
                }
            }

            int y = multiplyNumber(k, power(d, (l + 1) / 2, _primeP), _primeP);

            solvingSimpleEquation(multiplyNumber(2, _coefficientA, _primeP), modulo(_coefficientB + y, _primeP), _primeP);
            solvingSimpleEquation(multiplyNumber(2, _coefficientA, _primeP), modulo(_coefficientB - y, _primeP), _primeP);
        }
    }
}
