#ifndef __GL_POLYGON_WINDOW_H__
#define __GL_POLYGON_WINDOW_H__ 1

#include <QGLWidget>
#include <QMenuBar>
#include <QTimer>
#include <QSlider>
#include <QBoxLayout>
#include <QGroupBox>
#include "VehicleWidget.h"

class VehicleWindow: public QWidget{
	public:

	// constructor / destructor
	VehicleWindow(QWidget *parent);
	~VehicleWindow();

	//window layout
	QBoxLayout *windowLayout;

	//sceneLayout
	QBoxLayout *sceneLayout;

	//for vertical widget
	QBoxLayout *vertLayout;

	QTimer *ptimer;

	VehicleWidget *vWidget;

	// labels for sliders
	QLabel *label1;
	QLabel *label2;
	QLabel *label3;
	QLabel *label4;
	QLabel *label5;

	QGridLayout *horizontal;
	QGridLayout *zoom;
	QGridLayout *opdoors;
	QGridLayout *opwindows;
	QGridLayout *opboot;

	//Sliders for various options
	QSlider *zoomSlider; //zooming
	QSlider *nVerticalSlider; //y axis camera view
	QSlider *nHorizontalSlider; //x axis camera view
	QSlider *doorSlider; //vehicle doors open
	QSlider *windowSlider; //vehicle windows open
	QSlider *bootSlider; //vehicle boot open

	// resets all the interface elements
	void ResetInterface();
};

#endif
