#include "widget.h"
#include "ui_widget.h"
#include <QSaveFile>

stmConnector::stmConnector(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    serialPort = new QSerialPort(this);
    connect(serialPort, &QSerialPort::readyRead, this, &stmConnector::readData);
    refreshPorts();
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
    while (len-- > 0)
    {
        uint8_t i = crc_hi ^ *ptr++;
        crc_hi = crc_lo ^ (uint8_t) (auchCRCHi[i]);
        crc_lo = (uint8_t) (auchCRCLo[i]);
    }

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




void stmConnector::refreshPorts()
{
    const QString selectedPort = ui->serialPortInfoListBox->currentText();
    ui->serialPortInfoListBox->clear();
    for (const QSerialPortInfo &info : QSerialPortInfo::availablePorts()) {
        ui->serialPortInfoListBox->addItem(info.portName());
    }
    const int selectedIndex = ui->serialPortInfoListBox->findText(selectedPort);
    if (selectedIndex >= 0)
        ui->serialPortInfoListBox->setCurrentIndex(selectedIndex);
}

void stmConnector::start()
{
    refreshPorts();
    serialPort->close();
    if (ui->serialPortInfoListBox->count() == 0) {
        ui->console->setText("No available ports");
        return;
    }

    bool validBaudRate = false;
    const int baudRate = ui->bodEdit->text().toInt(&validBaudRate);
    if (!validBaudRate || baudRate <= 0) {
        ui->console->setText("Enter a positive baud rate");
        return;
    }

    const QSerialPortInfo info(ui->serialPortInfoListBox->currentText());
    ui->descriptionLabel->setText(tr("Description: %1").arg(info.description()));
    ui->manufacturerLabel->setText(tr("Manufacturer: %1").arg(info.manufacturer()));
    ui->serialNumberLabel->setText(tr("Serial number: %1").arg(info.serialNumber()));
    ui->locationLabel->setText(tr("Location: %1").arg(info.systemLocation()));
    ui->vidLabel->setText(tr("Vendor ID: %1").arg(info.vendorIdentifier(), 0, 16));
    ui->pidLabel->setText(tr("Product ID: %1").arg(info.productIdentifier(), 0, 16));

    serialPort->setPort(info);
    if (!serialPort->setBaudRate(baudRate)
        || !serialPort->setDataBits(QSerialPort::Data8)
        || !serialPort->setParity(QSerialPort::NoParity)
        || !serialPort->setStopBits(QSerialPort::OneStop)) {
        ui->console->setText("Invalid serial port settings: " + serialPort->errorString());
        return;
    }
    if (!serialPort->open(QIODevice::ReadWrite)) {
        ui->console->setText("Failed to open port: " + serialPort->errorString());
        return;
    }
    receiveData.clear();
    receiveContainer.clear();
    ui->console->setText("Serial port open");
}

void stmConnector::sendMessage(const QByteArray &message)
{
    if (!serialPort->isOpen()) {
        ui->console->append("Connect to a serial port first");
        return;
    }
    if (serialPort->write(message) != message.size()) {
        ui->console->append("Failed to queue command: " + serialPort->errorString());
        return;
    }
    ui->console->append("Sent: " + message.toHex());
}

void stmConnector::on_checkStatusButton_clicked()
{
    sendMessage(templateMessage(0x3A,0x0020,0x06));
}

void stmConnector::on_checkFileButton_clicked()
{
    sendMessage(templateMessage(0x3A,0x0020,0x05));
}

void stmConnector::on_showDirectory_clicked()
{
    sendMessage(templateMessage(0x3A,0x0020,0x11));

}


void stmConnector::on_readFileButton_clicked()
{
    receiveData.clear();
    receiveContainer.clear();
    sendMessage(templateMessage(0x3A,0x0020,0x12));
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
    if (receiveContainer.isEmpty()) {
        ui->console->setText("No received data to save");
        return;
    }
    QByteArray payload = receiveContainer;
    if (payload.startsWith("fsize: ")) {
        const int headerEnd = payload.indexOf("\r\n");
        bool validSize = false;
        const qlonglong expectedSize = headerEnd < 0 ? -1
            : payload.mid(7, headerEnd - 7).toLongLong(&validSize);
        if (!validSize || expectedSize < 0
            || payload.size() - headerEnd - 2 != expectedSize) {
            ui->console->setText("Incomplete or invalid file response");
            return;
        }
        payload.remove(0, headerEnd + 2);
    }
    QSaveFile outputFile(ui->lineEdit->text() + ".bin");
    if (!outputFile.open(QIODevice::WriteOnly)
        || outputFile.write(payload) != payload.size()
        || !outputFile.commit()) {
        ui->console->setText("Failed to save output file: " + outputFile.errorString());
        return;
    }
    ui->console->setText("File saved. Size: " + QString::number(payload.size()));
}



void stmConnector::on_readLocalFile_clicked()
{
    inputArray.clear();
    QFile file(ui->lineEdit->text()+".bin");
    if (!file.open(QIODevice::ReadOnly)) {
        ui->console->setText("Failed to open local file");
        return;
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
    sendMessage(templateMessage(0x3A,0x0020,0x13));
}


void stmConnector::on_createMyselfFile_clicked()
{
    uint16_t fileNum =ui->lineEdit->text().toInt();
    sendMessage(templateMessage(0x3A,0x0020,0x14,fileNum));
}


void stmConnector::on_deleteMyselfFile_clicked()
{
    uint16_t fileNum = ui->lineEdit->text().toInt();
    sendMessage(templateMessage(0x3A,0x0020,0x15,fileNum));
}

void stmConnector::on_defineFile_clicked()
{
    uint16_t fileNum = ui->lineEdit->text().toInt();
    sendMessage(templateMessage(0x3A,0x0020,0x16,fileNum));
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




