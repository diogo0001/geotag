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

//    QString filter = "Arquivos de texto (*.txt)";
//    QString open_file = QFileDialog::getOpenFileName(this,"Abrir arquivo","C://",filter);
//    QFile file(open_file);

    QFile file("C:/Users/kulie/Documents/##PROGRAMACAO##/HORUS/geotag/geotag_file.txt");

    if(!file.open(QFile::ReadOnly|QFile::Text)){
        QMessageBox::warning(this,"ERRO","Erro ao abrir o arquivo");
    }
    QTextStream stream_data(&file);
    QString coord_data = "";
    QStringList list;
    float aux,sum = 0;

    //Calcular a altitude média, mínima e máxima do log e mostrar ao usuário

    while(!stream_data.atEnd())
    {
        read_data = stream_data.readLine();
        coord_data += read_data+"\n";
        list = read_data.split(QRegExp("\\s+"));

        latitude.append(list[0].toDouble());
        longitude.append(list[1].toDouble());

        aux = list[2].toDouble();
        highs.append(aux);
        sum = sum + aux;
    }

    sum = sum/highs.length();
    std::sort(highs.begin(), highs.end());
    float max_value = highs.first();
    float min_value = highs.last();

    qDebug()<<"Media: "<<sum;
    qDebug()<<"Max: "<<max_value;
    qDebug()<<"Min: "<<min_value;

    QString str_out = "Altura média: "+QString().sprintf("%0.3f", sum);
    str_out += "\nAltura máxima: "+QString().sprintf("%0.3f", max_value);
    str_out += "\nAltura mínima: "+QString().sprintf("%0.3f", min_value);
    str_out += "\n\nCoordenadas:\n\n";

    ui->plainTextEdit->setPlainText(str_out+coord_data);
    file.close();
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
