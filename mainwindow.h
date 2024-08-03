#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFile>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


private slots:
    void on_pauseButton_clicked();

    void on_exitButton_clicked();

    void on_openShaderButton_clicked();

    void on_recompileButton_clicked();

private:
    Ui::MainWindow *ui;
    QString shaderBuffer;
};
#endif // MAINWINDOW_H
