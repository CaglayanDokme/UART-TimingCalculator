/* @brief   Graphical main window class source of UART Timing Calculator app.
 * @author  Caglayan DOKME, caglayandokme@gmail.com
 * @date    November 11, 2021
 */

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
    stats.setBaudrate(ui->input_Baudrate->text().toInt());
    stats.setDataBits(ui->options_DataBits->currentText().toInt());

    if(ui->options_Parity->currentText() == "NONE")
        stats.setParity(UartStats::Parity_t::NONE);
    else if(ui->options_Parity->currentText() == "ODD")
        stats.setParity(UartStats::Parity_t::ODD);
    else if(ui->options_Parity->currentText() == "EVEN")
        stats.setParity(UartStats::Parity_t::EVEN);
    else{ }

    if(ui->options_StopBits->currentText().toFloat() == 1.5)
        stats.setStopBit(UartStats::StopBit_t::STOP_BIT_1p5);
    else if(ui->options_StopBits->currentText().toFloat() == 2)
        stats.setStopBit(UartStats::StopBit_t::STOP_BIT_2);
    else
        stats.setStopBit(UartStats::StopBit_t::STOP_BIT_1);

    const int   bytes       = ui->input_ByteCount->text().toInt();
    const float timePerByte = stats.calculate();
    const float timeForAll  = stats.calculate() * bytes;

    // Update results
    ui->result_BitsPerByte->setText(QString::number(stats.getBitPerByte()) + " bits");
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
