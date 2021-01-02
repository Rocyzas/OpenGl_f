#include <QApplication>
#include <QVBoxLayout>
#include "VehicleWindow.h"
#include <GL/glut.h>

int main(int argc, char *argv[])
	{ // main()
	// create the application
	glutInit( & argc, argv );
	QApplication app(argc, argv);

	// create a master widget
  VehicleWindow *window = new VehicleWindow(NULL);


	// resize the window
	window->resize(612, 800);

	// show the label
	window->show();

	// start it running
	app.exec();

	// clean up
	//	delete controller;
	delete window;

	// return to caller
	return 0;
	} // main()
