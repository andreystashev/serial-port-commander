#include "widget.h"
#include "ui_widget.h"

stmConnector::stmConnector(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    ui->clearDirectory->hide();
    ui->deleteMyselfFile->hide();
    ui->deleteLocalFile->hide();
    ui->createMyselfFile->hide();



}

stmConnector::~stmConnector()
{
    delete ui;
}


void stmConnector::on_startButton_clicked()
{
    start();
}


static const uint8_t auchCRCHi[256] = {
    0x11, 0xD1, 0xD0, 0x10, 0xF0, 0x30, 0x31, 0xF1, 0x33, 0xF3, 0xF2, 0x32, 0x36, 0xF6, 0xF7,
    0x11, 0xD1, 0xD0, 0x10, 0xF0, 0x30, 0x31, 0xF1, 0x33, 0xF3, 0xF2, 0x32, 0x36, 0xF6, 0xF7,
    0x62, 0x66, 0xA6, 0xA7, 0x67, 0xA5, 0x65, 0x64, 0xA4, 0x6C, 0xAC, 0xAD, 0x6D, 0xAF, 0x6F,
    0x00, 0xC0, 0xC1, 0x01, 0xC3, 0x03, 0x02, 0xC2, 0xC6, 0x06, 0x07, 0xC7, 0x05, 0xC5, 0xC4,
    0x2E, 0x2F, 0xEF, 0x2D, 0xED, 0xEC, 0x2C, 0xE4, 0x24, 0x25, 0xE5, 0x27, 0xE7, 0xE6, 0x26,
    0x22, 0xE2, 0xE3, 0x23, 0xE1, 0x21, 0x20, 0xE0, 0xA0, 0x60, 0x61, 0xA1, 0x63, 0xA3, 0xA2,
    0x62, 0x66, 0xA6, 0xA7, 0x67, 0xA5, 0x65, 0x64, 0xA4, 0x6C, 0xAC, 0xAD, 0x6D, 0xAF, 0x6F,
    0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x10, 0x21, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41,
    0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x11, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81,
    0x00, 0xC0, 0xC1, 0x01, 0xC3, 0x03, 0x02, 0xC2, 0xC6, 0x06, 0x07, 0xC7, 0x05, 0xC5, 0xC4,
    0x04, 0xCC, 0x0C, 0x0D, 0xCD, 0x0F, 0xCF, 0xCE, 0x0E, 0x0A, 0xCA, 0xCB, 0x0B, 0xC9, 0x09,
    0x08, 0xC8, 0xD8, 0x18, 0x19, 0xD9, 0x1B, 0xDB, 0xDA, 0x1A, 0x1E, 0xDE, 0xDF, 0x1F, 0xDD,
    0x3B, 0xFB, 0x39, 0xF9, 0xF8, 0x38, 0x28, 0xE8, 0xE9, 0x29, 0xEB, 0x2B, 0x2A, 0xEA, 0xEE,
    0x1D, 0x1C, 0xDC, 0x14, 0xD4, 0xD5, 0x15, 0xD7, 0x17, 0x16, 0xD6, 0xD2, 0x12, 0x13, 0xD3,
    0x1D, 0x1C, 0xDC, 0x14, 0xD4, 0xD5, 0x15, 0xD7, 0x17, 0x16, 0xD6, 0xD2, 0x12, 0x13, 0xD3,
    0x11, 0xD1, 0xD0, 0x10, 0xF0, 0x30, 0x31, 0xF1, 0x33, 0xF3, 0xF2, 0x32, 0x36, 0xF6, 0xF7,
    0x37, 0xF5, 0x35, 0x34, 0xF4, 0x3C, 0xFC, 0xFD, 0x3D, 0xFF, 0x3F, 0x3E, 0xFE, 0xFA, 0x3A,
    0xF5
};

static const uint8_t auchCRCLo[256] = {
    0x11, 0xD1, 0xD0, 0x10, 0xF0, 0x30, 0x31, 0xF1, 0x33, 0xF3, 0xF2, 0x32, 0x36, 0xF6, 0xF7,
    0x11, 0xD1, 0xD0, 0x10, 0xF0, 0x30, 0x31, 0xF1, 0x33, 0xF3, 0xF2, 0x32, 0x36, 0xF6, 0xF7,
    0x62, 0x66, 0xA6, 0xA7, 0x67, 0xA5, 0x65, 0x64, 0xA4, 0x6C, 0xAC, 0xAD, 0x6D, 0xAF, 0x6F,
    0x00, 0xC0, 0xC1, 0x01, 0xC3, 0x03, 0x02, 0xC2, 0xC6, 0x06, 0x07, 0xC7, 0x05, 0xC5, 0xC4,
    0x2E, 0x2F, 0xEF, 0x2D, 0xED, 0xEC, 0x2C, 0xE4, 0x24, 0x25, 0xE5, 0x27, 0xE7, 0xE6, 0x26,
    0x22, 0xE2, 0xE3, 0x23, 0xE1, 0x21, 0x20, 0xE0, 0xA0, 0x60, 0x61, 0xA1, 0x63, 0xA3, 0xA2,
    0x62, 0x66, 0xA6, 0xA7, 0x67, 0xA5, 0x65, 0x64, 0xA4, 0x6C, 0xAC, 0xAD, 0x6D, 0xAF, 0x6F,
    0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x10, 0x21, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41,
    0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x11, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81,
    0x00, 0xC0, 0xC1, 0x01, 0xC3, 0x03, 0x02, 0xC2, 0xC6, 0x06, 0x07, 0xC7, 0x05, 0xC5, 0xC4,
    0x04, 0xCC, 0x0C, 0x0D, 0xCD, 0x0F, 0xCF, 0xCE, 0x0E, 0x0A, 0xCA, 0xCB, 0x0B, 0xC9, 0x09,
    0x08, 0xC8, 0xD8, 0x18, 0x19, 0xD9, 0x1B, 0xDB, 0xDA, 0x1A, 0x1E, 0xDE, 0xDF, 0x1F, 0xDD,
    0x1D, 0x1C, 0xDC, 0x14, 0xD4, 0xD5, 0x15, 0xD7, 0x17, 0x16, 0xD6, 0xD2, 0x12, 0x13, 0xD3,
    0x3B, 0xFB, 0x39, 0xF9, 0xF8, 0x38, 0x28, 0xE8, 0xE9, 0x29, 0xEB, 0x2B, 0x2A, 0xEA, 0xEE,
    0x1D, 0x1C, 0xDC, 0x14, 0xD4, 0xD5, 0x15, 0xD7, 0x17, 0x16, 0xD6, 0xD2, 0x12, 0x13, 0xD3,
    0x11, 0xD1, 0xD0, 0x10, 0xF0, 0x30, 0x31, 0xF1, 0x33, 0xF3, 0xF2, 0x32, 0x36, 0xF6, 0xF7,
    0x37, 0xF5, 0x35, 0x34, 0xF4, 0x3C, 0xFC, 0xFD, 0x3D, 0xFF, 0x3F, 0x3E, 0xFE, 0xFA, 0x3A,
    0xF5
};

uint16_t CRC16(const void *p, uint len) {
    const uint8_t *ptr = (const uint8_t *) p;
    if (len > 256U)
    {
        return 0;
    }
    uint8_t crc_hi = 0xFF;
    uint8_t crc_lo = 0xFF;
    do
    {
        uint8_t i = crc_hi ^ *ptr++;
        crc_hi = crc_lo ^ (uint8_t) (auchCRCHi[i]);
        crc_lo = (uint8_t) (auchCRCLo[i]);
    } while (--len);

    return ((crc_hi << 8) | crc_lo);
}



QByteArray templateMessage(uint8_t start=0x3A,uint16_t address = 0x0020,uint8_t code = 0x06,uint16_t fileNum = 0,QByteArray array = 0)
{
    //    QByteArray array = 0;
    if(fileNum!=0)
    {
        array.append(reinterpret_cast<const char*>(&fileNum),sizeof(fileNum));
    }
    QByteArray messageArray;
    messageArray.append(start);
    messageArray.append(reinterpret_cast<const char*>(&address),sizeof(address));
    messageArray.append(code);
    uint16_t length = array.size();
    messageArray.append(reinterpret_cast<const char*>(&length),sizeof(length));
    messageArray.append(array);
    uint16_t controlSumm = CRC16(messageArray, messageArray.size());
    messageArray.append(reinterpret_cast<const char*>(&controlSumm),sizeof(controlSumm));

    qDebug()<<messageArray.toHex()<<messageArray.size();
    return messageArray;
}




static const char blankString[] = QT_TRANSLATE_NOOP("SettingsDialog", "N/A");

void stmConnector::start()
{

    QList<QSerialPortInfo> ports = QSerialPortInfo::availablePorts();

    serialPort=new QSerialPort(ports.first());
    connect(serialPort, &QSerialPort::readyRead, this, &stmConnector::readData);
    // Если доступных портов нет, выходим из программы
    if (ports.isEmpty()) {
        ui->console->setText("No available ports");
    }


    else{
    const QStringList list = ui->serialPortInfoListBox->itemData(1).toStringList();
    ui->descriptionLabel->setText(tr("Подпись: %1").arg(list.count() > 1 ? list.at(1) : tr(blankString)));
    ui->manufacturerLabel->setText(tr("Производитель: %1").arg(list.count() > 2 ? list.at(2) : tr(blankString)));
    ui->serialNumberLabel->setText(tr("Серийный номер: %1").arg(list.count() > 3 ? list.at(3) : tr(blankString)));
    ui->locationLabel->setText(tr("Местонахождение: %1").arg(list.count() > 4 ? list.at(4) : tr(blankString)));
    ui->vidLabel->setText(tr("Идентификатор производителя: %1").arg(list.count() > 5 ? list.at(5) : tr(blankString)));
    ui->pidLabel->setText(tr("Идентификатор продукта: %1").arg(list.count() > 6 ? list.at(6) : tr(blankString)));


    ui->serialPortInfoListBox->clear();
    QString description;
    QString manufacturer;
    QString serialNumber;
    const auto infos = QSerialPortInfo::availablePorts();
    for (const QSerialPortInfo &info : infos) {
        QStringList list;
        description = info.description();
        manufacturer = info.manufacturer();
        serialNumber = info.serialNumber();
        list << info.portName()
             << (!description.isEmpty() ? description : blankString)
             << (!manufacturer.isEmpty() ? manufacturer : blankString)
             << (!serialNumber.isEmpty() ? serialNumber : blankString)
             << info.systemLocation()
             << (info.vendorIdentifier() ? QString::number(info.vendorIdentifier(), 16) : blankString)
             << (info.productIdentifier() ? QString::number(info.productIdentifier(), 16) : blankString);

        ui->serialPortInfoListBox->addItem(list.first(), list);
    }
    ui->serialPortInfoListBox->addItem(tr("Custom"));
    }



    // Настраиваем параметры соединения
    serialPort->setBaudRate(QSerialPort::BaudRate(ui->bodEdit->text().toInt()));//460800 //921600
    serialPort->setDataBits(QSerialPort::Data8);
    serialPort->setParity(QSerialPort::NoParity);
    serialPort->setStopBits(QSerialPort::OneStop);

    // Открываем порт
    if (!serialPort->open(QIODevice::ReadWrite)) {
        ui->console->setText("Failed to open port");
    }
    else{
        ui->console->setText("Serial port open");
    }
}



void stmConnector::on_checkStatusButton_clicked()
{
    ui->console->append("Отправлено: "+templateMessage(0x3A,0x0020,0x06).toHex()+"\n");
    serialPort->write(templateMessage(0x3A,0x0020,0x06));
}

void stmConnector::on_checkFileButton_clicked()
{
    ui->console->append("Отправлено: "+templateMessage(0x3A,0x0020,0x05).toHex()+"\n");
    serialPort->write(templateMessage(0x3A,0x0020,0x05));
}

void stmConnector::on_showDirectory_clicked()
{
    ui->console->append("Отправлено: "+templateMessage(0x3A,0x0020,0x11).toHex()+"\n");
    serialPort->write(templateMessage(0x3A,0x0020,0x11));

}


void stmConnector::on_readFileButton_clicked()
{
    receiveData.clear();
    receiveContainer.clear();
    ui->console->append("Отправлено: "+templateMessage(0x3A,0x0020,0x12).toHex()+"\n");
    serialPort->write(templateMessage(0x3A,0x0020,0x12));
}


void stmConnector::readData()
{
    receiveData = serialPort->readAll();
    receiveContainer+=receiveData;

    ui->console->append(receiveData.toHex());
    ui->console_2->append(receiveData);

    ui->console_2->append("Получено байт: "+QString::number(receiveContainer.size()));


}


void stmConnector::on_clearConsole_clicked()
{
    ui->console->clear();
    ui->console_2->clear();
}


void stmConnector::on_writeFile_clicked()
{
    QFile outputFile(ui->lineEdit->text()+".bin");
    if (!outputFile.open(QIODevice::WriteOnly))
    {
        ui->console->setText("Failed to open output file");
    }
    QString header = "fsize: "+QString::number(receiveContainer.size());
    ui->console->setText("Header was deleted. Size: "+QString::number(header.size()));
    qDebug()<<"Header was deleted. Size: "+QString::number(header.size());
    if(receiveContainer.data()[0]!=0x3A)
    receiveContainer.remove(0,header.size()+2);
    outputFile.write(receiveContainer);
    outputFile.close();
    ui->console->setText("File was created. Size: "+QString::number(receiveContainer.size()));
    qDebug()<<"File was created. Size: "+QString::number(receiveContainer.size());
}



void stmConnector::on_readLocalFile_clicked()
{
    inputArray.clear();
    QFile file(ui->lineEdit->text()+".bin");
    if (!file.open(QIODevice::ReadOnly)) {
        ui->console->setText("Failed to open local file");
    }

    inputArray = file.readAll();
    ui->console->append(inputArray.toHex());
    ui->console_2->append(inputArray);
    ui->console->append(QString::number(file.size())+"- size of file");
    file.close();

}


void stmConnector::on_deleteLocalFile_clicked()
{
    QFile file(ui->lineEdit->text()+".bin");
    if (!file.remove()){
        ui->console->setText("Local file not delete.");
    }
    else{
        ui->console->setText("Local file has been delete.");
    }
}







void stmConnector::on_clearDirectory_clicked()
{
    ui->console->append("Отправлено: "+templateMessage(0x3A,0x0020,0x13).toHex()+"\n");
    serialPort->write(templateMessage(0x3A,0x0020,0x13));
}


void stmConnector::on_createMyselfFile_clicked()
{
    uint16_t fileNum =ui->lineEdit->text().toInt();
    ui->console->append("Отправлено: "+templateMessage(0x3A,0x0020,0x14,fileNum).toHex()+"\n");
    serialPort->write(templateMessage(0x3A,0x0020,0x14,fileNum));
}


void stmConnector::on_deleteMyselfFile_clicked()
{
    uint16_t fileNum = ui->lineEdit->text().toInt();
    ui->console->append("Отправлено: "+templateMessage(0x3A,0x0020,0x15,fileNum).toHex()+"\n");
    serialPort->write(templateMessage(0x3A,0x0020,0x15,fileNum));
}

void stmConnector::on_defineFile_clicked()
{
    uint16_t fileNum = ui->lineEdit->text().toInt();
    ui->console->append("Отправлено: "+templateMessage(0x3A,0x0020,0x16,fileNum).toHex()+"\n");
    serialPort->write(templateMessage(0x3A,0x0020,0x16,fileNum));
}



void stmConnector::on_deleteRegime_toggled(bool checked)
{
    if(checked){
        ui->console->append("ВНИМАНИЕ! КНОПКИ УДАЛЕНИЯ БЕЗВОЗВРАТНО УДАЛЯЮТ ДАННЫЕ!");
        ui->clearDirectory->show();
        ui->deleteMyselfFile->show();
        ui->deleteLocalFile->show();
        ui->createMyselfFile->show();
    }
    else{
        ui->clearDirectory->hide();
        ui->deleteMyselfFile->hide();
        ui->deleteLocalFile->hide();
        ui->createMyselfFile->hide();
    }
}




