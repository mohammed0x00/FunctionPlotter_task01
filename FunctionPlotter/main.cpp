#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    // Start of the App.
    QApplication a(argc, argv);

    // Create the main window and display it
    MainWindow w;
    w.show();

    // End of the Application
    return a.exec();
}
