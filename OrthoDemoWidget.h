#ifndef __GL_POLYGON_WIDGET_H__
#define __GL_POLYGON_WIDGET_H__ 1

#include <QGLWidget>
#include <QObject>
#include "ui_dialog.h"

struct materialStruct;

class OrthoDemoWidget: public QGLWidget
	{ //

	Q_OBJECT

	public:
	OrthoDemoWidget(QWidget *parent);

	public slots:
				// called by the timer in the main window
	void updateAngle();
	void zoomIn(int);
	void moveVehicle(int);
	void updateAngleManual(int);
	// void updateAngleManualV(int);

	protected:
	// called when OpenGL context is set up
	void initializeGL();
	// called every time the widget is resized
	void resizeGL(int w, int h);
	// called every time the widget needs painting
	void paintGL();

	void mouseDoubleClickEvent ( QMouseEvent * event );

	private:
		double _angle;
		double _angleWh;
		bool _b_lighting;
		double _time;
		double _scaler;
		double _movement;

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
		float wheelRotateAngle(float);
		void unify(double _time);
// UI
	  void LoadDialog(const Ui_Dialog&);
	  void UnloadDialog(const Ui_Dialog&);
	  struct OrthoPar {
	    float _x_min;
	    float _x_max;
	    float _y_min;
	    float _y_max;
	    float _z_min;
	    float _z_max;

	    OrthoPar(float x_min,
		     float x_max,
		     float y_min,
		     float y_max,
		     float z_min,
		     float z_max):
	      _x_min(x_min),
	      _x_max(x_max),
	      _y_min(y_min),
	      _y_max(y_max),
	      _z_min(z_min),
	      _z_max(z_max){}

	  };
	  struct GluPar {
	    float _x;
	    float _y;
	    float _z;
	    float _at_x;
	    float _at_y;
	    float _at_z;
	    float _up_x;
	    float _up_y;
	    float _up_z;

	    GluPar( float x,
		    float y,
		    float z,
		    float at_x,
		    float at_y,
		    float at_z,
		    float up_x,
		    float up_y,
		    float up_z ):
	      _x(x),
	      _y(y),
	      _z(z),
	      _at_x(at_x),
	      _at_y(at_y),
	      _at_z(at_z),
	      _up_x(up_x),
	      _up_y(up_y),
	      _up_z(up_z){}

	  };
	  OrthoPar _ortho_par;
	  GluPar _glupar;
	  Ui_Dialog _ui;

	}; // class GLPolygonWidget

#endif
