#include "NodeTree.h"
#include <QFile>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QFile style_sheet_file(":/style/NodeTree.qss");
    style_sheet_file.open(QFile::ReadOnly);
    QString style_sheet = QLatin1String(style_sheet_file.readAll());
    app.setStyleSheet(style_sheet);

    NodeTree w;
    w.show();
    return app.exec();
}
