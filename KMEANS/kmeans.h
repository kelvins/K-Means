#ifndef KMEANS_H
#define KMEANS_H

#include <QVector>
#include <QString>
#include <QFile>
#include <QMessageBox>
#include <cstdlib>
#include <math.h>
#include <QDebug>

class KMeans
{
public:
    QVector<int> start(int k, QVector<double> col1, QVector<double> col2);
    QVector<int> KMEANS();

    QVector<double> getXKinicial() const;

    QVector<double> getYKinicial() const;

    QVector<double> getXKfinal() const;

    QVector<double> getYKfinal() const;

    int getIteracoes() const;

    QVector<int> getGuardaGrupo() const;

private:
    double achaMaximo(QVector<double> vetor);
    double achaMinimo(QVector<double> vetor);
    double random(double valor1, double valor2);

private:
    int K;

    QVector<double> xKinicial;
    QVector<double> yKinicial;
    QVector<double> xKfinal;
    QVector<double> yKfinal;

    QVector<double> col1;
    QVector<double> col2;

    QVector<int> guardaGrupo;

    int iteracoes;
};

#endif // KMEANS_H
