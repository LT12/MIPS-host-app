#ifndef COMMS
#define COMMS

#include <QtCore/QtGlobal>
#include <QtSerialPort/QSerialPort>
#include <QStatusBar>
#include <QMessageBox>
#include <QObject>
#include <QTime>
#include <QApplication>
#include <QtNetwork/QTcpSocket>

#include "settingsdialog.h"
#include "ringbuffer.h"

class Comms : public QDialog
{
     Q_OBJECT

signals:
    void DataReady(void);

public:
    explicit Comms(SettingsDialog *settings, QString Host, QStatusBar *statusbar);
    bool ConnectToMIPS();
    void DisconnectFromMIPS();
    void SendCommand(QString message);
    QString SendMessage(QString message);
    void SendString(QString message);
    void writeData(const QByteArray &data);
    bool openSerialPort();
    void closeSerialPort();
    void waitforline(int timeout);
    QString getline(void);
    QByteArray readall(void);

    QSerialPort *serial;
    QStatusBar *sb;
    SettingsDialog::Settings p;
    QTcpSocket client;
    bool client_connected;
    QString host;
    RingBuffer rb;

private slots:
    void handleError(QSerialPort::SerialPortError error);
    void readData2RingBuffer(void);
    void connected(void);
    void disconnected(void);
};

#endif // COMMS

