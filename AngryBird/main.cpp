#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    // ================= Setting Windows Size ===========================
    QDesktopWidget wid;
    int screenW = 1200;
    int screenH = 545;
    w.setGeometry(wid.screen()->width()/2 - (screenW/2) , wid.screen()->height()/2 - (screenH/2) , screenW , screenH);
    // ================= Setting Windows Title and Icon =================
    w.setWindowTitle("AngryBird");
    w.setWindowIcon(QIcon(":/image/icon.png"));
    w.show();

    return a.exec();
}
