#include <QCoreApplication>
#include <windows.h>
#include <time.h>
#include <stdio.h>
#include <QtSerialPort/QSerialPort>
#include <serialReader.h>
#include <iostream>
#include <QCoreApplication>
#include <QStringList>
#include <QTextStream>

using namespace std;

void press_1(void);

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    const int argumentCount = QCoreApplication::arguments().size(); //Count number of parameters

    const QStringList argumentList = QCoreApplication::arguments();

    if (argumentCount == 1)
    {
        cout << "Usage: <serialportname> [baudrate]\n";
        return 1;
    }
    QSerialPort serial;
    const QString serialPortName = argumentList.at(1); //Use first parameter as serial port name

    serial.setPortName(serialPortName);
    const int serialPortBaudRate = (argumentCount > 2) //Use second parameter as serial baud rate
        ? argumentList.at(2).toInt() : QSerialPort::Baud9600;
    serial.setBaudRate(serialPortBaudRate);
    if (!serial.open(QIODevice::ReadOnly)) //If connection to device failed
    {
        cout << "Failed to open port\n";
        return 1;
    }
    serialReader serialReader(&serial); //Else start to read
    return a.exec();
}

































void press_0(void)
{
    keybd_event(VkKeyScan('0'),0x9e,0 , 0); // ‘A’ Press
    Sleep(50);
    keybd_event(VkKeyScan('0'),0x9e, KEYEVENTF_KEYUP,0); // ‘A’ Release
}

void press_9(void)
{
    keybd_event(VkKeyScan('9'),0x9e,0 , 0); // ‘A’ Press
    Sleep(50);
    keybd_event(VkKeyScan('9'),0x9e, KEYEVENTF_KEYUP,0); // ‘A’ Release
}

void press_8(void)
{
    keybd_event(VkKeyScan('8'),0x9e,0 , 0); // ‘A’ Press
    Sleep(50);
    keybd_event(VkKeyScan('8'),0x9e, KEYEVENTF_KEYUP,0); // ‘A’ Release
}

void press_7(void)
{
    keybd_event(VkKeyScan('7'),0x9e,0 , 0); // ‘A’ Press
    Sleep(50);
    keybd_event(VkKeyScan('7'),0x9e, KEYEVENTF_KEYUP,0); // ‘A’ Release
}

void press_6(void)
{
    keybd_event(VkKeyScan('6'),0x9e,0 , 0); // ‘A’ Press
    Sleep(50);
    keybd_event(VkKeyScan('6'),0x9e, KEYEVENTF_KEYUP,0); // ‘A’ Release
}
