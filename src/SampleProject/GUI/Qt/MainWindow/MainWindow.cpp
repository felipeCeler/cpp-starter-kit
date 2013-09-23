#include <QtGui>
#include <QtGui/QInputDialog>
#include <iostream>

#include <GUI/Qt/MainWindow/MainWindow.hpp>

MainWindow::MainWindow ( QMainWindow *parent ) :
	QMainWindow ( parent )
{


	setupUi ( this );
	this->glWidget = new GLWidget ( this );
	this->setCentralWidget ( glWidget );

	QIcon icon;
	icon.addFile ( ":/Icons/celerSystemIcon.svg" , QSize ( ) , QIcon::Normal , QIcon::Off );
	setWindowIcon ( icon );

}

void MainWindow::keyPressEvent(QKeyEvent *e)
{

}
