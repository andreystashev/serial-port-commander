#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QCoreApplication>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QDebug>
#include <QTimer>
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
    void start();


private slots:
    void on_requestFile_clicked();
    void readData();

    void on_clearConsole_clicked();

    void on_writeFile_clicked();

    void on_readMyselfFile_clicked();

    void on_clearMyselfFile_clicked();

    void on_doubleScreen_toggled(bool checked);

    void on_status_clicked();

    void on_showDirectory_clicked();

    void on_deleteFiles_clicked();

    void on_createMyselfFile_clicked();

    void on_deleteMyselfFile_clicked();

private:
    QSerialPort *serialPort=nullptr;
    Ui::MainWindow *ui;
    QByteArray receiveData;
    QByteArray receiveContainer;
    QByteArray inputArray;
};
#endif // MAINWINDOW_H
