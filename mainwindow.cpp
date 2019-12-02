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


void MainWindow::on_abrir_arquivo_clicked()
{
    String fileName = "geotag_file.txt";
    QFile file(fileName);

}

//Calcular a altitude média, mínima e máxima do log e mostrar ao usuário
void MainWindow::on_calcular_clicked()
{

}

//Realizar a conversão dos dados de latitude e longitude para graus minutos e segundos
//Os segundos devem ter precisão de 4 casas após a vírgula
void MainWindow::on_converter_clicked()
{

}

void MainWindow::on_salvar_clicked()
{
    String fileName = "conversão.txt";
    QFile file(fileName);
}
