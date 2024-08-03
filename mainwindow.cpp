#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QFile ffile(ui->openGLWidget->fFile);
    if(!ffile.exists())
            qDebug() << "WE POOP \n";
        else
            qDebug() <<" WE NO POOP \n";


    ui->textEdit->clear();
    if (ffile.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QTextStream stream(&ffile);
        ui->openGLWidget->currentFShader = ffile.readAll();
        ui->textEdit->setText(ui->openGLWidget->currentFShader);
    }
    ffile.close();
}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_pauseButton_clicked()
{
    if (ui->openGLWidget->timer->isActive())
        ui->openGLWidget->timer->stop();
    else
        ui->openGLWidget->timer->start(1000/60.0);
}


void MainWindow::on_exitButton_clicked()
{
    QApplication::quit();
}


void MainWindow::on_openShaderButton_clicked()
{

}


void MainWindow::on_recompileButton_clicked()
{
    ui->openGLWidget->currentFShader = ui->textEdit->toPlainText();
    ui->openGLWidget->shaderRecompile();
}

