#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Accept digits only for baudrate and baudcount inputs
    ui->input_Baudrate->setValidator(new QIntValidator(0, 1e9, this));
    ui->input_ByteCount->setValidator(new QIntValidator(0, 1e9, this));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_input_Baudrate_returnPressed()
{
    updateCalculation();
}

void MainWindow::updateCalculation()
{
    // Get inputs
    const int   baudrate = ui->input_Baudrate->text().toInt();
    const int   dataBits = ui->options_DataBits->currentText().toInt();
    const int   parity   = (ui->options_Parity->currentText() == "NONE") ? 0 : 1;
    const float stopBits = ui->options_StopBits->currentText().toFloat();
    const int   bytes    = ui->input_ByteCount->text().toInt();

    // Derive helper values
    const float bitPerByte = 1 + dataBits + parity + stopBits;  // 1: Start bit

    // Calculate new outputs
    const float timePerByte = 1 / (float(baudrate) / bitPerByte);
    const float timeForAll  = timePerByte * bytes;

    // Update results
    ui->result_BitsPerByte->setText(QString::number(bitPerByte) + " bits");
    ui->result_TimePerPacket->setText(timeToString(timeForAll));
    ui->result_TimePerByte->setText(timeToString(timePerByte));
}

QString MainWindow::timeToString(const float time)
{

    if(time > 1)
        return (QString::number(time) + " s");    // Seconds range
    else if(time > 1e-3)
        return (QString::number(time * 1e3) + " ms");    // Milliseconds range
    else if(time > 1e-6)
        return (QString::number(time * 1e6) + " us");    // Microseconds range
    else if(time > 1e-9)
        return (QString::number(time * 1e9) + " ns");    // Nanoseconds range
    else
        return (QString::number(time * 1e12) + " ps");    // Picoseconds range
}

void MainWindow::on_options_Parity_currentIndexChanged(int index)
{
    updateCalculation();
}

void MainWindow::on_options_DataBits_currentIndexChanged(int index)
{
    updateCalculation();
}

void MainWindow::on_options_StopBits_currentIndexChanged(int index)
{
    updateCalculation();
}

void MainWindow::on_input_ByteCount_returnPressed()
{
    updateCalculation();
}
