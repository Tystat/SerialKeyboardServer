#include "serialreader.h"

serialReader::serialReader(QSerialPort *serialPort, QObject *parent) : QObject(parent)
{
    connect(serialPort, &QSerialPort::readyRead, this, &serialReader::dataReceived);
    port = serialPort;
    cout<<"Link established\n";
}

void serialReader::dataReceived (void)
{
    cout<<"Data received : ";
    readData.append(port->readAll());
    char data = readData[0];
    int i_data = data-48;
    cout<<i_data<<"\n";
    switch (i_data)
    {
        case 1 :
            press_0();
            cout<<"0 pressed\n";
            break;
        case 2 :
            press_9();
            cout<<"9 pressed\n";
            break;
        case 3 :
            press_8();
            cout<<"8 pressed\n";
            break;
        case 4 :
            press_7();
            cout<<"7 pressed\n";
            break;
        case 5 :
            press_6();
            cout<<"6 pressed\n";
            break;
    }
    readData.clear();

}

void serialReader::press_0(void)
{
    INPUT ip;
    ip.type = INPUT_KEYBOARD;
    ip.ki.time = 0;
    ip.ki.wVk = 0; //Disable virtual keyboard (emulating HW keyboard)
    ip.ki.dwExtraInfo = 0;
    ip.ki.dwFlags = KEYEVENTF_SCANCODE;//Key press
    ip.ki.wScan = 0x0B; // hardware scan code for key
    SendInput(1, &ip, sizeof(INPUT)); //Action
    ip.ki.dwFlags = KEYEVENTF_SCANCODE | KEYEVENTF_KEYUP;//Key press
    SendInput(1, &ip, sizeof(INPUT));//Action
}

void serialReader::press_9(void)
{
    INPUT ip;
    ip.type = INPUT_KEYBOARD;
    ip.ki.time = 0;
    ip.ki.wVk = 0; //Disable virtual keyboard (emulating HW keyboard)
    ip.ki.dwExtraInfo = 0;
    ip.ki.dwFlags = KEYEVENTF_SCANCODE;//Key press
    ip.ki.wScan = 0x0A; // hardware scan code for key
    SendInput(1, &ip, sizeof(INPUT));//Action
    ip.ki.dwFlags = KEYEVENTF_SCANCODE | KEYEVENTF_KEYUP;//Key press
    SendInput(1, &ip, sizeof(INPUT));//Action
}

void serialReader::press_8(void)
{
    INPUT ip;
    ip.type = INPUT_KEYBOARD;
    ip.ki.time = 0;
    ip.ki.wVk = 0; //Disable virtual keyboard (emulating HW keyboard)
    ip.ki.dwExtraInfo = 0;
    ip.ki.dwFlags = KEYEVENTF_SCANCODE;//Key press
    ip.ki.wScan = 0x09; // hardware scan code for key
    SendInput(1, &ip, sizeof(INPUT));//Action
    ip.ki.dwFlags = KEYEVENTF_SCANCODE | KEYEVENTF_KEYUP;//Key press
    SendInput(1, &ip, sizeof(INPUT));//Action
}

void serialReader::press_7(void)
{
    INPUT ip;
    ip.type = INPUT_KEYBOARD;
    ip.ki.time = 0;
    ip.ki.wVk = 0; //Disable virtual keyboard (emulating HW keyboard)
    ip.ki.dwExtraInfo = 0;
    ip.ki.dwFlags = KEYEVENTF_SCANCODE;//Key press
    ip.ki.wScan = 0x08; // hardware scan code for key
    SendInput(1, &ip, sizeof(INPUT));//Action
    ip.ki.dwFlags = KEYEVENTF_SCANCODE | KEYEVENTF_KEYUP;//Key press
    SendInput(1, &ip, sizeof(INPUT));//Action
}

void serialReader::press_6(void)
{
    INPUT ip;
    ip.type = INPUT_KEYBOARD;
    ip.ki.time = 0;
    ip.ki.wVk = 0; //Disable virtual keyboard (emulating HW keyboard)
    ip.ki.dwExtraInfo = 0;
    ip.ki.dwFlags = KEYEVENTF_SCANCODE; //Key press
    ip.ki.wScan = 0x07; // hardware scan code for key
    SendInput(1, &ip, sizeof(INPUT));//Action
    ip.ki.dwFlags = KEYEVENTF_SCANCODE | KEYEVENTF_KEYUP; //Key press
    SendInput(1, &ip, sizeof(INPUT));//Action
}
