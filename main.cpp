#include <QCoreApplication>
#include <QtConcurrent/QtConcurrent>
#include <QVector>
#include <QFuture>
#include <iostream>
#include <QTime>
#include <QTextStream>

bool isPrime(int num)
{
    int limit = sqrt(num) + 1;

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
    return isPrime(num) ? num : 0;
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    int limit = 0;
    long long result = 2;
    QTime timer;
    float timeSec = 0;
    QVector <QFuture < int >> futureVec;
    QTextStream s(stdin);


    qDebug() << "This program calculates the sum of the first X primes..." <<  endl << endl;
    qDebug() << "Limit: ";
    limit = s.readLine().toInt();


    timer.start();

    for (int i = 3; i < limit; i+= 2)
    {
        futureVec.append(QtConcurrent::run(numToAdd, i));
    }


    foreach (QFuture <int> futInst, futureVec)
    {
        result += futInst.result();
    }

    timeSec = (float)timer.elapsed() / 1000;


    qDebug() << "Result: " << result << endl;
    qDebug() << "Calculation time: " << timeSec << " seconds" << endl;


    return a.exec();
}
