#include "OrthoDemoWindow.h"

// constructor / destructor
OrthoDemoWindow::OrthoDemoWindow(QWidget *parent)
	: QWidget(parent)
	{ // constructor

	// create menu bar
	menuBar = new QMenuBar(this);

	// create file menu
	fileMenu = menuBar->addMenu("&File");

	// create the action
	actionQuit = new QAction("&Quit", this);

	// leave signals & slots to the controller

	// add the item to the menu
	fileMenu->addAction(actionQuit);

	// create the window layout
	windowLayout = new QBoxLayout(QBoxLayout::TopToBottom, this);

	// create main widget
	cubeWidget = new OrthoDemoWidget(this);
	windowLayout->addWidget(cubeWidget);

// =========================================
	// ptimer = new QTimer(this);
	//
	// ptimer->start(20);
	//
	// connect(ptimer, SIGNAL(timeout()),  cubeWidget, SLOT(updateAngle()));
	// ptimer->stop();
// =========================================
	nSlider = new QSlider(Qt::Horizontal);
	connect(nSlider, SIGNAL(valueChanged(int)), cubeWidget, SLOT(updateAngleManual(int)));
	windowLayout->addWidget(nSlider);

	// nSliderV = new QSlider(Qt::Vertical);
	// connect(nSliderV, SIGNAL(valueChanged(int)), cubeWidget, SLOT(updateAngleManualV(int)));
	// windowLayout->addWidget(nSliderV);
	} // constructor

OrthoDemoWindow::~OrthoDemoWindow()
	{ // destructor
	delete nSlider;
	delete cubeWidget;
	delete windowLayout;
	delete actionQuit;
	delete fileMenu;
	delete menuBar;
	} // destructor

// resets all the interface elements
void OrthoDemoWindow::ResetInterface()
	{ // ResetInterface()
	// nVerticesSlider->setMinimum(3);
	// nVerticesSlider->setMaximum(30);

	nSlider->setMinimum(0);
	nSlider->setMaximum(360);
	nSlider->setValue(0);
	//don't use the slider for now

	//	nVerticesSlider->setValue(thePolygon->nVertices);

	// now force refresh
	cubeWidget->update();
	update();
	} // ResetInterface()
