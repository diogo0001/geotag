#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QFileDialog>
#include <QDebug>
#include <QStringList>
#include <QList>

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

    void on_abrir_arquivo_clicked();
    void on_converter_clicked();
    void on_salvar_clicked();
    void on_limpar_clicked();

private:
    Ui::MainWindow *ui;
    QList<double> height;
    QList<double> latitude;
    QList<double> longitude;

    QString convert_to_dms(double lat, double lng, double alt);
};

#endif // MAINWINDOW_H
