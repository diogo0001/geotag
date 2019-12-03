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

    if (!latitude.empty()){
        latitude.clear();
        longitude.clear();
        highs.clear();
    }

    // Obtém os dados do arquvo e os converte para os tipos apropriados
    // Armazena cada coordenada em sua lista, realiza o somatório para a média
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
    file.close();

    //Calcula a altitude média, mínima e máxima do log e mostrar ao usuário
    sum = sum/highs.length();
    std::sort(highs.begin(), highs.end());
    float max_value = highs.last();
    float min_value = highs.first();

    QString str_out = "Número de medições :  "+QString().sprintf("%d",highs.length());
    str_out += "\n\nAltura média\t:  "+QString().sprintf("%0.3f", sum);
    str_out +=   "\nAltura máxima\t:  "+QString().sprintf("%0.3f", max_value);
    str_out +=   "\nAltura mínima\t:  "+QString().sprintf("%0.3f", min_value);

    ui->label_2->setText(str_out);
    ui->plainTextEdit->setPlainText(coord_data);
}

//Realizar a conversão dos dados de latitude e longitude para graus minutos e segundos
//Os segundos devem ter precisão de 4 casas após a vírgula
void MainWindow::on_converter_clicked()
{
    read_data = "";

    for(int i=0;i<latitude.length();i++){
        QGeoCoordinate coordinates = QGeoCoordinate(latitude[i], longitude[i]);
        read_data += coordinates.toString(QGeoCoordinate::DegreesMinutesSeconds)+"\n";
    }

    ui->plainTextEdit->setPlainText(read_data);
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
    data_out << read_data;
    file.flush();
    file.close();
}


void MainWindow::on_limpar_clicked()
{
    ui->label_2->setText("");
    ui->plainTextEdit->setPlainText("");

    if (!latitude.empty()){
        latitude.clear();
        longitude.clear();
        highs.clear();
    }
}
