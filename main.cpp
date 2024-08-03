#include <QApplication>
#include "mainwindow.h"

int main(int argc, char *argv[])
{

    QApplication app(argc, argv);

//    QSurfaceFormat format;
//    format.setDepthBufferSize(24);

//    if (QOpenGLContext::openGLModuleType() == QOpenGLContext::LibGL) {
//        qDebug("Requesting 3.3 core context");
//        format.setVersion(3, 3);
//        format.setProfile(QSurfaceFormat::CoreProfile);
//    } else {
//        qDebug("Requesting 3.0 context");
//        format.setVersion(3, 0);
//    }

//    QSurfaceFormat::setDefaultFormat(format);


    //GLWidget w;
    MainWindow w;

    w.show();


    return app.exec();
}
