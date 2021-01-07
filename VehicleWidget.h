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


class VehicleWidget: public QGLWidget{

	Q_OBJECT

	public:
	VehicleWidget(QWidget *parent);

	public slots:
				// called by the timer in the main window
	void updateCameraYAngle(int);
	void updateCameraXAngle(int);
	void updateAngle();
	void updateAngleLight();
	void updateAngleEarth();
	void zoomIn(int);
	void doorsOpen(int);
	void windowTranslate(int);
	void openBoot(int);



	protected:
	// called when OpenGL context is set up
	void initializeGL();
	// called every time the widget is resized
	void resizeGL(int w, int h);
	// called every time the widget needs painting
	void paintGL();


	private:
		bool _b_lighting;
		bool _b_textures;
		bool _b_obstacles;

		double _rotateLight;
		double _rotateEarth;
		double _angleWhole; //for a whole car
		double _wheelRotate;
		int _doorsAngle;

		double _windowTranslate;
		double _bootTranslate;

		double _scaler;
		double _y_camera_angle;
		double _x_camera_angle;



		Image   _imageMarc;
		Image   _imageRaceTrack;
		Image   _imageMap;

		glm::vec3 normal3Points(const std::array<double, 9>&);


		void sphereWithTexture();
		void renderPlane(const materialStruct&);
		void makeLight(float, float, float, float, const materialStruct&);
		void obstacle(float, const materialStruct&, const materialStruct&);
		void spawnObstacles(int,int, float,const materialStruct&,const materialStruct&);
		void drawTextures(float);


		void drawDodecahedron(const materialStruct&); //the convex object
		void drawWheel(float, float, float, float, const materialStruct&, const materialStruct&);
		void wheelAxes(float, float , float, float);
		void vehicleBootTop(double, float, const materialStruct&);
		void vehicleBootBottom(float, const materialStruct&);
		void vehicleRoof(float, const materialStruct&);
		void vehicleWheelBumbers(float, const materialStruct&);
		void vehicleSideGround(float, const materialStruct&);
		void vehicleDoors(float, const materialStruct&);
		void vehicleSideUper(float, const materialStruct&);
		void vehicleDynaWindows(float, const materialStruct&);
		void vehicleStatWindows(float, const materialStruct&);

		void unifyVehicle();

// UI
	  void LoadDialog();
	  void UnloadDialog(const Ui_Dialog&);
		Ui_Dialog _ui;
		void mouseDoubleClickEvent(QMouseEvent* event);

};

#endif
