#include "mainwindow.h"
#include "logging.h"

#include <QApplication>

Q_LOGGING_CATEGORY(perf, "performance", QtInfoMsg)

int main(int argc, char *argv[])
{
    // QLoggingCategory::setFilterRules(QStringLiteral("performance.info=false"));
    QCoreApplication::setAttribute(Qt::AA_ShareOpenGLContexts, false);

    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
