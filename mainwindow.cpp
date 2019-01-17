#include "mainwindow.h"
#include "ui_mainwindow.h"

/*
 *
 * LISTE DES SCANCODE
 * http://www.ee.bgu.ac.il/~microlab/MicroLab/Labs/ScanCodes.htm
 *
 *
 */

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    serial = new QSerialPort; //creating new serial port
    console = new Console; //creating new console
    for(int i=0;i<=5;i++) //creating led indicators
    {
        ledInd[i]= new LedIndicator;
        ledInd[i]->setLedSize(15);
    }
    for(int i=0;i<=5;i++) //create new inputs
    {
        ip[i]=new INPUT;
        ip[i]->type = INPUT_KEYBOARD;
        ip[i]->ki.time = 0;
        ip[i]->ki.wVk = 0; //Disable virtual keyboard (emulating HW keyboard)
        ip[i]->ki.dwExtraInfo = 0;
    }
    ui->LayoutTerm->addWidget(console);
    ui->LayoutLed1->addWidget(ledInd[0]);
    ui->LayoutLed2->addWidget(ledInd[1]);
    ui->LayoutLed3->addWidget(ledInd[2]);
    ui->LayoutLed4->addWidget(ledInd[3]);
    ui->LayoutLed5->addWidget(ledInd[4]);
    ui->LayoutLed6->addWidget(ledInd[5]);
    ui->labelServerStatus->setText("Server status : stopped");

}

MainWindow::~MainWindow()
{
    delete ui;
    for(int i=0;i<=5;i++)
        delete ledInd[i];
    delete console;
    delete serial;
}

void MainWindow::on_ServerStartButton_clicked()
{
    serial->setPortName(this->ui->PortInput->text());
    serial->setBaudRate(QSerialPort::Baud9600);
    if (this->ui->PortInput->text().toLatin1()!="")
    {
        if (!serial->open(QIODevice::ReadOnly)) //If connection to device failed
        {
            console->putData("Failed to open port ");
            console->putData(this->ui->PortInput->text().toLatin1());
            console->putData("@9600 bauds\n");
        }
        else
        {
            console->putData("Port ");
            console->putData(this->ui->PortInput->text().toLatin1());
            console->putData("@9600 bauds successfully openned\n");
            ui->labelServerStatus->setText("Server status : running");
        }
    }
    else
        console->putData("No COM port set !\n");
    connect(serial, SIGNAL(readyRead()), this, SLOT(on_Serial_Data_Received()));
    seq1 = ui->ShortCut1->keySequence();
    seq2 = ui->ShortCut2->keySequence();
    seq3 = ui->ShortCut3->keySequence();
    seq4 = ui->ShortCut4->keySequence();
    seq5 = ui->ShortCut5->keySequence();
    seq6 = ui->ShortCut6->keySequence();
    for (int i=0;i<26;i++)
    {
        if (seq1[0]==ASCIICODE[i])
            HWcodeSet[0]=HWCODE[i];
        if (seq2[0]==ASCIICODE[i])
            HWcodeSet[1]=HWCODE[i];
        if (seq3[0]==ASCIICODE[i])
            HWcodeSet[2]=HWCODE[i];
        if (seq4[0]==ASCIICODE[i])
            HWcodeSet[3]=HWCODE[i];
        if (seq5[0]==ASCIICODE[i])
            HWcodeSet[4]=HWCODE[i];
        if (seq6[0]==ASCIICODE[i])
            HWcodeSet[5]=HWCODE[i];
    }
}

void MainWindow::on_StopServerButton_clicked()
{
    if (serial->isOpen())
    {
        serial->close();
        for(int i=0;i<=5;i++)
            ledInd[i]->setState(false);
        console->putData("Port ");
        console->putData(this->ui->PortInput->text().toLatin1());
        console->putData("@9600 bauds successfully closed\n");
        ui->labelServerStatus->setText("Server status : stopped");
    }
    else
        console->putData("Port not openned\n");
}

void MainWindow::on_Serial_Data_Received()
{
    readData.append(serial->readAll());
    char data = readData[0];
    int i_data = data-48; //convert ascii numbers in integers : "0" = 48, "1" = 49...
    holdState[0]=ui->checkBoxSw1->isChecked();
    holdState[1]=ui->checkBoxSw2->isChecked();
    holdState[2]=ui->checkBoxSw3->isChecked();
    holdState[3]=ui->checkBoxSw4->isChecked();
    holdState[4]=ui->checkBoxSw5->isChecked();
    holdState[5]=ui->checkBoxSw6->isChecked();
    switch (i_data)
    {
        case 1 :
            console->putData("switch 1 flipped\n");
            if (switchState[0])
                switchState[0]=false;
            else
                switchState[0]=true;
            key_press(0);
            ledInd[0]->setState(switchState[0]);
            break;
        case 2 :
            console->putData("switch 2 flipped\n");
            if (switchState[1])
                switchState[1]=false;
            else
                switchState[1]=true;
            key_press(1);
            ledInd[1]->setState(switchState[1]);
            break;
        case 3 :
            console->putData("switch 3 flipped\n");
            if (switchState[2])
                switchState[2]=false;
            else
                switchState[2]=true;
            key_press(2);
            ledInd[2]->setState(switchState[2]);
            break;
        case 4 :
            console->putData("switch 4 flipped\n");
            if (switchState[3])
                switchState[3]=false;
            else
                switchState[3]=true;
            key_press(3);
            ledInd[3]->setState(switchState[3]);
            break;
        case 5 :
            console->putData("switch 5 flipped\n");
            if (switchState[4])
                switchState[4]=false;
            else
                switchState[4]=true;
            key_press(4);
            ledInd[4]->setState(switchState[4]);
            break;
        case 6 :
            console->putData("switch 6 flipped\n");
            if (switchState[5])
                switchState[5]=false;
            else
                switchState[5]=true;
            key_press(5);
            ledInd[5]->setState(switchState[5]);
            break;
    }
    readData.clear();
}

void MainWindow::key_press(int sw)
{
    if (holdState[sw])
    {
        if (!switchState[sw])
        {
            ip[sw]->ki.dwFlags = KEYEVENTF_SCANCODE | KEYEVENTF_KEYUP;//Key press
            SendInput(1, ip[sw], sizeof(INPUT));//Action
        }
        else
        {
            ip[sw]->ki.dwFlags = KEYEVENTF_SCANCODE;//Key press
            ip[sw]->ki.wScan = HWcodeSet[sw] ; // hardware scan code for key
            SendInput(1, ip[sw], sizeof(INPUT)); //Action
        }
    }
    else
    {
        ip[sw]->ki.dwFlags = KEYEVENTF_SCANCODE;//Key press
        ip[sw]->ki.wScan = HWcodeSet[sw] ; // hardware scan code for key
        SendInput(1, ip[sw], sizeof(INPUT)); //Action
        ip[sw]->ki.dwFlags = KEYEVENTF_SCANCODE | KEYEVENTF_KEYUP;//Key press
        SendInput(1, ip[sw], sizeof(INPUT));//Action
    }
}

void MainWindow::on_action_Save_triggered()
{
    cfgFileSave.open("settings.cfg");
    cfgFileSave << char(ui->ShortCut1->keySequence()[0]);
    cfgFileSave << "\n";
    cfgFileSave << char(ui->ShortCut2->keySequence()[0]);
    cfgFileSave << "\n";
    cfgFileSave << char(ui->ShortCut3->keySequence()[0]);
    cfgFileSave << "\n";
    cfgFileSave << char(ui->ShortCut4->keySequence()[0]);
    cfgFileSave << "\n";
    cfgFileSave << char(ui->ShortCut5->keySequence()[0]);
    cfgFileSave << "\n";
    cfgFileSave << char(ui->ShortCut6->keySequence()[0]);
    cfgFileSave << "\n";
    cfgFileSave << this->ui->PortInput->text().toStdString();
    cfgFileSave.close();
}

void MainWindow::on_action_Load_triggered()
{
    cfgFileLoad.open("settings.cfg");
    std::string line;
    int i=0;
    while ( getline (cfgFileLoad,line) )
    {
        QString bind = QString::fromStdString(line);
        QKeySequence key(bind);
        switch (i)
        {
            case 0 : ui->ShortCut1->setKeySequence(key); break;
            case 1 : ui->ShortCut2->setKeySequence(key); break;
            case 2 : ui->ShortCut3->setKeySequence(key); break;
            case 3 : ui->ShortCut4->setKeySequence(key); break;
            case 4 : ui->ShortCut5->setKeySequence(key); break;
            case 5 : ui->ShortCut6->setKeySequence(key); break;
            case 6 : this->ui->PortInput->setText(bind); break;
            default: cfgFileLoad.close(); return;
        }
        i++;
    }
    cfgFileLoad.close();
}
