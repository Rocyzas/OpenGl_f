#ifndef __GL_POLYGON_WIDGET_H__
#define __GL_POLYGON_WIDGET_H__ 1

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <QGLWidget>
#include <QObject>
#include <iostream>

#include "Image.h"
#include "ui_dialog.h"

struct materialStruct;

const unsigned int N_COLOR   = 3;


class VehicleWidget: public QGLWidget{

	Q_OBJECT

	public:
	VehicleWidget(QWidget *parent);

	public slots:
				// called by the timer in the main window
	void updateCameraYAngle(int);
	void updateCameraXAngle(int);
	void updateAngle();
	void zoomIn(int);
	void doorsOpen(int);
	void windowTranslate(int);
	// void moveVehicle(int);
	void openBoot(int);
	// void updateAngleManual(int);


	protected:
	// called when OpenGL context is set up
	void initializeGL();
	// called every time the widget is resized
	void resizeGL(int w, int h);
	// called every time the widget needs painting
	void paintGL();


	private:
		double _angle;
		double _angleWhole; //for a whole car
		bool _b_lighting;
		bool _b_textures;
		bool _b_obstacles;
		double _time;
		double _scaler;
		double _movement;
		double _y_camera_angle;
		double _x_camera_angle;
		double _wheelRotate;
		int _doorsAngle;
		double _windowTranslate;
		double _bootTranslate;

		glm::vec3 normal3Points(const std::array<double, 9>&);

		Image   _imageMarc;
		Image   _imageRaceTrack;
		Image   _imageMap;
	  QImage* p_qimage;

		void cylinder(float, float, const materialStruct&);
		void drawWheel(float, float, float, float, const materialStruct&, const materialStruct&);
		void sphere(const materialStruct&);
		void wheelAxes(float, float , float, float);

		void vehicleBootTop(double, float, const materialStruct&);
		void vehicleBootBottom(float, const materialStruct&);
		void vehicleRoof(float, const materialStruct&);
		void vehicleSideGround(float, const materialStruct&);
		void vehicleDoors(float, const materialStruct&);
		void vehicleSideUper(float, const materialStruct&);
		void vehicleDynaWindows(float, const materialStruct&);
		void vehicleStatWindows(float, const materialStruct&);

		void renderPlane(const materialStruct&);
		void renderPlaneP();

		void obstacle(float, const materialStruct&, const materialStruct&);
		void spawnObstacles(int,int, float,const materialStruct&,const materialStruct&);

		void unify(double);

// UI

	  void LoadDialog(const Ui_Dialog&);
	  void UnloadDialog(const Ui_Dialog&);
		Ui_Dialog _ui;
		void mouseDoubleClickEvent(QMouseEvent* event);

};

#endif
