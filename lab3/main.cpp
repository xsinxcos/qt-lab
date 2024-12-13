#include <QApplication>
#include "loginwindow.h"
#include "database.h"
#include <QDir>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    
    // 初始化数据库
    QString databaseFile = QDir::currentPath() + QDir::separator() + "hospital.db";
    Database::init(databaseFile);
    
    // 显示登录窗口
    LoginWindow w;
    w.show();
    
    return a.exec();
}
