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

    QString filter = "Arquivos de texto (*.txt)";
    QString open_file = QFileDialog::getOpenFileName(this,"Abrir arquivo","C://",filter);
    QFile file(open_file);

    if(!file.open(QFile::ReadOnly|QFile::Text)){
        QMessageBox::warning(this,"ERRO","Erro ao abrir o arquivo");
    }
    QTextStream data_in(&file);
    read_data = data_in.readAll();
    ui->plainTextEdit->setPlainText(read_data);
    file.close();

    //Calcular a altitude média, mínima e máxima do log e mostrar ao usuário
}


//Realizar a conversão dos dados de latitude e longitude para graus minutos e segundos
//Os segundos devem ter precisão de 4 casas após a vírgula
void MainWindow::on_converter_clicked()
{

}

void MainWindow::on_salvar_clicked()
{
    QString filter = "Arquivos de texto (*.txt)";
    QString open_file = QFileDialog::getSaveFileName(this,"Salvar Arquivo","C://",filter);
    QFile file(open_file);

    if(!file.open(QFile::WriteOnly|QFile::Text)){
        QMessageBox::warning(this,"ERRO","Erro ao abrir o arquivo");
    }
    QDataStream data_out(&file);
    QString data = "Calculos";
    data_out << data;
    file.flush();
    file.close();

}
