#ifndef MAINWINDOW_H
#define MAINWINDOW_H

/** Libraries **/
#include <QMainWindow>

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
    Ui::MainWindow *ui;

    /** Helper Methods **/
    void updateCalculation();
    QString timeToString(const float time);
};

#endif // MAINWINDOW_H
