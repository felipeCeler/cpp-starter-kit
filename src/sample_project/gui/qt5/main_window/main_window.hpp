#ifndef _MYMAINWINDOW_HPP_
#define _MYMAINWINDOW_HPP_

#include <QtWidgets/QMainWindow>
#include <QtWidgets/QDockWidget>

#include "gui/qt5/about_widget/about_widget.hpp"

#include "gui/qt5/opengl_canvas_widget/opengl_canvas_widget.hpp"
namespace Ui
{
    class MainWindowForm;
}


class MainWindow: public QMainWindow
{
        Q_OBJECT

        public:
                MainWindow ( QMainWindow *parent = 0 );
                virtual ~MainWindow ( ) = default;
                void keyPressEvent ( QKeyEvent * _key_event );

        public slots:

        private:

                void createWidgets();
                void createWidgetsConnections();

                Ui::MainWindowForm*    ui_;
                AboutWidget*       aboutWidget_;    

                OpenGLCanvasWidget* opengl_canvas_widget_;          
};


#endif  /// _MYMAINWINDOW_HPP_