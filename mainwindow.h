#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QFileDialog>
#include <QDataStream>

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

private:
    Ui::MainWindow *ui;
    QString read_data;
};

#endif // MAINWINDOW_H
