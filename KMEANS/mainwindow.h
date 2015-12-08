#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVector>
#include "kmeans.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_arquivoPushButton_clicked();
    void on_start1PushButton_clicked();

    void on_salvarComoImagemPushButton_clicked();

    void on_salvarCSVPushButton_clicked();

private:
    void start();
    void plotaDados();
    bool carregaDados(int coluna1, int coluna2);
    void mostraDados();

private:
    Ui::MainWindow *ui;

    QString filePath;
    int K;

    QVector<int> grupos;
    QVector<double> col1;
    QVector<double> col2;

    QVector<int> resultado;

    KMeans kmeans;
};

#endif // MAINWINDOW_H
