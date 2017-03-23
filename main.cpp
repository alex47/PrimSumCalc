#include <QCoreApplication>
#include <QThread>
#include <QtConcurrent/QtConcurrent>
#include <QVector>
#include <QFuture>
#include <iostream>

bool isPrime(int num)
{
    int limit = num / 2 + 1;

        for (int i = 3; i < limit; i += 2)
        {
            if (num % i == 0)
            {
                return false;
            }
        }

        return true;
}

int numToAdd(int num)
{
    if (isPrime(num))
    {
        return num;
    }

    return 0;
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    int limit = 0;
    long long result = 2;

    std::cout << "Number: ";
    std::cin >> limit;

    QVector <QFuture < int >> futureVec;

    for (int i = 3; i < limit; i+= 2)
    {
        futureVec.append(QtConcurrent::run(numToAdd, i));
    }

    foreach (QFuture <int> futInst, futureVec)
    {
        result += futInst.result();
    }

    std::cout << std::endl << "Result: " << result;

    return a.exec();
}
