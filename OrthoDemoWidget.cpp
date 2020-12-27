#include <GL/glut.h>
#include <QGLWidget>
#include <QDebug>
#include <cmath>
#include "OrthoDemoWidget.h"
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

static const float PI = 3.1415926535;
static const int N        = 100; // This determines the number of faces of the cylinder
static const int n_div   =  100;  // This determines the fineness of the cylinder along its length
static const int StartingPosition = -80;
GLUquadric* qobj;


void OrthoDemoWidget::updateAngle(){
  _angleWh -= 1.0; //clockwise
  // _time +=0.25;
  // printf("UpdateAngle %f\n", _angleWh);
  this->repaint();
}
// cia widget.cpp
void OrthoDemoWidget::zoomIn(int d){
  _scaler = 1 + d -pow(d, 0.97);
  printf("ZoomIn %f, %d\n", _scaler, d);
  this->repaint();
}

void OrthoDemoWidget::moveVehicle(int i){
  _movement = i*0.1 + StartingPosition;
  printf("MoveVehicl: %f, %f\n", _movement, i);
  // printf("%f\n", _movement);
  this->repaint();
}

void OrthoDemoWidget::updateAngleManual(int i){
  _angle = 3*i;
  printf("updateAngleManual: %f, %f\n", _angle, i);
  this->repaint();
}


// Setting up material properties
typedef struct materialStruct {
  GLfloat ambient[4];
  GLfloat diffuse[4];
  GLfloat specular[4];
  GLfloat shininess;
} materialStruct;


static materialStruct brassMaterials = {
  { 0.33, 0.22, 0.03, 1.0},
  { 0.78, 0.57, 0.11, 1.0},
  { 0.99, 0.91, 0.81, 1.0},
  27.8
};

static materialStruct whiteShinyMaterials = {
  { 1.0, 1.0, 1.0, 1.0},
  { 1.0, 1.0, 1.0, 1.0},
  { 1.0, 1.0, 1.0, 1.0},
  100.0
};


static materialStruct blueShinyMaterials = {
  { 0.0, 0.0, 0.5, 0.0},
  { 0.0, 0.0, 1.0, 0.0},
  { 0.0, 0.0, 1.0, 0.0},
  100.0
};


static materialStruct greenShinyMaterials = {
  { 0.0, 0.0, 0.0, 0.0},
  { 1.0, 1.0, 1.0, 1.0},
  { 0.0, 0.0, 0.0, 0.0},
  100.0
};


static materialStruct redShinyMaterials = {
  { 1.0, 0.0, 0.0, 0.0},
  { 1.0, 0.0, 0.0, 0.0},
  { 1.0, 0.0, 0.0, 0.0},
  100.0
};

// constructor
OrthoDemoWidget::OrthoDemoWidget(QWidget *parent)
  : QGLWidget(parent),
    _ortho_par(-90.,0.,-45, 45,-200.,200),
    _glupar(0.,0.,100.,0.,0.,0.,0.,1.,0.),
    _b_lighting(true),
    _angle(0.0),
    _angleWh(0.0),
    _time(0),
    _scaler(1.0),
    _movement(StartingPosition)
	{ // constructor


	} // constructor

// called when OpenGL context is set up
void OrthoDemoWidget::initializeGL()
	{ // initializeGL()
	// set the widget background colour
	glClearColor(0.3, 0.3, 0.3, 0.0);
    glColor3f(1.0, 1.0, 1.0);
    //
    // // Set the camera lens to have a 60 degree (vertical) field of view, an
    // // aspect ratio of 4/3, and have everything closer than 1 unit to the
    // // camera and greater than 40 units distant clipped away.
    glMatrixMode(GL_PROJECTION);
    // glLoadIdentity();
    // gluPerspective(60, 1, 1, 40);
    qobj = gluNewQuadric();
    gluQuadricNormals(qobj, GLU_SMOOTH);
    // // Position camera at (4, 6, 5) looking at (0, 0, 0) with the vector
    // // <0, 1, 0> pointing upward.
    // glMatrixMode(GL_MODELVIEW);
    // glLoadIdentity();
    // gluLookAt(60, 6, 5, 1000, 1000, 1000, 0, 100, 0);


	// glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

	glOrtho(_ortho_par._x_min,
		_ortho_par._x_max,
		_ortho_par._y_min,
		_ortho_par._y_max,
		_ortho_par._z_min,
		_ortho_par._z_max);
  // glOrtho(-100.,100.,-100.,100.,-200.,200);

} // initializeGL()


// called every time the widget is resized
void OrthoDemoWidget::resizeGL(int w, int h)
	{ // resizeGL()
	// set the viewport to the entire widget
	glViewport(0, 0, w, h);

	glEnable(GL_LIGHTING); // enable lighting in general
        glEnable(GL_LIGHT0);   // each light source must also be enabled
	glEnable(GL_LIGHT1);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	materialStruct* p_front = &brassMaterials;

  GLfloat qa[] = {0.2, 0.2, 0.9, 1};
  glLightfv(GL_LIGHT0, GL_DIFFUSE, qa);

	GLfloat light_pos[] = {100, -200, 60, 1.};
	glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
	// light_pos[0] = -300;
	// light_pos[1] = -300;
	// glLightfv(GL_LIGHT1,GL_POSITION, light_pos);

	} // resizeGL()

void OrthoDemoWidget::cylinder(float scale, float length, const materialStruct& material){

  if (_b_lighting)
    glEnable(GL_LIGHTING);
  else
    glDisable(GL_LIGHTING);

  glMaterialfv(GL_FRONT, GL_AMBIENT,    material.ambient); //spalvos tsg
  glMaterialfv(GL_FRONT, GL_DIFFUSE,    material.diffuse);
  glMaterialfv(GL_FRONT, GL_SPECULAR,   material.specular);
  glMaterialf(GL_FRONT, GL_SHININESS,   material.shininess);

  //obj, base(bottom), base(top), length(height), slices, stacks?
  gluCylinder(qobj, scale, scale, length, 10, 1);
}

void OrthoDemoWidget::hexo(float inner, float outer, float nsides, float rings, const materialStruct& material){

  if (_b_lighting)
    glEnable(GL_LIGHTING);
  else
    glDisable(GL_LIGHTING);
  glMaterialfv(GL_FRONT, GL_AMBIENT,    material.ambient);
  glMaterialfv(GL_FRONT, GL_DIFFUSE,    material.diffuse);
  glMaterialfv(GL_FRONT, GL_SPECULAR,   material.specular);
  glMaterialf(GL_FRONT, GL_SHININESS,   material.shininess);

  // glutSolidTorus(inner, outer, nsides, rings);
  glutSolidTorus(inner, outer, nsides, rings);
  glutSolidTorus(inner/2, outer*2, 16, 16);
  // radius, slices, stacks
  glutSolidSphere((outer-inner)*2, 36, 32);

}

void OrthoDemoWidget::windowsPoly(float side, const materialStruct& material){
  if (_b_lighting)
    glEnable(GL_LIGHTING);
  else
    glDisable(GL_LIGHTING);

  glMaterialfv(GL_FRONT, GL_AMBIENT,    material.ambient);
  glMaterialfv(GL_FRONT, GL_DIFFUSE,    material.diffuse);
  glMaterialfv(GL_FRONT, GL_SPECULAR,   material.specular);
  glMaterialf(GL_FRONT, GL_SHININESS,   material.shininess);

// FRONT window
  glBegin(GL_POLYGON);//1
    glVertex3f(6,8,side);
    glVertex3f(6,8,-side);
    glVertex3f(19.5,12,-side);
    glVertex3f(19.5,12,side);
  glEnd();

  glBegin(GL_TRIANGLES);//1.1
    glVertex3f(7,8,side);
    glVertex3f(19,8,side);
    glVertex3f(19,11.5,side);
  glEnd();
  glBegin(GL_TRIANGLES);//1.2
    glVertex3f(35.5,8,side);
    glVertex3f(20,11.5,side);
    glVertex3f(20,8,side);
  glEnd();

  glBegin(GL_TRIANGLES);//2.1
    glVertex3f(7,8,-side);
    glVertex3f(19,8,-side);
    glVertex3f(19,11.5,-side);
  glEnd();
  glBegin(GL_TRIANGLES);//2.2
    glVertex3f(35.5,8,-side);
    glVertex3f(20,11.5,-side);
    glVertex3f(20,8,-side);
  glEnd();



}

void OrthoDemoWidget::roof(float side, const materialStruct& material){
  if (_b_lighting)
    glEnable(GL_LIGHTING);
  else
    glDisable(GL_LIGHTING);

  glMaterialfv(GL_FRONT, GL_AMBIENT,    material.ambient); //spalvos tsg
  glMaterialfv(GL_FRONT, GL_DIFFUSE,    material.diffuse);
  glMaterialfv(GL_FRONT, GL_SPECULAR,   material.specular);
  glMaterialf(GL_FRONT, GL_SHININESS,   material.shininess);

  glBegin(GL_POLYGON);//1
    glVertex3f(2,1,side);
    glVertex3f(2,1,-side);
    glVertex3f(0.5,1.5,-side);
    glVertex3f(0.5,1.5,side);
  glEnd();

  glBegin(GL_POLYGON);//2
    glVertex3f(0.5,1.5,side);
    glVertex3f(0.5,1.5,-side);
    glVertex3f(0,5.5,-side);
    glVertex3f(0,5.5,side);
  glEnd();

  glBegin(GL_POLYGON);//3
    glVertex3f(0,5.5,side);
    glVertex3f(0,5.5,-side);
    glVertex3f(2,7,-side);
    glVertex3f(2,7,side);
  glEnd();

  glBegin(GL_POLYGON);//3.5 (pre-window)
    glVertex3f(2,7,side);
    glVertex3f(2,7,-side);
    glVertex3f(7,8,-side);
    glVertex3f(7,8,side);
  glEnd();

// FRONT WINDOW
  // glColor3i(100,100,20);
  // glBegin(GL_POLYGON);//4
  //   glVertex3f(7,8,8.14);
  //   glVertex3f(7,8,-8.14);
  //   glVertex3f(19.5,12.5,-8.14);
  //   glVertex3f(19.5,12.5,8.14);
  // glEnd();

  glBegin(GL_POLYGON);//5
    glVertex3f(19.5,12.5,side);
    glVertex3f(19.5,12.5,-side);
    glVertex3f(29,11,-side);
    glVertex3f(29,11,side);
  glEnd();

  glBegin(GL_POLYGON);//6
    glVertex3f(29,11,side);
    glVertex3f(29,11,-side);
    glVertex3f(29,7,-side);
    glVertex3f(29,7,side);
  glEnd();

  glBegin(GL_POLYGON);//7
    glVertex3f(29,7,side);
    glVertex3f(29,7,-side);
    glVertex3f(47,7,-side);
    glVertex3f(47,7,side);
  glEnd();

// BACK
  // glBegin(GL_POLYGON);//8
  //   glVertex3f(29,7,8.14);
  //   glVertex3f(29,7,-8.14);
  //   glVertex3f(47,7,-8.14);
  //   glVertex3f(47,7,8.14);
  // glEnd();

  glBegin(GL_POLYGON);//9
    glVertex3f(46,3,side);
    glVertex3f(46,3,-side);
    glVertex3f(43,0.5,-side);
    glVertex3f(43,0.5,side);
  glEnd();


}

void OrthoDemoWidget::sideUPPoly(float side, const materialStruct& material){
  if (_b_lighting)
    glEnable(GL_LIGHTING);
  else
    glDisable(GL_LIGHTING);

  glMaterialfv(GL_FRONT, GL_AMBIENT,    material.ambient); //spalvos tsg
  glMaterialfv(GL_FRONT, GL_DIFFUSE,    material.diffuse);
  glMaterialfv(GL_FRONT, GL_SPECULAR,   material.specular);
  glMaterialf(GL_FRONT, GL_SHININESS,   material.shininess);

  glBegin(GL_TRIANGLES);//1
    glVertex3f(7,7,side);
    glVertex3f(6,8,side);
    glVertex3f(19.5,12.5,side);
  glEnd();
  glBegin(GL_TRIANGLES);//2
    glVertex3f(7,7,side);
    glVertex3f(19,11,side);
    glVertex3f(19.5, 12.5,side);
  glEnd();
  glBegin(GL_TRIANGLES);//3
    glVertex3f(19,11,side);
    glVertex3f(20,11,side);
    glVertex3f(19.5,12.5,side);
  glEnd();
  glBegin(GL_TRIANGLES);//4
    glVertex3f(19,11,side);
    glVertex3f(20,8,side);
    glVertex3f(20,11,side);
  glEnd();
  glBegin(GL_TRIANGLES);//5
    glVertex3f(19,11,side);
    glVertex3f(19,8,side);
    glVertex3f(20,8,side);
  glEnd();
  glBegin(GL_TRIANGLES);//6
    glVertex3f(19.5,12.5,side);
    glVertex3f(20.5,11,side);
    glVertex3f(47,9,side);
  glEnd();
  glBegin(GL_TRIANGLES);//7
    glVertex3f(20,11,side);
    glVertex3f(35.5,8,side);
    glVertex3f(47,9,side);
  glEnd();
  glBegin(GL_TRIANGLES);//8
    glVertex3f(47,8,side);
    glVertex3f(47,9,side);
    glVertex3f(35.5,8,side);
  glEnd();
}
void OrthoDemoWidget::sideGroundPoly(float side, const materialStruct& material){
  if (_b_lighting)
    glEnable(GL_LIGHTING);
  else
    glDisable(GL_LIGHTING);

  glMaterialfv(GL_FRONT, GL_AMBIENT,    material.ambient); //spalvos tsg
  glMaterialfv(GL_FRONT, GL_DIFFUSE,    material.diffuse);
  glMaterialfv(GL_FRONT, GL_SPECULAR,   material.specular);
  glMaterialf(GL_FRONT, GL_SHININESS,   material.shininess);

  glBegin(GL_TRIANGLES); //1
    glVertex3f(0,5.5,side);
    glVertex3f(2,5.5,side);
    glVertex3f(2,7,side);
  glEnd();
  glBegin(GL_TRIANGLES);//2
    glVertex3f(0,5.5,side);
    glVertex3f(2,1,side);
    glVertex3f(2,5.5,side);
  glEnd();
  glBegin(GL_TRIANGLES);//3
    glVertex3f(0.5,1.5,side);
    glVertex3f(2,1,side);
    glVertex3f(0,5.5,side);
  glEnd();
  glBegin(GL_TRIANGLES);//4
    glVertex3f(2,3,side);
    glVertex3f(2,5.5,side);
    glVertex3f(3.5,5.5,side);
  glEnd();
  glBegin(GL_TRIANGLES);//5
    glVertex3f(2,5.5,side);
    glVertex3f(11,5.5,side);
    glVertex3f(2,7,side);
  glEnd();
  glBegin(GL_TRIANGLES);//6
    glVertex3f(11,5.5,side);
    glVertex3f(11,7,side);
    glVertex3f(2,7,side);
  glEnd();
  glBegin(GL_TRIANGLES);//6.5 (the forgotten)
    glVertex3f(9,5.5,side);
    glVertex3f(11,2,side);
    glVertex3f(11,5.5,side);
  glEnd();

  // FIRST Doors
  glBegin(GL_TRIANGLES);//7
    glVertex3f(11,0,side);
    glVertex3f(19,0,side);
    glVertex3f(11,7,side);
  glEnd();
  glBegin(GL_TRIANGLES);//8
    glVertex3f(19,0,side);
    glVertex3f(19,7,side);
    glVertex3f(11,7,side);
  glEnd();
  //SECOND Doors
  glBegin(GL_TRIANGLES);//9
    glVertex3f(19,7,side);
    glVertex3f(19,0,side);
    glVertex3f(28,0,side);
  glEnd();
  glBegin(GL_TRIANGLES);//10
    glVertex3f(28,0,side);
    glVertex3f(28,7,side);
    glVertex3f(19,7,side);
  glEnd();
  //THIRD
  glBegin(GL_TRIANGLES);//11
    glVertex3f(28,0,side);
    glVertex3f(34,0,side);
    glVertex3f(28,7,side);
  glEnd();
  glBegin(GL_TRIANGLES);//12
    glVertex3f(34,7,side);
    glVertex3f(28,7,side);
    glVertex3f(34,0,side);
  glEnd();
  glBegin(GL_TRIANGLES);//13
    glVertex3f(34,3,side);
    glVertex3f(34,7,side);
    glVertex3f(37,7,side);
  glEnd();
  glBegin(GL_TRIANGLES);//14
    glVertex3f(36,5.5,side);
    glVertex3f(37,7,side);
    glVertex3f(41,5.5,side);
  glEnd();
  glBegin(GL_TRIANGLES);//15
    glVertex3f(41,5.5,side);
    glVertex3f(37,7,side);
    glVertex3f(41,7,side);
  glEnd();
  glBegin(GL_TRIANGLES);//16
    glVertex3f(41,7,side);
    glVertex3f(41,5.5,side);
    glVertex3f(43,5.5,side);
  glEnd();
  glBegin(GL_TRIANGLES);//17
    glVertex3f(41,5.5,side);
    glVertex3f(43,5.5,side);
    glVertex3f(43,3,side);
  glEnd();
  glBegin(GL_TRIANGLES);//18
    glVertex3f(43, 5.5,side);
    glVertex3f(43,3,side);
    glVertex3f(46,3,side);
  glEnd();
  glBegin(GL_TRIANGLES);//19
    glVertex3f(43,0.5,side);
    glVertex3f(46,3,side);
    glVertex3f(43,3,side);
  glEnd();
  glBegin(GL_TRIANGLES);//20
    glVertex3f(46,3,side);
    glVertex3f(47,7,side);
    glVertex3f(41,7,side);
  glEnd();

//NOW THE MIDDLE AREA BETWEEN GROUNDSIDE AND WINDOW
  glBegin(GL_TRIANGLES);
    glVertex3f(2,7,side);
    glVertex3f(47,7,side);
    glVertex3f(47,8,side);
  glEnd();
  glBegin(GL_TRIANGLES);
    glVertex3f(47,8,side);
    glVertex3f(6,8,side);
    glVertex3f(2,7,side);
  glEnd();

}


float OrthoDemoWidget::wheelRotateAngle(float size){
  // float angle;
  // float movementSize = 1; //should be automatic (maybe global variable)
  _angleWh = -1*(_movement*360)/(2*PI*size);
  // printf("%f, %f\n", -1*(_movement*360)/(2*PI*size), _movement);
  return _angleWh;
}

void OrthoDemoWidget::wheelAxes(float wheelWidth, float whichWheel, float ZaxisPosition, float wheelSize){

  //left axis
  glPushMatrix();
     glTranslatef(whichWheel, 0, -ZaxisPosition);
     glRotatef(wheelRotateAngle(wheelSize), 0,0,1);
    this->hexo(wheelWidth, wheelSize, 3, 6, blueShinyMaterials);
  glPopMatrix();

  glPushMatrix(); //sitas pisa i centra
    glTranslatef(whichWheel, 0, ZaxisPosition);
    glRotatef(wheelRotateAngle(wheelSize), 0,0,1);
    this->hexo(wheelWidth, wheelSize, 3, 6, whiteShinyMaterials);
  glPopMatrix();

  glPushMatrix();
    glTranslatef(whichWheel, 0, -ZaxisPosition);
    this->cylinder(1, ZaxisPosition*2, redShinyMaterials);
  glPopMatrix();

}

void OrthoDemoWidget::unify(double time){

  int rot[3] = {1,0,0}; //for rotating

  glLoadIdentity();
  glMatrixMode(GL_MODELVIEW);
  gluLookAt(0,4,4,  0,3,0,  0,1,0);

  glPushMatrix(); //left wheelset
    glTranslatef(_movement, 0, 0);
    glScalef(_scaler, _scaler, _scaler);
    glRotatef(_angle, rot[0], rot[1], rot[2]);
    this->wheelAxes(1, 6.5, 8.14, 1.8);
    //I can create a separate PushPop, if vehicle would drive while rotating each side differently
    this->wheelAxes(1, 38.5, 8.14, 1.8);
  glPopMatrix();

  glPushMatrix(); //vehicle side
    glTranslatef(_movement, 0, 0);
    glRotatef(_angle, rot[0], rot[1], rot[2]);
    glScalef(_scaler, _scaler, _scaler);
    this->sideGroundPoly(-8.14, greenShinyMaterials);
    this->sideGroundPoly(8.14, blueShinyMaterials);
    this->sideUPPoly(-8.14, redShinyMaterials);
    this->sideUPPoly(8.14, redShinyMaterials);
    this->roof(8.14, whiteShinyMaterials);
    this->windowsPoly(8.14, greenShinyMaterials);
  glPopMatrix();

}

// called every time the widget needs painting
void OrthoDemoWidget::paintGL()
	{ // paintGL()
	// clear the widget
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glEnable(GL_NORMALIZE);

        glShadeModel(GL_FLAT);
        	// You must set the matrix mode to model view directly before enabling the depth test
      	glMatrixMode(GL_MODELVIEW);
       	glEnable(GL_DEPTH_TEST); // comment out depth test to observe the result

        //SETTING UP THE PLANE
        glPushMatrix();
        glColor3f(0.5f, 0.0f, 1.0f);
        glScalef(_scaler, _scaler, _scaler);
        glBegin(GL_POLYGON);
        glColor3f(1.0f, 0.99f, 1.0f);
          glVertex3f(-100, -5, 100);
          glColor3f(1.0f, 0.99f, 1.0f);
          glVertex3f(100, -5, 100);
          glColor3f(1.0f, 0.99f, 1.0f);
          glVertex3f(100, -5, -100);
          glColor3f(1.0f, 0.99f, 1.0f);
          glVertex3f(-100, -5, -100);
        glEnd();
        glPopMatrix();

        unify(_time);
	glFlush();

	} // paintGL()

void OrthoDemoWidget::mouseDoubleClickEvent (QMouseEvent* event )
{
  QDialog *widget = new QDialog;
  _ui.setupUi(widget);
  this->LoadDialog(_ui);
  widget->exec();
  this->UnloadDialog(_ui);
}

void OrthoDemoWidget::LoadDialog(const Ui_Dialog& dialog)
{
  _ui.xmin->setText(QString::number(_ortho_par._x_min));
  _ui.xmax->setText(QString::number(_ortho_par._x_max));
  _ui.ymin->setText(QString::number(_ortho_par._y_min));
  _ui.ymax->setText(QString::number(_ortho_par._y_max));
  _ui.zmin->setText(QString::number(_ortho_par._z_min));
  _ui.zmax->setText(QString::number(_ortho_par._z_max));
  _ui.pos1->setText(QString::number(_glupar._x));
  _ui.pos2->setText(QString::number(_glupar._y));
  _ui.pos3->setText(QString::number(_glupar._z));
  _ui.at1->setText(QString::number(_glupar._at_x));
  _ui.at2->setText(QString::number(_glupar._at_y));
  _ui.at3->setText(QString::number(_glupar._at_z));
  _ui.up1->setText(QString::number(_glupar._up_x));
  _ui.up2->setText(QString::number(_glupar._up_y));
  _ui.up3->setText(QString::number(_glupar._up_z));
  _ui.blight->setCheckState(_b_lighting ? Qt::Checked : Qt::Unchecked);
}

void OrthoDemoWidget::UnloadDialog(const Ui_Dialog& dialog)
{
  _ortho_par._x_min = dialog.xmin->toPlainText().toFloat();
  _ortho_par._y_min = dialog.ymin->toPlainText().toFloat();
  _ortho_par._z_min = dialog.zmin->toPlainText().toFloat();
  _ortho_par._x_max = dialog.xmax->toPlainText().toFloat();
  _ortho_par._y_max = dialog.ymax->toPlainText().toFloat();
  _ortho_par._z_max = dialog.zmax->toPlainText().toFloat();
  _glupar._x = dialog.pos1->toPlainText().toFloat();
  _glupar._y = dialog.pos2->toPlainText().toFloat();
  _glupar._z = dialog.pos3->toPlainText().toFloat();
  _glupar._at_x = dialog.at1->toPlainText().toFloat();
  _glupar._at_y = dialog.at2->toPlainText().toFloat();
  _glupar._at_z = dialog.at3->toPlainText().toFloat();
  _glupar._up_x = dialog.up1->toPlainText().toFloat();
  _glupar._up_y = dialog.up2->toPlainText().toFloat();
  _glupar._up_z = dialog.up3->toPlainText().toFloat();
  _b_lighting = (_ui.blight->checkState() == Qt::Checked) ? true : false;
}
