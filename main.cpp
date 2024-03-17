#include "MainWidget.h"

#include <QApplication>
#include <QFontDatabase>
int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    // 添加字体文件
        int fontId = QFontDatabase::addApplicationFont(":/resources/fonts/AlimamaDongFangDaKai-Regular.ttf");
        QStringList fontFamilies = QFontDatabase::applicationFontFamilies(fontId);

        QFont font;
        if (fontFamilies.size() > 0)
        {
            font.setFamily(fontFamilies.at(0));
            font.setPixelSize(14);
            QApplication::setFont(font);
        }



    a.setStyleSheet(":/resources/styles/app.qss");

    MainWidget w;

    w.show();
    return a.exec();
}
