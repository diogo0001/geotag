/*************************************************************
 *  Projeto: Conversor de coordenadas a partir de arquivo
 *  Autor: Diogo Tavares
 *  Última atualização: 03/12/2019
**************************************************************/

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

// Carrega dados do arquivo selecionado, armazena na classe e mostra
void MainWindow::on_abrir_arquivo_clicked()
{
    QString filter = "Arquivos de texto (*.txt)";
    QString open_file = QFileDialog::getOpenFileName(this,"Abrir arquivo","C://",filter);
    QFile file(open_file);

    if(file.open(QFile::ReadOnly|QFile::Text))
    {
        QTextStream stream_data(&file);
        QString coord_data = "";
        QStringList list;
        QList<double> h;
        float aux,sum = 0;

        if (!latitude.empty()){
            latitude.clear();
            longitude.clear();
            height.clear();
        }

        // Obtém os dados de cada linha do arquivo e os converte para os tipos apropriados
        // Armazena cada coordenada em sua lista, realiza o somatório para a média
        while(!stream_data.atEnd())
        {
            QString read_data = stream_data.readLine();
            coord_data += read_data+"\n";
            list = read_data.split(QRegExp("\\s+"));

            latitude.append(list[0].toDouble());
            longitude.append(list[1].toDouble());

            aux = list[2].toDouble();
            height.append(aux);
            sum = sum + aux;
        }

        file.close();

        //Calcula a altitude média, mínima e máxima do log e mostra ao usuário
        sum = sum/height.length();
        h = height;
        std::sort(h.begin(), h.end());
        float max_value = h.last();
        float min_value = h.first();
        h.clear();
        qDebug()<<h.length();

        QString statistics = "Número de medições :  "+QString().sprintf("%d",height.length());
        statistics += "\n\nAltura média\t:  "+QString().sprintf("%0.3f", sum);
        statistics +=  "\nAltura máxima\t:  "+QString().sprintf("%0.3f", max_value);
        statistics +=  "\nAltura mínima\t:  "+QString().sprintf("%0.3f", min_value);

        ui->label_2->setText(statistics);
        ui->plainTextEdit->setPlainText(coord_data);
    }
}

//Realiza a conversão dos dados de latitude e longitude para graus minutos e segundos
//Com precisão nos segundos de 4 casas após a vírgula
void MainWindow::on_converter_clicked()
{
    QString read_data = QString();

    for(int i=0;i<latitude.length();i++){
        read_data += convert_to_dms(latitude[i],longitude[i],height[i])+"\n";
    }

    ui->plainTextEdit->setPlainText(read_data);
}

// Retorna uma string com os dados convertidos para graus, minutos, segundos e a altura
QString MainWindow::convert_to_dms(double lat, double lng, double alt){

       QString latStr;
       QString longStr;
       double absLat = qAbs(lat);
       double absLng = qAbs(lng);
       double latMin = (absLat - int(absLat)) * 60;
       double lngMin = (absLng - int(absLng)) * 60;
       double latSec = (latMin - int(latMin)) * 60;
       double lngSec = (lngMin - int(lngMin)) * 60;

       // overflow to full minutes
       if (qRound(latSec) >= 60) {
           latMin++;
           latSec = qAbs(latSec - 60.0f);
           // overflow to full degrees
           if (qRound(latMin) >= 60) {
               absLat++;
               latMin = qAbs(latMin - 60.0f);
               // avoid invalid latitude due to latSec rounding below
               if (qRound(absLat) >= 90)
                   latSec = 0.0f;
           }
       }
       if (qRound(lngSec) >= 60) {
           lngMin++;
           lngSec = qAbs(lngSec - 60.0f);
           if (qRound(lngMin) >= 60) {
               absLng++;
               lngMin = qAbs(lngMin - 60.0f);
               // avoid invalid longitude due to lngSec rounding below
               if (qRound(absLng) >= 180)
                   lngSec = 0.0f;
           }
       }

       latStr = QString::number(int(absLat))+"°"+
                QString::number(int(latMin))+"'"+
                QString::number(latSec,'f',4)+"\"";

       longStr = QString::number(int(absLng))+"°"+
                 QString::number(int(lngMin))+"'"+
                 QString::number(lngSec,'f',4)+"\"";

      return latStr+"  "+longStr+"  "+QString::number(alt,'f', 4);
}

// Salva os dados que estiverem sendo exibidos na tela
void MainWindow::on_salvar_clicked()
{
    QString filter = "Arquivos de texto (*.txt)";
    QString open_file = QFileDialog::getSaveFileName(this,"Salvar Arquivo","C://",filter);
    QFile file(open_file);

    if(file.open(QFile::WriteOnly|QFile::Text)){
        QTextStream data_out(&file);
        data_out << ui->plainTextEdit->toPlainText();
        file.flush();
        file.close();
    }
}

// Limpa a tela e os dados armazenados
void MainWindow::on_limpar_clicked()
{
    ui->label_2->setText("");
    ui->plainTextEdit->setPlainText("");

    if (!latitude.empty()){
        latitude.clear();
        longitude.clear();
        height.clear();
    }
}
