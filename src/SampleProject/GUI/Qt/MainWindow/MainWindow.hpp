#ifndef _MYMAINWINDOW_
#define _MYMAINWINDOW_

#include <QtGui/QtGui>

#include "ui_SampleProject.h"

#include <GUI/Qt/GLWidget/GLWidget.hpp>

class QWorkspace;

class MainWindow: public QMainWindow , private Ui::MainWindow
{
		Q_OBJECT

	public:
		MainWindow ( QMainWindow *parent = 0 );
		void keyPressEvent ( QKeyEvent *e );

	public slots:


	private:

		GLWidget* glWidget;
};

#endif
