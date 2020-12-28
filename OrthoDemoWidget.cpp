#include <GL/glut.h>
#include <QGLWidget>
#include <QDebug>
#include <cmath>
#include "OrthoDemoWidget.h"
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

// TODO list:
/*
==NOT DONE==
lighting (normals and normalise)
textures
wheels to turn by 'radius' angle
wheels to spin acordingly
make a stop and play button
Windows with glTranslatef
Back with hierarchical
Doors with hierarchical


==HALF DONE==
Plane with color

*/

static const GLfloat radius = 2;
static const float speed = 0.4;
static const float PI = 3.1415926535;
static const int N        = 100; // This determines the number of faces of the cylinder
static const int n_div   =  100;  // This determines the fineness of the cylinder along its length
static const int StartingPosition = -80;
GLUquadric* qobj;
static const int rot[3] = {0,1,0}; //for rotating
float TotalDistance =0;

void OrthoDemoWidget::updateCameraYAngle(int angle){
  _y_camera_angle = angle;
  this->repaint();
}

// For infinite rotation(has to be set)
void OrthoDemoWidget::updateAngle(){
  float Wheelsize = 1;
  TotalDistance += speed;
  _angleWhole = TotalDistance;
  _wheelRotate = -360*(int(TotalDistance)%360)/(2*PI*Wheelsize);
  // printf("UpdateAngle %f, %f\n", _angleWhole, _wheelRotate);
  this->repaint();
}

void OrthoDemoWidget::doorsOpen(int d){
  _doorsAngle = _doorsAngle%360 + 1;
  printf("%f %i\n", _doorsAngle, d);
  this->repaint();
}

// when zooming in
void OrthoDemoWidget::zoomIn(int d){
  _scaler = 1 + d -pow(d, 0.97);
  printf("ZoomIn %f, %d\n", _scaler, d);
  this->repaint();
}
//
// Moving the vehicle among the x axis
// void OrthoDemoWidget::moveVehicle(int i){
//   _movement = i*0.25 + StartingPosition;
//   printf("MoveVehicl: %f, %f\n", _movement, i);
//   this->repaint();
// }

// void OrthoDemoWidget::updateAngleManual(int i){
//   _angle = 3*i;
//   printf("updateAngleManual: %f, %f\n", _angle, i);
//   this->repaint();
// }

float OrthoDemoWidget::wheelRotateAngle(float size){
  // printf("%f, %f\n", -1*(_movement*360)/(2*PI*size), _movement);
  //TODO:_scaler is running two functions (way to avoid is to get rid of widget and do UI menu)
  // _wheelRotate = 360*(int(TotalDistance)%360)/(2*PI*Wheelsize);
  // return -1*(_movement*360)/(2*PI*size)/_scaler;
  return 360/(2*PI*size);
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
    _b_lighting(true),
    _angle(0.0),
    _time(0),
    _scaler(1.0),
    _wheelRotate(0),
    _doorsAngle(0),
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



	// glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
    glOrtho(-100.,100.,-100.,100.,-200.,200);

} // initializeGL()


// called every time the widget is resized
void OrthoDemoWidget::resizeGL(int w, int h){

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

  glMaterialfv(GL_FRONT, GL_AMBIENT,    material.ambient);
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

//TODO there should be hierarchical modeling of the back

// BACK
  glBegin(GL_POLYGON);//8
    glVertex3f(47,7,side);
    glVertex3f(47,7,-side);
    glVertex3f(46,3,-side);
    glVertex3f(46,3,side);
  glEnd();

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
  glPushMatrix();
    glRotatef(_doorsAngle, 0,1,0);
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
  glPopMatrix();
  
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


void OrthoDemoWidget::wheelAxes(float wheelWidth, float whichWheel, float ZaxisPosition, float wheelSize){

  //left axis
  glPushMatrix();
     glTranslatef(whichWheel, 0, -ZaxisPosition);
     // glRotatef(wheelRotateAngle(wheelSize), 0,0,1);
     glRotatef(_wheelRotate, 0,0,1);
    this->hexo(wheelWidth, wheelSize, 3, 6, blueShinyMaterials);
  glPopMatrix();

  glPushMatrix(); //sitas pisa i centra
    glTranslatef(whichWheel, 0, ZaxisPosition);
    // glRotatef(wheelRotateAngle(wheelSize), 0,0,1);
    glRotatef(_wheelRotate, 0,0,1);
    this->hexo(wheelWidth, wheelSize, 3, 6, whiteShinyMaterials);
  glPopMatrix();

  glPushMatrix();
    glTranslatef(whichWheel, 0, -ZaxisPosition);
    this->cylinder(1, ZaxisPosition*2, redShinyMaterials);
  glPopMatrix();

}

void OrthoDemoWidget::unify(double time){

  glLoadIdentity();
  // glMatrixMode(GL_MODELVIEW);

  glPushMatrix();
    // glTranslatef(_movement, 0, 0);
    // glScalef(_scaler, _scaler, _scaler);
    // glRotatef(_angleWhole, rot[0], rot[1], rot[2]);

    glRotatef(_y_camera_angle, 1., 0., 0.);
    glRotatef(_angleWhole, 0., 1., 0.); //change _angle or _angleWhole
    glTranslatef(_movement, radius, 0);
    glScalef(_scaler,_scaler,_scaler);
    //
    glRotatef(90, 0,1,0);//Rotate the car itself
    this->wheelAxes(1, 6.5, 8.14, 1.8);
    this->wheelAxes(1, 38.5, 8.14, 1.8);

    this->sideGroundPoly(-8.14, greenShinyMaterials);
    this->sideGroundPoly(8.14, blueShinyMaterials);

    this->sideUPPoly(-8.14, redShinyMaterials);
    this->sideUPPoly(8.14, redShinyMaterials);

    this->roof(8.14, whiteShinyMaterials);

    this->windowsPoly(8.14, greenShinyMaterials);

  glPopMatrix();

}

// called every time the widget needs painting
void OrthoDemoWidget::paintGL(){
	// clear the widget
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glEnable(GL_NORMALIZE);

  glShadeModel(GL_FLAT);
	glMatrixMode(GL_MODELVIEW);
 	glEnable(GL_DEPTH_TEST);


  glLoadIdentity();
  gluLookAt(0,100,0,  0,0,0,  0,0,1);
  // gluLookAt(0., 5., 0.0, 0.0,0.0,0.0, 0.0,0.0,1.0);
  // glRotatef(_y_camera_angle, 1., 0., 0.);

  renderPlane(whiteShinyMaterials);

  unify(_time);
	glFlush();
}

void OrthoDemoWidget::renderPlane(const materialStruct& material){

  glMaterialfv(GL_FRONT, GL_AMBIENT,    material.ambient);
  glMaterialfv(GL_FRONT, GL_DIFFUSE,    material.diffuse);
  glMaterialfv(GL_FRONT, GL_SPECULAR,   material.specular);
  glMaterialf(GL_FRONT, GL_SHININESS,   material.shininess);


  GLfloat normals[][3] = { {0., 1. ,0.} };
  glNormal3fv(normals[0]);
  glBegin(GL_POLYGON);
    glVertex3f(-100, -100, 0);
    glVertex3f(100, -100, 0);
    glVertex3f(100, 100, 0);
    glVertex3f(-100,  100, 0);
  glEnd();
}
