#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_arquivoPushButton_clicked()
{
    // Pega o caminho do arquivo
    filePath = QFileDialog::getOpenFileName(this, tr("Open File"), "", tr("All Files ()"));
    ui->arquivoLineEdit->setText(filePath); // Mostra o caminho no edit
    ui->start1PushButton->setEnabled(true); // Libera o botão
}

void MainWindow::on_start1PushButton_clicked()
{
    start();
}

void MainWindow::start()
{
    bool cabecalho = false;
    if( ui->checkBox->isChecked() )
        cabecalho = true;

    int coluna1 = ui->spinBox->value();
    int coluna2 = ui->spinBox_2->value();
    K = ui->kSpinBox->value();

    if( carregaDados(coluna1, coluna2) )
    {
        if( K > col1.length() )
        {
            QMessageBox::warning(this, "Erro", "O parâmetro K deve ser menor que o número de dados.");
            return;
        }

        grupos.clear();
        resultado.clear();

        grupos    = kmeans.start(K, col1, col2);
        resultado = kmeans.getGuardaGrupo();

        mostraDados();

        plotaDados();
    }
}

void MainWindow::plotaDados()
{
    ui->plot->addGraph();
    ui->plot->graph(0)->setPen(QColor(0, 200, 50, 255));
    ui->plot->graph(0)->setData(kmeans.getXKfinal(), kmeans.getYKfinal());
    ui->plot->graph(0)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssSquare, 10));
    ui->plot->graph(0)->setLineStyle(QCPGraph::lsNone);

    ui->plot->addGraph();
    ui->plot->graph(1)->setPen(QColor(200, 00, 00, 255));
    ui->plot->graph(1)->setData(kmeans.getXKinicial(), kmeans.getYKinicial());
    ui->plot->graph(1)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssTriangle, 8));
    ui->plot->graph(1)->setLineStyle(QCPGraph::lsNone);

    // Add o gráfico, seta os dados das colunas x e y, seta o label, o estilo e a interação
    ui->plot->addGraph();
    ui->plot->graph(2)->setPen(QColor(10, 30, 250, 255));
    ui->plot->graph(2)->setData(col1, col2);
    ui->plot->xAxis->setLabel("Coluna 1");
    ui->plot->yAxis->setLabel("Coluna 2");
    ui->plot->graph(2)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 6));
    ui->plot->graph(2)->setLineStyle(QCPGraph::lsNone);
    ui->plot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);

    // Acha o minimo e o máximo de cada coluna para posicionar o gráfico de acordo com os dados
    double min = col1.at(0);
    double max = col1.at(0);
    for (int var = 1; var < col1.length(); ++var) {
        if( col1.at(var) < min )
            min = col1.at(var);
        if( col1.at(var) > max )
            max = col1.at(var);
    }
    ui->plot->xAxis->setRange(min, max);

    min = col2.at(0);
    max = col2.at(0);
    for (int var = 1; var < col2.length(); ++var) {
        if( col2.at(var) < min )
            min = col2.at(var);
        if( col2.at(var) > max )
            max = col2.at(var);
    }
    ui->plot->yAxis->setRange(min, max);

    ui->plot->replot();
}

bool MainWindow::carregaDados(int coluna1, int coluna2)
{
    // Testa abrir o arquivo para leitura
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly)) {
        return false;
    }

    // Checa se o arquivo tem cabeçalho, se sim, descarta ele
    if( ui->checkBox->isChecked() )
        file.readLine();

    col1.clear();
    col2.clear();

    while(!file.atEnd())
    {
        QString line = file.readLine(); // Lê uma linha no arquivo
        col1.append( line.split(",").at(coluna1-1).toDouble() ); // Lê a coluna 1
        col2.append( line.split(",").at(coluna2-1).toDouble() ); // Lê a coluna 2
    }

    file.close(); // Fecha o arquivo

    return true;
}

void MainWindow::mostraDados()
{
    ui->resultPlainText->clear();

    ui->resultPlainText->appendPlainText( "Centroides Iniciais " );
    QVector<double> xKinicial = kmeans.getXKinicial();
    QVector<double> yKinicial = kmeans.getYKinicial();
    for (int var = 0; var < xKinicial.length(); ++var)
    {
        ui->resultPlainText->appendPlainText( "Centroide " + QString::number(var+1) + " : " +
                                              "x : " + QString::number(xKinicial.at(var)) +
                                              ", y : " +  QString::number(yKinicial.at(var)) );
    }

    ui->resultPlainText->appendPlainText("\n");
    for (int var = 0; var < grupos.length(); ++var)
    {
        ui->resultPlainText->appendPlainText( "Grupo " + QString::number(var+1) + " : " + QString::number(grupos.at(var)) );
    }
    ui->resultPlainText->appendPlainText("\n");

    ui->resultPlainText->appendPlainText( "Centroides Finais " );
    QVector<double> xKfinal = kmeans.getXKfinal();
    QVector<double> yKfinal = kmeans.getYKfinal();
    for (int var = 0; var < xKinicial.length(); ++var)
    {
        ui->resultPlainText->appendPlainText( "Centroide " + QString::number(var+1) + " : " +
                                              "x : " + QString::number(xKfinal.at(var)) +
                                              ", y : " + QString::number(yKfinal.at(var)) );
    }

    ui->resultPlainText->appendPlainText( "\nNúmero de Iterações: " + QString::number( kmeans.getIteracoes() ));

}

void MainWindow::on_salvarComoImagemPushButton_clicked()
{
    QString filePath = QFileDialog::getSaveFileName(
            new QWidget,
            tr("Salvar Gráfico"),
            "Grafico",
            "Portable Network Graphics files (*.png)" );

    if( filePath.isEmpty() )
        return;

    if( ui->plot->savePng(filePath) )
        QMessageBox::information(this, "KMEANS", "Salvo com sucesso!");
    else
        QMessageBox::information(this, "KMEANS", "Não foi possível salvar, tente novamente!");
}

void MainWindow::on_salvarCSVPushButton_clicked()
{
    if( resultado.isEmpty() )
        return;

    QString filePath = QFileDialog::getSaveFileName(
            new QWidget,
            tr("Salvar Resultado"),
            "",
            "CSV files (*.csv)" );

    QFile file( filePath ); // Tenta escrever o resultado no arquivo CSV
    if( file.open( QFile::WriteOnly |QFile::Truncate ) )
    {
        QTextStream stream( &file );
        stream << "K : " << K << "\n";
        for (int temp = 0; temp < resultado.length(); ++temp)
        {
            stream << resultado.at(temp) << "\n";
        }
    }
}
