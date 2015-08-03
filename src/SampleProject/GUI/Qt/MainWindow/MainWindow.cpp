#include <iostream>

#include <GUI/Qt/MainWindow/MainWindow.hpp>

MainWindow::MainWindow ( QMainWindow *parent ) :
	QMainWindow ( parent )
{


	this->ui = new Ui::MainWindow;
	this->ui->setupUi ( this );

	this->glWidget = new GLWidget ( this );
	this->setCentralWidget ( glWidget );

	this->aboutWidget = new AboutWidget ( this );

	QIcon icon;
	icon.addFile ( ":/Icons/celerSystem.svg" , QSize ( ) , QIcon::Normal , QIcon::Off );
	setWindowIcon ( icon );

	connect( ui->action_About_, SIGNAL( triggered() ), aboutWidget, SLOT(show()) );

}

MainWindow::~MainWindow ( )
{
	delete glWidget;
	delete aboutWidget;

	delete ui;
}

void MainWindow::keyPressEvent(QKeyEvent *e)
{

}
