#include "VehicleWindow.h"

// constructor / destructor
VehicleWindow::VehicleWindow(QWidget *parent)
	: QWidget(parent){

	// create the window layout
	windowLayout = new QBoxLayout(QBoxLayout::LeftToRight, this);
	vertLayout = new QBoxLayout(QBoxLayout::TopToBottom, this);
	sceneLayout = new QBoxLayout(QBoxLayout::TopToBottom, this);

	// create main widget
	vWidget = new VehicleWidget(this);
	sceneLayout->addWidget(vWidget);

	// create sliders
	nVerticalSlider = new QSlider(Qt::Vertical);
	zoomSlider = new QSlider(Qt::Horizontal);
	doorSlider = new QSlider(Qt::Horizontal);
	nHorizontalSlider = new QSlider(Qt::Horizontal);
	windowSlider = new QSlider(Qt::Horizontal);
	bootSlider = new QSlider(Qt::Horizontal);

	label1 = new QLabel("Horizontal View", this);
	label1->setFixedHeight(15);
	label2 = new QLabel("Zoom", this);
	label2->setFixedHeight(15);
	label3 = new QLabel("Open Doors", this);
	label3->setFixedHeight(15);
	label4 = new QLabel("Open Windows", this);
	label4->setFixedHeight(15);
	label5 = new QLabel("Open Boot", this);
	label5->setFixedHeight(15);


	horizontal = new QGridLayout;
  horizontal->addWidget(label1);
	sceneLayout->addLayout(horizontal);
	sceneLayout->addWidget(nHorizontalSlider);

	zoom = new QGridLayout;
	zoom->addWidget(label2);
	sceneLayout->addLayout(zoom);
	sceneLayout->addWidget(zoomSlider);

	opdoors = new QGridLayout;
  opdoors->addWidget(label3);
	sceneLayout->addLayout(opdoors);
	sceneLayout->addWidget(doorSlider);

	opwindows = new QGridLayout;
  opwindows->addWidget(label4);
	sceneLayout->addLayout(opwindows);
	sceneLayout->addWidget(windowSlider);

	opboot = new QGridLayout;
  opboot->addWidget(label5);
	sceneLayout->addLayout(opboot);
	sceneLayout->addWidget(bootSlider);


	windowLayout->addLayout(sceneLayout);

	vertLayout->addWidget(nVerticalSlider);
	windowLayout->addLayout(vertLayout);

// =========================================
	ptimer = new QTimer(this);
	ptimer->start(20);

	connect(ptimer, SIGNAL(timeout()),  vWidget, SLOT(updateAngle()));

	zoomSlider->setMinimum(-7);
	zoomSlider->setMaximum(40);
	connect(zoomSlider, SIGNAL(valueChanged(int)),  vWidget, SLOT(zoomIn(int)));

	doorSlider->setMinimum(0);
	doorSlider->setMaximum(60);
	connect(doorSlider, SIGNAL(valueChanged(int)), vWidget, SLOT(doorsOpen(int)));


	windowSlider->setMinimum(0);
	windowSlider->setMaximum(15);
	connect(windowSlider, SIGNAL(valueChanged(int)), vWidget, SLOT(windowTranslate(int)));

	nVerticalSlider->setMinimum(0);
	nVerticalSlider->setMaximum(90);
	connect(nVerticalSlider, SIGNAL(valueChanged(int)),  vWidget, SLOT(updateCameraYAngle(int)));

	nHorizontalSlider->setMinimum(-90);
	nHorizontalSlider->setMaximum(90);
	connect(nHorizontalSlider, SIGNAL(valueChanged(int)),  vWidget, SLOT(updateCameraXAngle(int)));

	bootSlider->setMinimum(0);
	bootSlider->setMaximum(50);
	connect(bootSlider, SIGNAL(valueChanged(int)),  vWidget, SLOT(openBoot(int)));
}

VehicleWindow::~VehicleWindow(){
	delete vWidget;

	delete vertLayout;
	delete windowLayout;
	delete sceneLayout;

	delete label1;
	delete label2;
	delete label3;
	delete label4;
	delete label5;

	delete horizontal;
	delete zoom;
	delete opdoors;
	delete opwindows;
	delete opboot;

	delete nVerticalSlider;
	delete zoomSlider;
	delete doorSlider;
	delete nHorizontalSlider;
	delete windowSlider;
	delete bootSlider;
} // destructor

// resets all the interface elements
void VehicleWindow::ResetInterface(){
	// now force refresh
	vWidget->update();
	update();
}
