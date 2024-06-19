#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

#include <QCoreApplication>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QDebug>
#include <QTimer>
#include <QFile>



QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class stmConnector : public QWidget
{
    Q_OBJECT

public:
    stmConnector(QWidget *parent = nullptr);
    ~stmConnector();

private slots:

    void start();

    void on_checkStatusButton_clicked();

    void on_checkFileButton_clicked();


    void readData();

    void on_clearConsole_clicked();

    void on_writeFile_clicked();

    void on_readLocalFile_clicked();

    void on_deleteLocalFile_clicked();



    void on_showDirectory_clicked();

    void on_clearDirectory_clicked();

    void on_createMyselfFile_clicked();

    void on_deleteMyselfFile_clicked();

    void on_defineFile_clicked();






    void on_readFileButton_clicked();

    void on_deleteRegime_toggled(bool checked);

    void on_startButton_clicked();

private:
    QSerialPort *serialPort=nullptr;
    Ui::Widget *ui;
    QByteArray receiveData;
    QByteArray receiveContainer;
    QByteArray inputArray;

};
#endif // WIDGET_H
