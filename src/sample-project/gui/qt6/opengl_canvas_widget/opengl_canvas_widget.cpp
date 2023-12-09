/*
 * OpenGLCanvasWidget.cpp
 *
 *  Created on: Dec 24, 2016
 *      Author: felipe
 */


// glad
#include <glad/glad.h>

#include "opengl_canvas_widget.hpp"

// Qt5 Framework
// Qt Core
#include <QtCore/QDebug>
// Qt Gui
#include <QtGui/QOpenGLContext>


OpenGLCanvasWidget::OpenGLCanvasWidget(QWidget * parent) : QOpenGLWidget(parent) 
{
    
}

OpenGLCanvasWidget::~OpenGLCanvasWidget() 
{

}

void OpenGLCanvasWidget::mousePressEvent(QMouseEvent *_mouse_event)
{
    Q_UNUSED(_mouse_event);
}

void OpenGLCanvasWidget::mouseReleaseEvent(QMouseEvent *_mouse_event)
{
	Q_UNUSED(_mouse_event);
}

void OpenGLCanvasWidget::mouseMoveEvent(QMouseEvent* _mouse_event)
{
    Q_UNUSED(_mouse_event);
}

void OpenGLCanvasWidget::wheelEvent(QWheelEvent* _wheel_event)
{
    Q_UNUSED(_wheel_event);
}

void OpenGLCanvasWidget::keyPressEvent(QKeyEvent* _key_event)
{
	Q_UNUSED(_key_event);
}

void OpenGLCanvasWidget::initializeGL ( )
{    
    
    // print some gl infos (query)
    if (!gladLoadGL()) {
        // you need an OpenGL context before loading glad
        printf("I did load GL with no context!\n");
        exit(1);
    }

    auto context = this->context();

    qDebug() << "Context valid: " << context->isValid();
    qDebug() << "Really used OpenGl: " << context->format().majorVersion() << "." << context->format().minorVersion();
    qDebug() << "OpenGl information: VENDOR:       " << (const char*)glGetString(GL_VENDOR);
    qDebug() << "                    RENDERDER:    " << (const char*)glGetString(GL_RENDERER);
    qDebug() << "                    VERSION:      " << (const char*)glGetString(GL_VERSION);
    qDebug() << "                    GLSL VERSION: " << (const char*)glGetString(GL_SHADING_LANGUAGE_VERSION);
    qDebug() << "end stuff\n";    
    	

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
}

void OpenGLCanvasWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void OpenGLCanvasWidget::resizeGL ( int _width , int _height )
{
    glViewport( 0, 0, _width, _height);	
}

