#ifndef _MYMAINWINDOW_
#define _MYMAINWINDOW_

#include <QtWidgets/QMainWindow>

#include "ui_SampleProject.h"

#include <GUI/Qt/GLWidget/GLWidget.hpp>
#include <GUI/Qt/AboutWidget/AboutWidget.hpp>


class MainWindow: public QMainWindow
{
		Q_OBJECT

	public:
		MainWindow ( QMainWindow *parent = 0 );
		virtual ~MainWindow ( );
		void keyPressEvent ( QKeyEvent *e );

	public slots:

	private:

		Ui::MainWindow 	*ui;

		GLWidget		*glWidget;
		AboutWidget 	*aboutWidget;

};

#endif
