#include <QCoreApplication>
#include <QThread>
#include <QtConcurrent/QtConcurrent>
#include <QVector>
#include <QFuture>
#include <QTime>
#include <iostream>

using namespace std;

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
    QTime timer;
    float timeSec = 0;

    cout << "This program calculates the sum of the first X primes..." <<  endl << endl;

    cout << "Limit: ";
    cin >> limit;

    QVector <QFuture < int >> futureVec;
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

    cout << "Result: " << result << endl;
    cout << "Calculation time: " << timeSec << " seconds" << endl;

    return a.exec();
}
