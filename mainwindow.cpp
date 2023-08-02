#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "commands.cpp"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QList<QSerialPortInfo> ports = QSerialPortInfo::availablePorts();
    if (ports.isEmpty()) {
        ui->console->setText("No available ports");
    }
    serialPort=new QSerialPort(ports.first());
        connect(serialPort, &QSerialPort::readyRead, this, &MainWindow::readData);

    start();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::start(){
    QList<QSerialPortInfo> ports = QSerialPortInfo::availablePorts();

    // Если доступных портов нет, выходим из программы
    if (ports.isEmpty()) {
        ui->console->setText("No available ports");
    }

    // Открываем первый доступный порт

    // Настраиваем параметры соединения
    serialPort->setBaudRate(QSerialPort::BaudRate(921600));//460800 //
    serialPort->setDataBits(QSerialPort::Data8);
    serialPort->setParity(QSerialPort::NoParity);
    serialPort->setStopBits(QSerialPort::OneStop);

    // Открываем порт
    if (!serialPort->open(QIODevice::ReadWrite)) {
        ui->console->setText("Failed to open port");
    }
    else{
        ui->console->setText("serial port open");

    }
}



void MainWindow::on_requestFile_clicked()
{
    receiveData.clear();
    receiveContainer.clear();

//    statusMessage()
//    fileMessage()
//    fileRequestMessage()
    serialPort->write(fileRequestMessage());

}

void MainWindow::readData(){

    receiveData = serialPort->readAll();
    receiveContainer+=receiveData;
    if(ui->hexBox->isChecked()){
        ui->console->append(receiveData.toHex());
        ui->console_2->append(receiveData);
    }
    else{
        ui->console->append(receiveData);
        ui->console_2->append(receiveData.toHex());
    }
}


void MainWindow::on_clearConsole_clicked()
{
    ui->console->clear();
    ui->console_2->clear();
}


void MainWindow::on_writeFile_clicked()
{
    QFile outputFile("output.bin");
    if (!outputFile.open(QIODevice::Append)) {
        ui->console->setText("Failed to open output file");
    }
    outputFile.write(receiveContainer);
    outputFile.close();
    ui->console->setText("file was appended");
}


void MainWindow::on_readMyselfFile_clicked()
{
    inputArray.clear();
    QFile file("output.bin");
    if (!file.open(QIODevice::ReadOnly)) {
        ui->console->setText("Failed to open output file");
    }

    inputArray = file.readAll();
    ui->console->setText(inputArray.toHex());
    ui->console->append(QString::number(file.size())+"- size of file");
    file.close();

}


void MainWindow::on_clearMyselfFile_clicked()
{
    QFile file("output.bin");
    if (!file.open(QIODevice::WriteOnly | QIODevice::Truncate)) {
        ui->console->setText("Failed to open output file");
    }

    file.resize(0);
    file.close();
    ui->console->setText("Our file has been cleared");

}


void MainWindow::on_doubleScreen_toggled(bool checked)
{
    if(checked){
        ui->console->resize(1181,551);
        ui->console_2->hide();
    }
    else{
        ui->console->resize(681,551);
        ui->console_2->show();
    }

}


void MainWindow::on_status_clicked()
{
    receiveData.clear();
    receiveContainer.clear();

    //    statusMessage()
    //    fileMessage()
    //    fileRequestMessage()
    serialPort->write(statusMessage());
}


void MainWindow::on_showDirectory_clicked()
{
    receiveData.clear();
    receiveContainer.clear();

    //    statusMessage()
    //    fileMessage()
    //    fileRequestMessage()
    serialPort->write(directoryMessage());
}


void MainWindow::on_deleteFiles_clicked()
{
    receiveData.clear();
    receiveContainer.clear();

    serialPort->write(deleteFileMessage());
}


void MainWindow::on_createMyselfFile_clicked()
{
    receiveData.clear();
    receiveContainer.clear();

    serialPort->write(createMyFileMessage());
}


void MainWindow::on_deleteMyselfFile_clicked()
{
    receiveData.clear();
    receiveContainer.clear();

    serialPort->write(deleteMyFileMessage());
}



