#include <QtTest>
#include <QLineEdit>
#include <QTextEdit>
#include <QTemporaryDir>
#include "widget.h"

uint16_t CRC16(const void *data, uint len);

class SerialPortTest : public QObject
{
    Q_OBJECT
private slots:
    void disconnectedCommands()
    {
        stmConnector widget;
        const char *commands[] = {"on_checkStatusButton_clicked", "on_checkFileButton_clicked",
            "on_showDirectory_clicked", "on_readFileButton_clicked", "on_clearDirectory_clicked",
            "on_createMyselfFile_clicked", "on_deleteMyselfFile_clicked", "on_defineFile_clicked"};
        for (const char *slot : commands)
            QVERIFY(QMetaObject::invokeMethod(&widget, slot));
        QVERIFY(widget.findChild<QTextEdit *>("console")->toPlainText().contains("Connect to a serial port first"));
        QCOMPARE(widget.findChildren<QSerialPort *>().size(), 1);
    }

    void savesPayloadWithoutChangingResponse()
    {
        QTemporaryDir dir;
        QVERIFY(dir.isValid());
        stmConnector widget;
        const QString path = dir.filePath("result");
        widget.findChild<QLineEdit *>("lineEdit")->setText(path);
        const QByteArray payload("a\0b\r\n", 5);
        const QByteArray response = "fsize: 5\r\n" + payload;
        widget.receiveContainer = response;
        for (int i = 0; i < 2; ++i) {
            QVERIFY(QMetaObject::invokeMethod(&widget, "on_writeFile_clicked"));
            QFile file(path + ".bin");
            QVERIFY(file.open(QIODevice::ReadOnly));
            QCOMPARE(file.readAll(), payload);
            QCOMPARE(widget.receiveContainer, response);
        }
    }

    void invalidResponsePreservesExistingFile_data()
    {
        QTest::addColumn<QByteArray>("response");
        QTest::newRow("empty") << QByteArray();
        QTest::newRow("truncated-header") << QByteArray("fsize: 3");
        QTest::newRow("truncated-body") << QByteArray("fsize: 3\r\na");
        QTest::newRow("invalid-size") << QByteArray("fsize: xyz\r\na");
        QTest::newRow("extra-data") << QByteArray("fsize: 1\r\nab");
    }

    void invalidResponsePreservesExistingFile()
    {
        QFETCH(QByteArray, response);
        QTemporaryDir dir;
        QVERIFY(dir.isValid());
        const QString path = dir.filePath("existing");
        QFile file(path + ".bin");
        QVERIFY(file.open(QIODevice::WriteOnly));
        QCOMPARE(file.write("original"), qint64(8));
        file.close();
        stmConnector widget;
        widget.findChild<QLineEdit *>("lineEdit")->setText(path);
        widget.receiveContainer = response;
        QVERIFY(QMetaObject::invokeMethod(&widget, "on_writeFile_clicked"));
        QVERIFY(file.open(QIODevice::ReadOnly));
        QCOMPARE(file.readAll(), QByteArray("original"));
    }

    void rawDataIsPreserved()
    {
        QTemporaryDir dir;
        QVERIFY(dir.isValid());
        stmConnector widget;
        const QString path = dir.filePath("raw");
        widget.findChild<QLineEdit *>("lineEdit")->setText(path);
        widget.receiveContainer = QByteArray("\x3a\0\xff", 3);
        QVERIFY(QMetaObject::invokeMethod(&widget, "on_writeFile_clicked"));
        QFile file(path + ".bin");
        QVERIFY(file.open(QIODevice::ReadOnly));
        QCOMPARE(file.readAll(), widget.receiveContainer);
    }

    void crcHandlesEmptyInput()
    {
        QCOMPARE(CRC16(nullptr, 0), uint16_t(0xffff));
    }
};
QTEST_MAIN(SerialPortTest)
#include "tst_widget.moc"
