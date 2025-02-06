#include <QApplication>
#include <QFile>
#include <QDebug>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // Resource path
    QFile file(":/myStyles.qss");
    if (!file.open(QFile::ReadOnly)) {
        qDebug() << "Could NOT open style file from resource!";
    } else {
        QString styleSheet = file.readAll();
        qDebug() << "Loaded style from resource, bytes:" << styleSheet.size();
        a.setStyleSheet(styleSheet);
    }

    MainWindow w;
    w.show();
    return a.exec();
}