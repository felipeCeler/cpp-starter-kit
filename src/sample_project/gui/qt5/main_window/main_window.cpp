#include "main_window.hpp"

#include "ui_main_window_form.h"

// C++ standard library
#include <iostream>

MainWindow::MainWindow ( QMainWindow *parent ) : QMainWindow ( parent )
{      
        this->ui_ = new Ui::MainWindowForm;
        this->ui_->setupUi ( this );        

        this->createWidgets();
        this->createWidgetsConnections();
}

void MainWindow::keyPressEvent ( QKeyEvent * _key_event )
{
        Q_UNUSED(_key_event);        
}

void MainWindow::createWidgets()
{
        this->aboutWidget_ = new AboutWidget ( this );

        this->opengl_canvas_widget_ = new OpenGLCanvasWidget( this );
        this->setCentralWidget(opengl_canvas_widget_);
}

void MainWindow::createWidgetsConnections()
{
        // About Widget
        connect ( this->ui_->action_About_ , &QAction::triggered , aboutWidget_ , &AboutWidget::show );
}
