#ifndef __GL_POLYGON_WIDGET_H__
#define __GL_POLYGON_WIDGET_H__ 1

#include <QGLWidget>
#include <QObject>

struct materialStruct;

class OrthoDemoWidget: public QGLWidget
	{ //

	Q_OBJECT

	public:
	OrthoDemoWidget(QWidget *parent);

	public slots:
				// called by the timer in the main window
	void updateCameraYAngle(int);
	void updateAngle();
	void zoomIn(int);
	void doorsOpen(int);
	// void moveVehicle(int);
	// void updateAngleManual(int);
	float wheelRotateAngle(float);

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
		double _time;
		double _scaler;
		double _movement;
		double _y_camera_angle;
		double _wheelRotate;
		int _doorsAngle;

	  void pyramid(float, const materialStruct&);
		void cylinder(float, float, const materialStruct&);
		void hexo(float, float, float, float, const materialStruct&);
		void sphere(const materialStruct&);
		void roof(float, const materialStruct& );
		void sideGroundPoly(float, const materialStruct&);
		void sideUPPoly(float, const materialStruct&);
		void windowsPoly(float, const materialStruct&);
		void cylinderforarm(const materialStruct&);
		void arm(double, double, double);
		void wheelAxes(float, float , float, float);
		void renderPlane(const materialStruct&);
		void unify(double);
// UI

	}; // class GLPolygonWidget

#endif
