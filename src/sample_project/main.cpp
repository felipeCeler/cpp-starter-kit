// # Qt5
#include <QtWidgets/QApplication>
#include <QtGui/QSurfaceFormat>

// Standard Library
#include <iostream>

// Self
#include "gui/qt5/main_window/main_window.hpp"

int main(int argc, char *argv[])
{
    /// Selecting the Desktop Driver instead the software one
    /// @see https://forum.qt.io/topic/51574/opengl-dynamic-selected-driver/3
    QApplication::setAttribute ( Qt::AA_UseDesktopOpenGL );
    QApplication::setAttribute ( Qt::AA_DontCreateNativeWidgetSiblings );
    

    // FIXME For some how, systems with dual GPU don't work with this line.
    QSurfaceFormat format;
        format.setDepthBufferSize(24);
        format.setVersion(4, 3);
        // If CompatibilityProfile, it will use the lasted version Ex: 4.6 if possible
        format.setProfile(QSurfaceFormat::CompatibilityProfile);
        format.setRenderableType ( QSurfaceFormat::OpenGL );
        format.setSamples ( 16 );
        QSurfaceFormat::setDefaultFormat ( format );

    QApplication app ( argc , argv );

    bool testingNativeDriver = app.testAttribute ( Qt::AA_UseDesktopOpenGL );

    if ( !testingNativeDriver )
    {
        std::cout << "Neither, your system do not have the hardware requirement (OpenGL 4.3+) " << std::endl << "nor the driver are not load properly" << std::endl;
        return 0;
    }

    MainWindow form;
    form.show();

    return app.exec();
}