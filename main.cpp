/* @brief   Main file of UART Timing Calculator utility tool.
 * @author  Caglayan DOKME, caglayandokme@gmail.com
 * @date    November 9, 2021
 */

/** Libraries **/
#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
