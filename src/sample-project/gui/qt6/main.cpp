// # Qt6
#include <QtWidgets/QApplication>
#include <QtGui/QSurfaceFormat>

// Standard Library
#include <iostream>

// Self
#include "main_window/main_window.hpp"

int main(int argc, char *argv[])
{

     QSurfaceFormat format;
     format.setDepthBufferSize(24);
     format.setVersion(4, 6);
     format.setProfile(QSurfaceFormat::CoreProfile);
     format.setRenderableType(QSurfaceFormat::OpenGL);
     format.setSwapBehavior(QSurfaceFormat::DoubleBuffer);
     format.setSamples(16);
     QSurfaceFormat::setDefaultFormat(format);

     QApplication app(argc, argv);

     MainWindow form;
     form.show();

     return app.exec();
}
