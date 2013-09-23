#include <QtGui/QtGui>
#include <GUI/Qt/GLWidget/GLWidget.hpp>


GLWidget::GLWidget ( const QGLFormat& format , QWidget* parent , const QGLWidget* shareWidget , Qt::WindowFlags f ) :
	QGLWidget ( format , parent , shareWidget , f )
{
}

GLWidget::GLWidget (  QWidget* parent , const QGLWidget* shareWidget , Qt::WindowFlags f ) :
	QGLWidget ( parent , shareWidget , f )
{
}

/// OpenGL
void GLWidget::initializeGL ( )
{
}

void GLWidget::resizeGL ( int width , int height )
{
}
/// Real Looping
void GLWidget::paintGL()
{

	glClear ( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

}
/// KeyInput
void GLWidget::processMultiKeys ( )
{
}

void GLWidget::keyPressEvent ( QKeyEvent * event )
{

}

void GLWidget::keyReleaseEvent ( QKeyEvent * event )
{

}
/// MouseInput
void GLWidget::mousePressEvent ( QMouseEvent *event )
{
}

void GLWidget::mouseReleaseEvent ( QMouseEvent *event )
{

}

void GLWidget::mouseMoveEvent ( QMouseEvent *event )
{


}
// WheelInput
void GLWidget::wheelEvent ( QWheelEvent *event )
{

}
// Drag and Drop
void GLWidget::dragEnterEvent(QDragEnterEvent *event)
{
	setBackgroundRole(QPalette::Highlight);

	event->acceptProposedAction();

	emit changed(event->mimeData());

	qDebug() << "Enter";
}
/// Then, we invoke acceptProposedAction() on event, setting the drop action to the one proposed.
/// Lastly, we emit the changed() signal, with the data that was dropped and its MIME type information as a parameter.
/// For dragMoveEvent(), we just accept the proposed QDragMoveEvent object, event, with acceptProposedAction().
void GLWidget::dragMoveEvent(QDragMoveEvent *event)
{
	event->acceptProposedAction();
}
///The DropArea class's implementation of dropEvent() extracts the event's mime data and displays it accordingly.
void GLWidget::dropEvent(QDropEvent *event)
{
	const QMimeData *mimeData = event->mimeData();
	/// The mimeData object can contain one of the following objects: an image, HTML text, plain text, or a list of URLs.

	if (event->mimeData()->hasUrls())
	{

		QList<QUrl> urlList = mimeData->urls();
		QString text;
		for (int i = 0; i < urlList.size() && i < 32; ++i) {
			QString url = urlList.at(i).path();
			text += url;// + QString("\n");
		}

	}


}

void GLWidget::dragLeaveEvent(QDragLeaveEvent *event)
{
		event->accept ( );

		qDebug() << "Exit";
}
/// For DropArea's implementation, we clear invoke clear() and then accept the proposed event.
/// The clear() function sets the text in DropArea to "<drop content>" and sets the backgroundRole to
/// QPalette::Dark. Lastly, it emits the changed() signal.


