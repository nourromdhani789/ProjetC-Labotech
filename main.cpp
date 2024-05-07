#include "mainwindow.h"
#include <QApplication>
#include <QMessageBox>
#include <connection.h>
#include "mainwindow.h"
#include <QApplication>
#include <QMessageBox>
#include "connection.h"
#include <QSystemTrayIcon>
#include <QMenu>
#include <QAction>
#include <QIcon>
#include <QLabel>
#include <QTimer>
#include <QHBoxLayout>
#include <QPushButton>
#include <QTime>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    connection c;

    bool test=c.createconnection();

    MainWindow w;

    if(test)
    {w.show();
        QMessageBox::information(nullptr, QObject::tr("database is open"),
                    QObject::tr("connection successful.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

}
    else
        QMessageBox::critical(nullptr, QObject::tr("database is not open"),
                    QObject::tr("connection failed.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

    // Create a main window widget
    QWidget window;
    window.setWindowTitle("Timer");
    window.resize(300, 150);
    window.setStyleSheet("background-color: #7500af;");

    // Create a layout to organize widgets horizontally
    QHBoxLayout layout(&window);

    // Create a label to display the timer value
    QLabel label("00:00:00.000");
    label.setAlignment(Qt::AlignCenter);
    label.setStyleSheet("color: black; font-size: 24px;");
    layout.addWidget(&label);

    // Create start/stop and reset buttons
    QPushButton startStopButton("Start");
    QPushButton resetButton("Reset");

    // Set button styles
    startStopButton.setStyleSheet("background-color: #7500af; color: white; font-weight: bold;");
    resetButton.setStyleSheet("background-color: #7500af; color: white; font-weight: bold;");

    layout.addWidget(&startStopButton);
    layout.addWidget(&resetButton);

    // Create a timer
    QTimer timer;
    QTime currentTime(0, 0, 0, 0);

    // Connect start/stop button
    QObject::connect(&startStopButton, &QPushButton::clicked, [&](){
        if (timer.isActive()) {
            // Stop the timer
            timer.stop();
            startStopButton.setText("Start");
        } else {
            // Start the timer
            timer.start(10); // Update every 10 milliseconds
            startStopButton.setText("Stop");
        }
    });

    // Connect reset button
    QObject::connect(&resetButton, &QPushButton::clicked, [&](){
        // Reset the timer and label
        timer.stop();
        currentTime = QTime(0, 0, 0, 0);
        label.setText("00:00:00.000");
        startStopButton.setText("Start");
    });

    // Connect the timer's timeout signal to a lambda function
    QObject::connect(&timer, &QTimer::timeout, [&](){
        // Increment the time
        currentTime = currentTime.addMSecs(10);

        // Update the label text
        label.setText(currentTime.toString("hh:mm:ss.zzz"));
        // Check if 2 minutes have elapsed (120,000 milliseconds)
                if (currentTime >= QTime(0, 1, 0, 0)) {
                    // Shutdown the application
                    QApplication::quit();
                }
    });


    return a.exec();
}
