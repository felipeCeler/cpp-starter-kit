#include <iostream>

#include <QtWidgets/QApplication>

#include <GUI/Qt/MainWindow/MainWindow.hpp>


int main(int argc, char *argv[])
{

    QApplication app(argc, argv);

    if (!QGLFormat::hasOpenGL()) {
        std::cerr << "This system has no OpenGL support" << std::endl;
        return 1;
    }

	MainWindow form;

	form.show();

    return app.exec();
}




