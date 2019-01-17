#ifndef SERIALREADER_H
#define SERIALREADER_H
#include <QByteArray>
#include <QSerialPort>
#include <QString>
#include <QObject>
#include <iostream>
#include <windows.h>

using namespace std;

class serialReader : public QObject
{
    Q_OBJECT
public:
    explicit serialReader(QSerialPort *serialPort, QObject *parent = nullptr);

signals:

public slots:
    void dataReceived (void);

private:
    QByteArray readData;
    QSerialPort *port;
    void press_0(void);
    void press_9(void);
    void press_8(void);
    void press_7(void);
    void press_6(void);
};

#endif // SERIALREADER_H
