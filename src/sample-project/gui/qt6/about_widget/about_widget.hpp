#ifndef _ABOUTWIDGET_HPP_
#define _ABOUTWIDGET_HPP_

#include <QtWidgets/QDialog>

namespace Ui
{
    class AboutWidgetForm;
}

class AboutWidget: public QDialog
{
		Q_OBJECT
	public:
		AboutWidget ( QWidget *parent = 0 );
		~AboutWidget ( ) = default;
	private:

		Ui::AboutWidgetForm * ui;

};

#endif /* _ABOUTWIDGET_HPP_ */
