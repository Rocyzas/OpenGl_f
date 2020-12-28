#include "OrthoDemoWindow.h"

// constructor / destructor
OrthoDemoWindow::OrthoDemoWindow(QWidget *parent)
	: QWidget(parent){ // constructor

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
	windowLayout = new QBoxLayout(QBoxLayout::LeftToRight, this);
	uiLayout = new QBoxLayout(QBoxLayout::TopToBottom, this);
	sceneLayout = new QBoxLayout(QBoxLayout::TopToBottom, this);

	// create main widget
	cubeWidget = new OrthoDemoWidget(this);
	sceneLayout->addWidget(cubeWidget);

	// create sliders
	nVerticalSlider = new QSlider(Qt::Vertical);
	aSlider = new QSlider(Qt::Horizontal);
	doorSlider = new QSlider(Qt::Horizontal);
	// mSlider = new QSlider(Qt::Horizontal);

	sceneLayout->addWidget(aSlider);
	sceneLayout->addWidget(doorSlider);
	// sceneLayout->addWidget(mSlider);
	// sceneLayout->addWidget(nSlider);

	windowLayout->addLayout(sceneLayout);
	windowLayout->addLayout(uiLayout);
	uiLayout->addWidget(nVerticalSlider);

// =========================================
	ptimer = new QTimer(this);
	ptimer->start(20);

	connect(ptimer, SIGNAL(timeout()),  cubeWidget, SLOT(updateAngle()));
	// connect(ptimer, SIGNAL(timeout()),  cubeWidget, SLOT(updateWheel()));

	connect(aSlider, SIGNAL(valueChanged(int)),  cubeWidget, SLOT(zoomIn(int)));
	connect(doorSlider, SIGNAL(valueChanged(int)), cubeWidget, SLOT(doorsOpen(int)));
	// connect(nSlider, SIGNAL(valueChanged(int)), cubeWidget, SLOT(updateAngleManual(int)));

	// connect(mSlider, SIGNAL(valueChanged(int)), cubeWidget, SLOT(moveVehicle(int)));

	nVerticalSlider->setMinimum(0);
	nVerticalSlider->setMaximum(90);
	connect(nVerticalSlider, SIGNAL(valueChanged(int)),  cubeWidget, SLOT(updateCameraYAngle(int)));

}

OrthoDemoWindow::~OrthoDemoWindow()
	{ // destructor
	delete nSlider;
	delete mSlider;
	delete aSlider;

	delete cubeWidget;
	delete windowLayout;
	delete actionQuit;
	delete fileMenu;
	delete menuBar;
	} // destructor

// resets all the interface elements
void OrthoDemoWindow::ResetInterface()
	{ // ResetInterface()

	nSlider->setMinimum(0);
	nSlider->setMaximum(360);
	nSlider->setValue(0);
	//don't use the slider for now

	//	nVerticesSlider->setValue(thePolygon->nVertices);

	// now force refresh
	cubeWidget->update();
	update();
	} // ResetInterface()
