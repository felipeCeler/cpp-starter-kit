/*
 * opengl_canvas_widget.hpp
 *
 *  Created on: Dec 24, 2019
 *      Author: felipe
 */

#ifndef _QT5_OPENGLCANVASWIDGET_HPP_
#define _QT5_OPENGLCANVASWIDGET_HPP_

// Standard Library
#include <memory>

// Qt5 Framework
// Qt Gui
#include <QtGui/QMouseEvent>
#include <QtGui/QKeyEvent>
// Qt Widgets
#include <QtOpenGLWidgets/QOpenGLWidget>

using ProcAddress = void(*)();

class OpenGLCanvasWidget: public QOpenGLWidget
{
        Q_OBJECT

        public:
                OpenGLCanvasWidget (QWidget * parent);
                ~OpenGLCanvasWidget ( );

                void initializeGL ( ) override;
                void paintGL ( ) override;
                void resizeGL ( int _width , int _height ) override;

        protected:
                void mouseMoveEvent ( QMouseEvent* _mouse_event ) override;
                void mousePressEvent ( QMouseEvent* _mouse_event ) override;
                void mouseReleaseEvent ( QMouseEvent* _mouse_event ) override;

                void wheelEvent ( QWheelEvent* _wheel_event ) override;
                void keyPressEvent ( QKeyEvent* _key_event ) override;                      

        private:            
                             
            
};

#endif /* _QT5_OPENGLCANVASWIDGET_HPP_ */