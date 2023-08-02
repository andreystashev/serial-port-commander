

#include <QFile>


QByteArray statusMessage(){
    uint8_t hStart = 0x3A;
    uint8_t hAddr = 0x20;
    uint8_t hAddr2 = 0x00;
    uint8_t hCode = 0x06;
    uint8_t hAddr3 = 0x00;
    uint8_t hAddr4 = 0x00;
    uint8_t hcontrolSumm = 0x87;
    uint8_t hcontrolSumm2 = 0x64;

    QByteArray bytesEmptyFile;
    bytesEmptyFile.clear();

    bytesEmptyFile.append(hStart);
    bytesEmptyFile.append(hAddr);
    bytesEmptyFile.append(hAddr2);
    bytesEmptyFile.append(hCode);
    bytesEmptyFile.append(hAddr3);
    bytesEmptyFile.append(hAddr4);
    bytesEmptyFile.append(hcontrolSumm);
    bytesEmptyFile.append(hcontrolSumm2);

    return bytesEmptyFile;
}

QByteArray fileMessage(){
    uint8_t hStart = 0x3A;
    uint8_t hAddr = 0x20;
    uint8_t hAddr2 = 0x00;
    uint8_t hCode = 0x05;
    uint8_t hAddr3 = 0x00;
    uint8_t hAddr4 = 0x00;
    uint8_t hcontrolSumm = 0x87;
    uint8_t hcontrolSumm2 = 0x64;

    QByteArray bytesEmptyFile;
    bytesEmptyFile.clear();

    bytesEmptyFile.append(hStart);
    bytesEmptyFile.append(hAddr);
    bytesEmptyFile.append(hAddr2);
    bytesEmptyFile.append(hCode);
    bytesEmptyFile.append(hAddr3);
    bytesEmptyFile.append(hAddr4);
    bytesEmptyFile.append(hcontrolSumm);
    bytesEmptyFile.append(hcontrolSumm2);

    return bytesEmptyFile;
}


QByteArray fileRequestMessage(){
    uint8_t hStart = 0x3A;
    uint8_t hAddr = 0x20;
    uint8_t hAddr2 = 0x00;
    uint8_t hCode = 0x12;
    uint8_t hAddr3 = 0x00;
    uint8_t hAddr4 = 0x00;
    uint8_t hcontrolSumm = 0x87;
    uint8_t hcontrolSumm2 = 0x64;

    QByteArray bytesEmptyFile;
    bytesEmptyFile.clear();

    bytesEmptyFile.append(hStart);
    bytesEmptyFile.append(hAddr);
    bytesEmptyFile.append(hAddr2);
    bytesEmptyFile.append(hCode);
    bytesEmptyFile.append(hAddr3);
    bytesEmptyFile.append(hAddr4);
    bytesEmptyFile.append(hcontrolSumm);
    bytesEmptyFile.append(hcontrolSumm2);

    return bytesEmptyFile;
}

QByteArray directoryMessage(){
    uint8_t hStart = 0x3A;
    uint8_t hAddr = 0x20;
    uint8_t hAddr2 = 0x00;
    uint8_t hCode = 0x11;
    uint8_t hAddr3 = 0x00;
    uint8_t hAddr4 = 0x00;
    uint8_t hcontrolSumm = 0x87;
    uint8_t hcontrolSumm2 = 0x64;

    QByteArray bytesEmptyFile;
    bytesEmptyFile.clear();

    bytesEmptyFile.append(hStart);
    bytesEmptyFile.append(hAddr);
    bytesEmptyFile.append(hAddr2);
    bytesEmptyFile.append(hCode);
    bytesEmptyFile.append(hAddr3);
    bytesEmptyFile.append(hAddr4);
    bytesEmptyFile.append(hcontrolSumm);
    bytesEmptyFile.append(hcontrolSumm2);

    return bytesEmptyFile;
}

QByteArray deleteFileMessage(){
    uint8_t hStart = 0x3A;
    uint8_t hAddr = 0x20;
    uint8_t hAddr2 = 0x00;
    uint8_t hCode = 0x13;
    uint8_t hAddr3 = 0x00;
    uint8_t hAddr4 = 0x00;
    uint8_t hcontrolSumm = 0x87;
    uint8_t hcontrolSumm2 = 0x64;

    QByteArray bytesEmptyFile;
    bytesEmptyFile.clear();

    bytesEmptyFile.append(hStart);
    bytesEmptyFile.append(hAddr);
    bytesEmptyFile.append(hAddr2);
    bytesEmptyFile.append(hCode);
    bytesEmptyFile.append(hAddr3);
    bytesEmptyFile.append(hAddr4);
    bytesEmptyFile.append(hcontrolSumm);
    bytesEmptyFile.append(hcontrolSumm2);

    return bytesEmptyFile;
}
QByteArray createMyFileMessage(){
    uint8_t hStart = 0x3A;
    uint8_t hAddr = 0x20;
    uint8_t hAddr2 = 0x00;
    uint8_t hCode = 0x14;
    uint8_t hAddr3 = 0x12;
    uint8_t hAddr4 = 0x34;
    uint8_t hcontrolSumm = 0x87;
    uint8_t hcontrolSumm2 = 0x64;

    QByteArray bytesEmptyFile;
    bytesEmptyFile.clear();

    bytesEmptyFile.append(hStart);
    bytesEmptyFile.append(hAddr);
    bytesEmptyFile.append(hAddr2);
    bytesEmptyFile.append(hCode);
    bytesEmptyFile.append(hAddr3);
    bytesEmptyFile.append(hAddr4);
    bytesEmptyFile.append(hcontrolSumm);
    bytesEmptyFile.append(hcontrolSumm2);

    return bytesEmptyFile;
}
QByteArray deleteMyFileMessage(){
    uint8_t hStart = 0x3A;
    uint8_t hAddr = 0x20;
    uint8_t hAddr2 = 0x00;
    uint8_t hCode = 0x15;
    uint8_t hAddr3 = 0x12;
    uint8_t hAddr4 = 0x34;
    uint8_t hcontrolSumm = 0x87;
    uint8_t hcontrolSumm2 = 0x64;

    QByteArray bytesEmptyFile;
    bytesEmptyFile.clear();

    bytesEmptyFile.append(hStart);
    bytesEmptyFile.append(hAddr);
    bytesEmptyFile.append(hAddr2);
    bytesEmptyFile.append(hCode);
    bytesEmptyFile.append(hAddr3);
    bytesEmptyFile.append(hAddr4);
    bytesEmptyFile.append(hcontrolSumm);
    bytesEmptyFile.append(hcontrolSumm2);

    return bytesEmptyFile;
}
