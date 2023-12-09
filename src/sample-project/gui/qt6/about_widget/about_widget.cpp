#include "about_widget.hpp"

#include "ui_about_widget_form.h"

AboutWidget::AboutWidget( QWidget *parent ) : QDialog ( parent )
{

	ui = new Ui::AboutWidgetForm;
	ui->setupUi ( this );
	setWindowFlags(Qt::Dialog);
}




