/* @brief   Graphical main window class header of UART Timing Calculator app.
 * @author  Caglayan DOKME, caglayandokme@gmail.com
 * @date    November 11, 2021
 */

#pragma once

/** Libraries **/
#include <QMainWindow>
#include "UartStats.h"

/** Namespace Definition **/
namespace Ui {
    class MainWindow;
}

/** Class Definition **/
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_input_Baudrate_returnPressed();
    void on_input_ByteCount_returnPressed();
    void on_options_Parity_currentIndexChanged(int index);
    void on_options_DataBits_currentIndexChanged(int index);
    void on_options_StopBits_currentIndexChanged(int index);

private:
    /** Members **/
    Ui::MainWindow* ui;
    UartStats       stats;

    /** Helper Methods **/
    void updateCalculation();
    QString timeToString(const float time);
};
