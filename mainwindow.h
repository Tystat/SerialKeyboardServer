#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSerialPort/QSerialPort>
#include <windows.h>
#include <QKeySequence>
#include <QString>
#include <console.h>
#include <ledindicator.h>
#include <iostream>
#include <fstream>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_ServerStartButton_clicked();
    void on_Serial_Data_Received(void);

    void on_StopServerButton_clicked();

    void on_action_Save_triggered();

    void on_action_Load_triggered();

private:
    Ui::MainWindow *ui;
    QByteArray readData;
    QSerialPort* serial;
    void key_press(int sw);
    QKeySequence seq1;
    QKeySequence seq2;
    QKeySequence seq3;
    QKeySequence seq4;
    QKeySequence seq5;
    QKeySequence seq6;
    int HWcodeSet[6];
    int ASCIICODE[26]={'A', 'Z', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P', 'Q', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L', 'M', 'W', 'X', 'C', 'V', 'B', 'N'};
    int HWCODE[26]={  0x10,0x11,0x12,0x13,0x14,0x15,0x16,0x17,0x18,0x19,0x1E,0x1F,0x20,0x21,0x22,0x23,0x24,0x25,0x26,0x27,0x2c,0x2d,0x2e,0x2f,0x30,0x31};
    Console *console;
    LedIndicator *ledInd[6];
    bool switchState[6]={false,false,false,false,false,false};
    bool holdState[6]={false,false,false,false,false,false};
    INPUT *ip[6];
    std::ofstream cfgFileSave;
    std::ifstream cfgFileLoad;
};

#endif // MAINWINDOW_H
