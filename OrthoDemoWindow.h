#ifndef __GL_POLYGON_WINDOW_H__
#define __GL_POLYGON_WINDOW_H__ 1

#include <QGLWidget>
#include <QMenuBar>
#include <QTimer>
#include <QSlider>
#include <QBoxLayout>
#include "OrthoDemoWidget.h"

class OrthoDemoWindow: public QWidget
	{
	public:


	// constructor / destructor
	OrthoDemoWindow(QWidget *parent);
	~OrthoDemoWindow();

	// visual hierarchy
	// menu bar
	QMenuBar *menuBar;
		// file menu
		QMenu *fileMenu;
			// quit action
			QAction *actionQuit;

	// window layout
	QBoxLayout *windowLayout;
	QTimer *ptimer;
	// beneath that, the main widget
	OrthoDemoWidget *cubeWidget;
	// and a slider for the number of vertices
	QSlider *nSlider;

	// resets all the interface elements
	void ResetInterface();
	};

#endif
