#include <GL/glut.h>
#include <QGLWidget>
#include <QDebug>
#include <iostream>
#include <cmath>
#include "VehicleWidget.h"
#include "Drawings.h"
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <array>

static const int StartingPosition = 80;
static const float PI = 3.1415926535;

float vehicleWidth=8.14;
float speed = 0.7;
float TotalDistance = 0;
GLfloat radius = 50;
GLUquadric* qobj;


// constructor
VehicleWidget::VehicleWidget(QWidget *parent)
  : QGLWidget(parent),
    _b_lighting(true),
    _b_textures(true),
    _b_obstacles(true),
    _angle(0.0),
    _scaler(1.0),
    _wheelRotate(0),
    _doorsAngle(0),
    _windowTranslate(0),
    _bootTranslate(0),
    _movement(StartingPosition),
    _rotateLight(0),
    _rotateEarth(0),
    _imageMarc("textures/Marc.ppm"),
    _imageRaceTrack("textures/race.png"),
    _imageMap("textures/Map.ppm")
	{

} // constructor


void VehicleWidget::updateCameraYAngle(int angle){
  _y_camera_angle = angle;
  this->repaint();
}

void VehicleWidget::updateCameraXAngle(int angle){
  _x_camera_angle = angle;
  this->repaint();
}

// Wheel spinning and whole vehicle move
void VehicleWidget::updateAngle(){
  float Wheelsize = 1;
  TotalDistance += speed;
  _angleWhole = (TotalDistance);
  _wheelRotate += 2*speed*(2*PI*Wheelsize);
  this->repaint();
}

//Rotating Light
void VehicleWidget::updateAngleLight(){
  //rotating slow and in different direction than earth
  _rotateLight -=0.5;
  this->repaint();
}

//Rotating Earth
void VehicleWidget::updateAngleEarth(){
  //rotating slower than light but in the same direction than vehicle
  _rotateEarth +=0.25;
  this->repaint();
}

void VehicleWidget::doorsOpen(int d){
  _doorsAngle = d;
  this->repaint();
}

void VehicleWidget::zoomIn(int d){
  _scaler = 1 + 0.1*d;//gradual zoom out/in
  this->repaint();
}

void VehicleWidget::windowTranslate(int d){
  _windowTranslate = d;
  this->repaint();
}

void VehicleWidget::openBoot(int d){
  _bootTranslate = d;
  this->repaint();
}


// Setting up material properties
typedef struct materialStruct {
  GLfloat ambient[4];
  GLfloat diffuse[4];
  GLfloat specular[4];
  GLfloat shininess;
} materialStruct;

static materialStruct dark0SteelMaterials ={
  { 0.1, 0.1, 0.1, 0.0},
  { 0.1, 0.1, 0.1, 0.0},
  { 0.1, 0.1, 0.1, 0.0},
  50
};

static materialStruct dark1SteelMaterials ={
  { 0.5, 0.5, 0.5, 0.0},
  { 0.1, 0.1, 0.1, 0.0},
  { 0.2, 0.2, 0.2, 0.0},
  10
};
static materialStruct mediumSteelMaterials ={
  { 0.3, 0.3, 0.3, 1.0},
  { 0.5, 0.5, 0.5, 1.0},
  { 0.3, 0.3, 0.3, 1.0},
  30
};
static materialStruct light0SteelMaterials ={
  { 0.3, 0.3, 0.3, 1.0},
  { 0.8, 0.8, 0.8, 1.0},
  { 0.5, 0.5, 0.5, 1.0},
  20
};

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
static materialStruct blackMaterial = {
  { 0.0, 0.0, 0.0, 0.0},
  { 0.0, 0.0, 0.0, 0.0},
  { 0.0, 0.0, 0.0, 0.0},
  100.0
};
static materialStruct redShinyMaterials = {
  { 1.0, 0.0, 0.0, 0.0},
  { 1.0, 0.0, 0.0, 0.0},
  { 1.0, 0.0, 0.0, 0.0},
  100.0
};

// called when OpenGL context is set up
void VehicleWidget::initializeGL()
	{
	// set the widget background colour as BLACK
	glClearColor(0, 0, 0, 0.0);

  qobj = gluNewQuadric();
  gluQuadricNormals(qobj, GLU_SMOOTH);

	glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(-100.,100.,-100.,100.,-600.,600);
}


// called every time the widget is resized
void VehicleWidget::resizeGL(int w, int h){
  glViewport(0, 0, w, h);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

  //Textures
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
}

void VehicleWidget::drawWheel(float inner, float outer, float nsides, float rings, const materialStruct& material1, const materialStruct& material2){

  glMaterialfv(GL_FRONT, GL_AMBIENT,    material1.ambient);
  glMaterialfv(GL_FRONT, GL_DIFFUSE,    material1.diffuse);
  glMaterialfv(GL_FRONT, GL_SPECULAR,   material1.specular);
  glMaterialf(GL_FRONT, GL_SHININESS,   material1.shininess);

  // glutSolidTorus(inner, outer, nsides, rings);
  glutSolidTorus(inner/2, outer*2, 16, 16);

  // radius, slices, stacks
  glutSolidSphere((outer-inner)*2, 36, 32);

  glMaterialfv(GL_FRONT, GL_AMBIENT,    material2.ambient);
  glMaterialfv(GL_FRONT, GL_DIFFUSE,    material2.diffuse);
  glMaterialfv(GL_FRONT, GL_SPECULAR,   material2.specular);
  glMaterialf(GL_FRONT, GL_SHININESS,   material2.shininess);
  glutSolidTorus(inner, outer, nsides, rings);
}

void VehicleWidget::sphereWithTexture(){

    GLUquadricObj *gobj=gluNewQuadric();

    gluQuadricDrawStyle(gobj,GLU_FILL);
    gluQuadricNormals(gobj,GLU_SMOOTH);
    gluQuadricTexture(gobj,GL_TRUE);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, _imageMap.Width(), _imageMap.Height(), 0, GL_RGB, GL_UNSIGNED_BYTE, _imageMap.imageField());

    glEnable(GL_TEXTURE_2D);
    gluSphere(gobj,0.75f,32,32);

    glFinish();
    glDisable(GL_TEXTURE_2D);
    gluDeleteQuadric(gobj);
}

// Function to calculate normals of a plane given three points
glm::vec3 VehicleWidget::normal3Points(const std::array<double, 9>& params){
  int otherSides = 0; //vertices on the negative z axis side
  // calculating matrices product
  int A=params[3]*params[1] + params[6]*params[4] + params[0]*params[7];
  int B=params[0]*params[4] + params[3]*params[7] + params[6]*params[1];

  // Adding one to the vertices on the negative z axis
  otherSides += (params[2]<0)?1:0;
  otherSides += (params[5]<0)?1:0;
  otherSides += (params[8]<0)?1:0;

// if there are more vertices on positive side, and its couterclockwise
//or if there are more negatives and its clockwise
  if((otherSides<2 && A<=B) || (otherSides>1 && A>=B)){
    glm::vec3 v1 = {params[0], params[1], params[2]};
    glm::vec3 v2 = {params[3], params[4], params[5]};
    glm::vec3 v3 = {params[6], params[7], params[8]};

  return glm::normalize(glm::cross(v2 - v1, v3 - v2));
  }
  else {
    // if there are less vertices on positive side, and its clockwise
    //or if there are more vertices on positive side and its counterclockwise
    glm::vec3 v2 = {params[0], params[1], params[2]};
    glm::vec3 v1 = {params[3], params[4], params[5]};
    glm::vec3 v3 = {params[6], params[7], params[8]};

  return glm::normalize(glm::cross(v2 - v1, v3 - v2));
  }
}

// static windows of a vehicle
void VehicleWidget::vehicleStatWindows(float side, const materialStruct& material){

  glMaterialfv(GL_FRONT, GL_AMBIENT,    material.ambient);
  glMaterialfv(GL_FRONT, GL_DIFFUSE,    material.diffuse);
  glMaterialfv(GL_FRONT, GL_SPECULAR,   material.specular);
  glMaterialf(GL_FRONT, GL_SHININESS,   material.shininess);

  if(_b_textures){
    glEnable(GL_TEXTURE_2D);
  }
  else{
    glDisable(GL_TEXTURE_2D);
  }

  //FRONT window
  glNormal3fv(glm::value_ptr(normal3Points({6,8,vehicleWidth,19.5,12.5,vehicleWidth,19.5,12.5,-vehicleWidth})));
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, _imageMarc.Width(), _imageMarc.Height(), 0, GL_RGB, GL_UNSIGNED_BYTE, _imageMarc.imageField());
  glBegin(GL_POLYGON);//1
  glTexCoord2f(0,0);
    glVertex3f(6,8,vehicleWidth);
    glTexCoord2f(0,1);
    glVertex3f(19.5,12.5,vehicleWidth);
    glTexCoord2f(1,1);
    glVertex3f(19.5,12.5,-vehicleWidth);
    glTexCoord2f(1,0);
    glVertex3f(6,8,-vehicleWidth);
  glEnd();
  glDisable(GL_TEXTURE_2D);

  // back windows
  glNormal3fv(glm::value_ptr(normal3Points({35.5,8,side, 20,11,side, 20,8,side})));
  glBegin(GL_TRIANGLES);//1.2
    glVertex3f(35.5,8,side);
    glVertex3f(20,11,side);
    glVertex3f(20,8,side);
  glEnd();
}

// dynamic/translating windows
void VehicleWidget::vehicleDynaWindows(float side, const materialStruct& material){

  glMaterialfv(GL_FRONT, GL_AMBIENT,    material.ambient);
  glMaterialfv(GL_FRONT, GL_DIFFUSE,    material.diffuse);
  glMaterialfv(GL_FRONT, GL_SPECULAR,   material.specular);
  glMaterialf(GL_FRONT, GL_SHININESS,   material.shininess);

  //first dorr windows
  glNormal3fv(glm::value_ptr(normal3Points({11,8,side,19,8,side,19,11,side})));
  glBegin(GL_TRIANGLES);//1.1
    glVertex3f(11,8,side);
    glVertex3f(19,8,side);
    glVertex3f(19,11,side);
  glEnd();
}

// the top of the vehicle boot(the cover)
void VehicleWidget::vehicleBootTop(double d, float side, const materialStruct& material){

  glMaterialfv(GL_FRONT, GL_AMBIENT,    material.ambient);
  glMaterialfv(GL_FRONT, GL_DIFFUSE,    material.diffuse);
  glMaterialfv(GL_FRONT, GL_SPECULAR,   material.specular);
  glMaterialf(GL_FRONT, GL_SHININESS,   material.shininess);

  glNormal3fv(glm::value_ptr(normal3Points({29,11,side,47-0.5*d,9,side,47-0.5*d,9,-side})));
  glBegin(GL_POLYGON);
    glVertex3f(29,11,side);
    glVertex3f(47-0.5*d,9,side);
    glVertex3f(47-0.5*d,9,-side);
    glVertex3f(29,11,-side);
  glEnd();
}

// the bottom of vehicle boot
void VehicleWidget::vehicleBootBottom(float side, const materialStruct& material){

  glMaterialfv(GL_FRONT, GL_AMBIENT,    material.ambient);
  glMaterialfv(GL_FRONT, GL_DIFFUSE,    material.diffuse);
  glMaterialfv(GL_FRONT, GL_SPECULAR,   material.specular);
  glMaterialf(GL_FRONT, GL_SHININESS,   material.shininess);

  glNormal3fv(glm::value_ptr(normal3Points({47,9,side,47,7,side,47,7,-side})));
  glBegin(GL_POLYGON);
    glVertex3f(47,9,side);
    glVertex3f(47,7,side);
    glVertex3f(47,7,-side);
    glVertex3f(47,9,-side);
  glEnd();
}

void VehicleWidget::vehicleRoof(float side, const materialStruct& material){

  glMaterialfv(GL_FRONT, GL_AMBIENT,    material.ambient);
  glMaterialfv(GL_FRONT, GL_DIFFUSE,    material.diffuse);
  glMaterialfv(GL_FRONT, GL_SPECULAR,   material.specular);
  glMaterialf(GL_FRONT, GL_SHININESS,   material.shininess);

  glNormal3fv(glm::value_ptr(normal3Points({2,1,side,0.5,1.5,side,0.5,1.5,-side})));
  glBegin(GL_POLYGON);//1
    glVertex3f(2,1,side);
    glVertex3f(0.5,1.5,side);
    glVertex3f(0.5,1.5,-side);
    glVertex3f(2,1,-side);
  glEnd();

  glNormal3fv(glm::value_ptr(normal3Points({0,5.5,side,0,5.5,-side,0.5,1.5,-side})));
  glBegin(GL_POLYGON);//2
    glVertex3f(0.5,1.5,side);
    glVertex3f(0.5,1.5,-side);
    glVertex3f(0,5.5,-side);
    glVertex3f(0,5.5,side);
  glEnd();

  glNormal3fv(glm::value_ptr(normal3Points({0,5.5,side,2,7,side,2,7,-side})));
  glBegin(GL_POLYGON);//3
    glVertex3f(0,5.5,side);
    glVertex3f(2,7,side);
    glVertex3f(2,7,-side);
    glVertex3f(0,5.5,-side);
  glEnd();

  glNormal3fv(glm::value_ptr(normal3Points({2,7,side,7,8,side,7,8,-side})));
  glBegin(GL_POLYGON);//3.5 (pre-window)
    glVertex3f(2,7,side);
    glVertex3f(2,7,-side);
    glVertex3f(7,8,-side);
    glVertex3f(7,8,side);
  glEnd();

  glNormal3fv(glm::value_ptr(normal3Points({19.5,12.5,side,29,11,side,29,11,-side})));
  glBegin(GL_POLYGON);//5
    glVertex3f(19.5,12.5,side);
    glVertex3f(19.5,12.5,-side);
    glVertex3f(29,11,-side);
    glVertex3f(29,11,side);
  glEnd();

  glNormal3fv(glm::value_ptr(normal3Points({29,11,side,29,7,side,29,7,-side})));
  glBegin(GL_POLYGON);//6
    glVertex3f(29,11,side);
    glVertex3f(29,11,-side);
    glVertex3f(29,7,-side);
    glVertex3f(29,7,side);
  glEnd();

  glNormal3fv(glm::value_ptr(normal3Points({29,7,side,47,7,side,47,7,-side})));
  glBegin(GL_POLYGON);//7
    glVertex3f(29,7,side);
    glVertex3f(47,7,side);
    glVertex3f(47,7,-side);
    glVertex3f(29,7,-side);
  glEnd();

// // BACK
  glNormal3fv(glm::value_ptr(normal3Points({47,7,side,46,3,-side,47,7,-side})));
  glBegin(GL_POLYGON);//8
    glVertex3f(47,7,side);
    glVertex3f(47,7,-side);
    glVertex3f(46,3,-side);
    glVertex3f(46,3,side);
  glEnd();

  glNormal3fv(glm::value_ptr(normal3Points({46,3,side,43,0.5,side,43,0.5,-side})));
  glBegin(GL_POLYGON);//9
    glVertex3f(46,3,side);
    glVertex3f(43,0.5,side);
    glVertex3f(43,0.5,-side);
    glVertex3f(46,3,-side);
  glEnd();

}

// Vehicle side middle area
void VehicleWidget::vehicleSideUper(float side, const materialStruct& material){

  glMaterialfv(GL_FRONT, GL_AMBIENT,    material.ambient);
  glMaterialfv(GL_FRONT, GL_DIFFUSE,    material.diffuse);
  glMaterialfv(GL_FRONT, GL_SPECULAR,   material.specular);
  glMaterialf(GL_FRONT, GL_SHININESS,   material.shininess);

  glNormal3fv(glm::value_ptr(normal3Points({11,8,side,19.5,12.5,side,6,8,side})));
  glBegin(GL_TRIANGLES);//1
    glVertex3f(11,8,side);
    glVertex3f(19.5,12.5,side);
    glVertex3f(6,8,side);
  glEnd();

  glNormal3fv(glm::value_ptr(normal3Points({11,8,side,19,11,side,19.5, 12.5,side})));
  glBegin(GL_TRIANGLES);//2
    glVertex3f(11,8,side);
    glVertex3f(19,11,side);
    glVertex3f(19.5, 12.5,side);
  glEnd();

  glNormal3fv(glm::value_ptr(normal3Points({19,11,side,20,11,side, 19.5,12.5,side})));
  glBegin(GL_TRIANGLES);//3
    glVertex3f(19,11,side);
    glVertex3f(20,11,side);
    glVertex3f(19.5,12.5,side);
  glEnd();

  glNormal3fv(glm::value_ptr(normal3Points({19,11,side,20,8,side, 20,11,side})));
  glBegin(GL_TRIANGLES);//4
    glVertex3f(19,11,side);
    glVertex3f(20,8,side);
    glVertex3f(20,11,side);
  glEnd();

  glNormal3fv(glm::value_ptr(normal3Points({19,11,side,19,8,side, 20,8,side})));
  glBegin(GL_TRIANGLES);//5
    glVertex3f(19,11,side);
    glVertex3f(19,8,side);
    glVertex3f(20,8,side);
  glEnd();

  glNormal3fv(glm::value_ptr(normal3Points({19.5,12.5,side,20,11,side, 47,9,side})));
  glBegin(GL_TRIANGLES);//6
    glVertex3f(19.5,12.5,side);
    glVertex3f(20,11,side);
    glVertex3f(47,9,side);
  glEnd();

  glNormal3fv(glm::value_ptr(normal3Points({20,11,side,35.5,8,side, 47,9,side})));
  glBegin(GL_TRIANGLES);//7
    glVertex3f(20,11,side);
    glVertex3f(35.5,8,side);
    glVertex3f(47,9,side);
  glEnd();

  glNormal3fv(glm::value_ptr(normal3Points({47,8,side,47,9,side,35.5,8,side})));
  glBegin(GL_TRIANGLES);//8
    glVertex3f(47,8,side);
    glVertex3f(47,9,side);
    glVertex3f(35.5,8,side);
  glEnd();
}

void VehicleWidget::vehicleDoors(float side, const materialStruct& material){

  glMaterialfv(GL_FRONT, GL_AMBIENT,    material.ambient);
  glMaterialfv(GL_FRONT, GL_DIFFUSE,    material.diffuse);
  glMaterialfv(GL_FRONT, GL_SPECULAR,   material.specular);
  glMaterialf(GL_FRONT, GL_SHININESS,   material.shininess);

  // FIRST Doors
  glNormal3fv(glm::value_ptr(normal3Points({11,0,side,19,0,side,19,7,side})));
    glBegin(GL_POLYGON);//7
      glVertex3f(11,0,side);
      glVertex3f(19,0,side);
      glVertex3f(19,7,side); //added
      glVertex3f(11,7,side);
    glEnd();

  // mid area between window and bottom
  glNormal3fv(glm::value_ptr(normal3Points({11,7,side,19,7,side,19,8,side})));
    glBegin(GL_POLYGON);//7
      glVertex3f(11,7,side);
      glVertex3f(19,7,side);
      glVertex3f(19,8,side);
      glVertex3f(11,8,side); //taken
    glEnd();

  //Now make the doors double, so that window translate will not be visible from the inside
  float adder = (side>0)?-0.015:0.015;//0.015 since window slides on z with 0.01

  glNormal3fv(glm::value_ptr(normal3Points({11,0,side,19,0,side,19,7,side})));
    glBegin(GL_POLYGON);//7
      glVertex3f(11,0,side+adder);
      glVertex3f(19,0,side+adder);
      glVertex3f(19,7,side+adder); //added
      glVertex3f(11,7,side+adder);
    glEnd();

  // mid area between window and bottom
  glNormal3fv(glm::value_ptr(normal3Points({11,7,side,19,7,side,19,8,side})));
    glBegin(GL_POLYGON);//7
      glVertex3f(11,7,side+adder);
      glVertex3f(19,7,side+adder);
      glVertex3f(19,8,side+adder);
      glVertex3f(11,8,side+adder); //taken
    glEnd();
}



void VehicleWidget::vehicleWheelBumbers(float side, const materialStruct& material){
  float adder = (side>0)?1:-1;

  glMaterialfv(GL_FRONT, GL_AMBIENT,    material.ambient);
  glMaterialfv(GL_FRONT, GL_DIFFUSE,    material.diffuse);
  glMaterialfv(GL_FRONT, GL_SPECULAR,   material.specular);
  glMaterialf(GL_FRONT, GL_SHININESS,   material.shininess);

  //3D WheelShields //FRONT WHEELSHIELD
  glNormal3fv(glm::value_ptr(normal3Points({2,1,side+adder,1,1.5,side,2,1.5,side})));
  glBegin(GL_TRIANGLES);
    glVertex3f(2,1,side+adder);
    glVertex3f(1,1.5,side);
    glVertex3f(2,1.5,side);
  glEnd();
  glNormal3fv(glm::value_ptr(normal3Points({2,1,side+adder,2,3,side+adder,1,3,side})));
  glBegin(GL_POLYGON);
    glVertex3f(2,1,side+adder);
    glVertex3f(2,3,side+adder);
    glVertex3f(1,3,side);
    glVertex3f(1,1.5,side);
  glEnd();
  glNormal3fv(glm::value_ptr(normal3Points({2,3,side+adder,2,1,side+adder,2,1,side})));
  glBegin(GL_POLYGON);
    glVertex3f(2,3,side+adder);
    glVertex3f(2,1,side+adder);
    glVertex3f(2,1,side);
    glVertex3f(2,3,side);
  glEnd();

  glNormal3fv(glm::value_ptr(normal3Points({2,3, side+adder,3.5, 5.5, side+adder,3.5,6.5,side})));
  glBegin(GL_POLYGON);
    glVertex3f(2,3, side+adder);
    glVertex3f(3.5, 5.5, side+adder);
    glVertex3f(3.5,6.5,side);
    glVertex3f(1,3,side);
  glEnd();
  glNormal3fv(glm::value_ptr(normal3Points({3.5, 5.5, side+adder,2,3, side+adder,2,3, side})));
  glBegin(GL_POLYGON);
    glVertex3f(3.5, 5.5, side+adder);
    glVertex3f(2,3, side+adder);
    glVertex3f(2,3, side);
    glVertex3f(3.5, 5.5, side);
  glEnd();

  glNormal3fv(glm::value_ptr(normal3Points({3.5, 5.5, side+adder,9,5.5, side+adder,9,6.5, side})));
  glBegin(GL_POLYGON);
    glVertex3f(3.5, 5.5, side+adder);
    glVertex3f(9,5.5, side+adder);
    glVertex3f(9,6.5, side);
    glVertex3f(3.5, 6.5, side);
  glEnd();
  glNormal3fv(glm::value_ptr(normal3Points({3.5, 5.5, side+adder,3.5, 5.5, side,9,6.5, side})));
  glBegin(GL_POLYGON);
    glVertex3f(3.5, 5.5, side+adder);
    glVertex3f(3.5, 6.5, side);
    glVertex3f(9,6.5, side);
    glVertex3f(9,5.5, side+adder);
  glEnd();

  glNormal3fv(glm::value_ptr(normal3Points({9, 6.5, side,9, 5.5, side+adder,11,2, side+adder})));
  glBegin(GL_POLYGON);
    glVertex3f(9, 6.5, side);
    glVertex3f(9, 5.5, side+adder);
    glVertex3f(11,2, side+adder);
    glVertex3f(12,2, side);
  glEnd();
  glNormal3fv(glm::value_ptr(normal3Points({9, 5.5, side+adder,9, 5.5, side,11,2, side})));
  glBegin(GL_POLYGON);
    glVertex3f(9, 5.5, side+adder);
    glVertex3f(9, 5.5, side);
    glVertex3f(11,2, side);
    glVertex3f(11,2, side+adder);
  glEnd();

  glNormal3fv(glm::value_ptr(normal3Points({12,2,side,11,2, side+adder,11,0, side+adder})));
  glBegin(GL_POLYGON);
    glVertex3f(12,2,side);
    glVertex3f(11,2, side+adder);
    glVertex3f(11,0, side+adder);
    glVertex3f(12,0, side);
  glEnd();
  glNormal3fv(glm::value_ptr(normal3Points({11,2,side+adder,11,2, side,11,0, side})));
  glBegin(GL_POLYGON);
    glVertex3f(11,2,side+adder);
    glVertex3f(11,2, side);
    glVertex3f(11,0, side);
    glVertex3f(11,0, side+adder);
  glEnd();
  glNormal3fv(glm::value_ptr(normal3Points({11,0,side+adder,11,0,side,12,0,side})));
  glBegin(GL_TRIANGLES);
    glVertex3f(11,0,side+adder);
    glVertex3f(11,0,side);
    glVertex3f(12,0,side);
  glEnd();

  //BACK WEENDSHEELD
  glNormal3fv(glm::value_ptr(normal3Points({33,0,side,34,0,side,34,0,side+adder})));
  glBegin(GL_TRIANGLES);
    glVertex3f(33,0,side);
    glVertex3f(34,0,side);
    glVertex3f(34,0,side+adder);
  glEnd();
  glNormal3fv(glm::value_ptr(normal3Points({34,0,side+adder,34,3,side+adder,33,3,side})));
  glBegin(GL_POLYGON);
    glVertex3f(34,0,side+adder);
    glVertex3f(34,3,side+adder);
    glVertex3f(33,3,side);
    glVertex3f(33,0,side);
  glEnd();
  glNormal3fv(glm::value_ptr(normal3Points({34,0,side+adder,34,0,side,34,3,side})));
  glBegin(GL_POLYGON);
    glVertex3f(34,0,side+adder);
    glVertex3f(34,0,side);
    glVertex3f(34,3,side);
    glVertex3f(34,3,side+adder);
  glEnd();
  glNormal3fv(glm::value_ptr(normal3Points({33,3,side,34,3,side+adder,36,5.5,side+adder})));
  glBegin(GL_POLYGON);
    glVertex3f(33,3,side);
    glVertex3f(34,3,side+adder);
    glVertex3f(36,5.5,side+adder);
    glVertex3f(36,6.5,side);
  glEnd();
  glNormal3fv(glm::value_ptr(normal3Points({34,3,side+adder,34,3,side,36,5.5,side})));
  glBegin(GL_POLYGON);
    glVertex3f(34,3,side+adder);
    glVertex3f(34,3,side);
    glVertex3f(36,5.5,side);
    glVertex3f(36,5.5, side+adder);
  glEnd();
  glNormal3fv(glm::value_ptr(normal3Points({36,5.5,side+adder,41,5.5,side+adder,41,6.5,side})));
  glBegin(GL_POLYGON);
    glVertex3f(36,5.5,side+adder);
    glVertex3f(41,5.5,side+adder);
    glVertex3f(41,6.5,side);
    glVertex3f(36,6.5,side);
  glEnd();
  glNormal3fv(glm::value_ptr(normal3Points({36,5.5,side+adder,36,5.5,side,41,5.5,side})));
  glBegin(GL_POLYGON);
    glVertex3f(36,5.5,side+adder);
    glVertex3f(36,5.5,side);
    glVertex3f(41,5.5,side);
    glVertex3f(41,5.5,side+adder);
  glEnd();
  glNormal3fv(glm::value_ptr(normal3Points({41,5.5,side+adder,43,3,side+adder,44,3,side})));
  glBegin(GL_POLYGON);
    glVertex3f(41,5.5,side+adder);
    glVertex3f(43,3,side+adder);
    glVertex3f(44,3,side);
    glVertex3f(41,6.5,side);
  glEnd();
  glNormal3fv(glm::value_ptr(normal3Points({41,5.5,side,43,3,side,43,3,side+adder})));
  glBegin(GL_POLYGON);
    glVertex3f(41,5.5,side);
    glVertex3f(43,3,side);
    glVertex3f(43,3,side+adder);
    glVertex3f(41,5.5,side+adder);
  glEnd();
  glNormal3fv(glm::value_ptr(normal3Points({43,0.5,side+adder,44,0.5,side,44,3,side})));
  glBegin(GL_POLYGON);
    glVertex3f(43,0.5,side+adder);
    glVertex3f(44,0.5,side);
    glVertex3f(44,3,side);
    glVertex3f(43,3,side+adder);
  glEnd();
  glNormal3fv(glm::value_ptr(normal3Points({43,3,side+adder,43,3,side,43,0.5,side})));
  glBegin(GL_POLYGON);
    glVertex3f(43,3,side+adder);
    glVertex3f(43,3,side);
    glVertex3f(43,0.5,side);
    glVertex3f(43,0.5,side+adder);
  glEnd();
  glNormal3fv(glm::value_ptr(normal3Points({43,0.5,side+adder,43,0.5,side,44,0.5,side})));
  glBegin(GL_TRIANGLES);
    glVertex3f(43,0.5,side+adder);
    glVertex3f(43,0.5,side);
    glVertex3f(44,0.5,side);
  glEnd();
}

void VehicleWidget::vehicleSideGround(float side, const materialStruct& material){

  glMaterialfv(GL_FRONT, GL_AMBIENT,    material.ambient); //spalvos tsg
  glMaterialfv(GL_FRONT, GL_DIFFUSE,    material.diffuse);
  glMaterialfv(GL_FRONT, GL_SPECULAR,   material.specular);
  glMaterialf(GL_FRONT, GL_SHININESS,   material.shininess);

  glNormal3fv(glm::value_ptr(normal3Points({0,5.5,side,2,5.5,side,2,7,side})));
  glBegin(GL_TRIANGLES); //1
    glVertex3f(0,5.5,side);
    glVertex3f(2,5.5,side);
    glVertex3f(2,7,side);
  glEnd();

  glNormal3fv(glm::value_ptr(normal3Points({0,5.5,side,2,1,side,2,5.5,side})));
  glBegin(GL_TRIANGLES);//2
    glVertex3f(0,5.5,side);
    glVertex3f(2,1,side);
    glVertex3f(2,5.5,side);
  glEnd();

  glNormal3fv(glm::value_ptr(normal3Points({0.5,1.5,side,2,1,side,0,5.5,side})));
  glBegin(GL_TRIANGLES);//3
    glVertex3f(0.5,1.5,side);
    glVertex3f(2,1,side);
    glVertex3f(0,5.5,side);
  glEnd();

  glNormal3fv(glm::value_ptr(normal3Points({2,5.5,side,2,3,side,3.5,5.5,side})));
  glBegin(GL_TRIANGLES);//4
    glVertex3f(2,5.5,side);
    glVertex3f(2,3,side);
    glVertex3f(3.5,5.5,side);
  glEnd();

  glNormal3fv(glm::value_ptr(normal3Points({2,5.5,side,11,5.5,side,2,7,side})));
  glBegin(GL_TRIANGLES);//5
    glVertex3f(2,5.5,side);
    glVertex3f(11,5.5,side);
    glVertex3f(2,7,side);
  glEnd();
  glNormal3fv(glm::value_ptr(normal3Points({11,5.5,side,11,7,side,2,7,side})));

  glBegin(GL_TRIANGLES);//6
    glVertex3f(11,5.5,side);
    glVertex3f(11,7,side);
    glVertex3f(2,7,side);
  glEnd();

  glNormal3fv(glm::value_ptr(normal3Points({9,5.5,side,11,2,side,11,5.5,side})));
  glBegin(GL_TRIANGLES);//6.5
    glVertex3f(9,5.5,side);
    glVertex3f(11,2,side);
    glVertex3f(11,5.5,side);
  glEnd();

  //SECOND Doors
  glNormal3fv(glm::value_ptr(normal3Points({19,7,side,19,0,side,28,0,side})));

  glPushMatrix();
    glBegin(GL_TRIANGLES);//9
      glVertex3f(19,7,side);
      glVertex3f(19,0,side);
      glVertex3f(28,0,side);
    glEnd();
    glNormal3fv(glm::value_ptr(normal3Points({28,0,side,28,7,side,19,7,side})));

    glBegin(GL_TRIANGLES);//10
      glVertex3f(28,0,side);
      glVertex3f(28,7,side);
      glVertex3f(19,7,side);
    glEnd();
  glPopMatrix();

  //THIRD
  glNormal3fv(glm::value_ptr(normal3Points({28,0,side,34,0,side,28,7,side})));

  glBegin(GL_TRIANGLES);//11
    glVertex3f(28,0,side);
    glVertex3f(34,0,side);
    glVertex3f(28,7,side);
  glEnd();
  glNormal3fv(glm::value_ptr(normal3Points({34,7,side,28,7,side,34,0,side})));

  glBegin(GL_TRIANGLES);//12
    glVertex3f(34,7,side);
    glVertex3f(28,7,side);
    glVertex3f(34,0,side);
  glEnd();
  glNormal3fv(glm::value_ptr(normal3Points({34,3,side,37,7,side,34,7,side})));

  glBegin(GL_TRIANGLES);//13
    glVertex3f(34,3,side);
    glVertex3f(37,7,side);
    glVertex3f(34,7,side);
  glEnd();
  glNormal3fv(glm::value_ptr(normal3Points({35,5.5,side,41,5.5,side,37,7,side})));

  glBegin(GL_TRIANGLES);//14
    glVertex3f(36,5.5,side);
    glVertex3f(41,5.5,side);
    glVertex3f(37,7,side);
  glEnd();
  glNormal3fv(glm::value_ptr(normal3Points({41,5.5,side,41,7,side,37,7,side})));

  glBegin(GL_TRIANGLES);//15
    glVertex3f(41,5.5,side);
    glVertex3f(41,7,side);
    glVertex3f(37,7,side);
  glEnd();
  glNormal3fv(glm::value_ptr(normal3Points({41,7,side,41,5.5,side,43,5.5,side})));

  glBegin(GL_TRIANGLES);//16
    glVertex3f(41,7,side);
    glVertex3f(41,5.5,side);
    glVertex3f(43,5.5,side);
  glEnd();
  glNormal3fv(glm::value_ptr(normal3Points({41,5.5,side,43,3,side,43,5.5,side})));

  glBegin(GL_TRIANGLES);//17
    glVertex3f(41,5.5,side);
    glVertex3f(43,3,side);
    glVertex3f(43,5.5,side);
  glEnd();
  glNormal3fv(glm::value_ptr(normal3Points({43,5.5,side,43,3,side,46,3,side})));

  glBegin(GL_TRIANGLES);//18
    glVertex3f(43, 5.5,side);
    glVertex3f(43,3,side);
    glVertex3f(46,3,side);
  glEnd();

  glNormal3fv(glm::value_ptr(normal3Points({43,0.5,side,46,3,side,43,3,side})));
  glBegin(GL_TRIANGLES);//19
    glVertex3f(43,0.5,side);
    glVertex3f(46,3,side);
    glVertex3f(43,3,side);
  glEnd();

  glNormal3fv(glm::value_ptr(normal3Points({46,3,side,47,7,side,41,7,side})));
  glBegin(GL_TRIANGLES);//20
    glVertex3f(46,3,side);
    glVertex3f(47,7,side);
    glVertex3f(41,7,side);
  glEnd();

//NOW THE MIDDLE AREA BETWEEN GROUNDSIDE AND WINDOW
  glNormal3fv(glm::value_ptr(normal3Points({19,7,side,47,8,side,19,8,side})));

  glBegin(GL_TRIANGLES);
    glVertex3f(19,7,side);
    glVertex3f(47,8,side);
    glVertex3f(19,8,side);
  glEnd();
  glNormal3fv(glm::value_ptr(normal3Points({19,7,side,47,7,side,47,8,side})));

  glBegin(GL_TRIANGLES);
    glVertex3f(19,7,side);
    glVertex3f(47,7,side);
    glVertex3f(47,8,side);
  glEnd();

  glNormal3fv(glm::value_ptr(normal3Points({2,7,side,11,7,side,2,8,side})));
  glBegin(GL_TRIANGLES);
    glVertex3f(2,7,side);
    glVertex3f(11,7,side);
    glVertex3f(6,8,side);
  glEnd();

  glNormal3fv(glm::value_ptr(normal3Points({2,8,side,11,7,side,11,8,side})));
  glBegin(GL_TRIANGLES);
    glVertex3f(6,8,side);
    glVertex3f(11,7,side);
    glVertex3f(11,8,side);
  glEnd();
}

// drawin wheels and connection between them
void VehicleWidget::wheelAxes(float wheelWidth, float whichWheel, float ZaxisPosition, float wheelSize){

  //left axis(x closer to 0)
  glPushMatrix();
     glTranslatef(whichWheel, 0, -ZaxisPosition);
    if(whichWheel<10){
      // Formula from https://www.assignmentexpert.com/homework-answers/physics/classical-mechanics
      // 32 is the vehicle length(static since it can't be)
      float turn = sin((32-2*wheelSize)/radius)*180/PI;
      glRotatef(turn,0,1,0);
    }
     glRotatef(_wheelRotate, 0,0,1);
    this->drawWheel(wheelWidth, wheelSize, 3, 5, dark0SteelMaterials, dark1SteelMaterials);
  glPopMatrix();

  //right axis(x more far to 0)
  glPushMatrix();
    glTranslatef(whichWheel, 0, ZaxisPosition);
    if(whichWheel<10){
      float turn = sin((32-2*wheelSize)/radius)*180/PI;
      glRotatef(turn,0,1,0);
    }
    glRotatef(_wheelRotate, 0,0,1);
    this->drawWheel(wheelWidth, wheelSize, 3, 5, dark0SteelMaterials, dark1SteelMaterials);
  glPopMatrix();

  //connecting wheels with a cylinder
  glPushMatrix();
    glMaterialfv(GL_FRONT, GL_AMBIENT,    dark0SteelMaterials.ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE,    dark0SteelMaterials.diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR,   dark0SteelMaterials.specular);
    glMaterialf(GL_FRONT, GL_SHININESS,   dark0SteelMaterials.shininess);
    glTranslatef(whichWheel, 0, -ZaxisPosition);
    gluCylinder(qobj, 1, 1, ZaxisPosition*2, 10, 1);
  glPopMatrix();

}

// assembling all components of a car
void VehicleWidget::unifyVehicle(){

  glLoadIdentity();

  glPushMatrix();

    glRotatef(_y_camera_angle, 1., 0., 0.); //vertical widget
    glRotatef(_x_camera_angle, 0., 1., 0.); //horizontal widget
    glRotatef(_angleWhole, 0., 1., 0.); //Car movement


    glScalef(_scaler,_scaler,_scaler);//scaling so it looks like zooming

    glTranslatef(-radius-0.1*radius, 0, 0);//move vehicle in circle

    glRotatef(70+radius/10, 0,1,0);//Rotate the car itself
    this->wheelAxes(1, 6.5, vehicleWidth, 1.8);
    this->wheelAxes(1, 38.5, vehicleWidth, 1.8);

    //Stationary parts of a Vehicle
    this->vehicleSideGround(-vehicleWidth, mediumSteelMaterials);
    this->vehicleSideGround(vehicleWidth, mediumSteelMaterials);

    this->vehicleSideUper(-vehicleWidth, light0SteelMaterials);
    this->vehicleSideUper(vehicleWidth, light0SteelMaterials);

    this->vehicleRoof(vehicleWidth, mediumSteelMaterials);

    // Stationary Windows (without translate)
    this->vehicleStatWindows(-vehicleWidth, whiteShinyMaterials);
    this->vehicleStatWindows(vehicleWidth, whiteShinyMaterials);

// HIERARCHYCAL MODELING
// Doors with Opening
    glPushMatrix();
    // Position of the x position of doors start(I want to rotate it from the start on y axis)
      glTranslatef(11,0,0);
      glTranslatef(0,0,vehicleWidth);
      glRotatef(-_doorsAngle, 0,1,0);//worst case just rotate around z an thats it
      glTranslatef(0,0,-vehicleWidth);
      glTranslatef(-11,0,0);
      this->vehicleDoors(vehicleWidth, mediumSteelMaterials);
    // Window openning
      glTranslatef(0,-1*_windowTranslate*0.25, -0.01); //Z coordinate should be added
      this->vehicleDynaWindows(vehicleWidth, whiteShinyMaterials);
    glPopMatrix();
    glPushMatrix();
      glTranslatef(11,0,0);
      glTranslatef(0,0,-vehicleWidth);
      glRotatef(_doorsAngle, 0,1,0);//worst case just rotate around z an thats it
      glTranslatef(0,0,vehicleWidth);
      glTranslatef(-11,0,0);
      this->vehicleDoors(-vehicleWidth, mediumSteelMaterials);
    // Window openning
      glTranslatef(0,-1*_windowTranslate*0.25, 0.01); //Z coordinate should be added
      this->vehicleDynaWindows(-vehicleWidth, whiteShinyMaterials);
    glPopMatrix();

// Opening boot
    glPushMatrix();
      glPushMatrix();
        glTranslatef(-1*_bootTranslate*0.25,0,0);
        this->vehicleBootTop(_bootTranslate, vehicleWidth, mediumSteelMaterials);
      glPopMatrix();
      glPushMatrix();
        glTranslatef(47,0,0);
        glTranslatef(0,7,0);
        glRotatef(-2*_bootTranslate, 0,0,1);//worst case just rotate around z an thats it
        glTranslatef(0,-7,0);
        glTranslatef(-47,0,0);
        this->vehicleBootBottom(vehicleWidth, dark1SteelMaterials);
      glPopMatrix();
    glPopMatrix();

  glPopMatrix();
}

void VehicleWidget::makeLight(float x, float y, float z, float w, const materialStruct& material){
  // setting light position in the scene
  GLfloat light_pos[] = {x,y,z, w};
  glEnable(GL_LIGHTING); // enable lighting in general
  glEnable(GL_LIGHT0);   // each light source must also be enabled
  glLightfv(GL_LIGHT0, GL_POSITION, light_pos);

  // The Sphere depicting where the light is comming from
  //makes light to visualise better
  glPushMatrix();
    glMaterialfv(GL_FRONT, GL_AMBIENT,    material.ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE,    material.diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR,   material.specular);
    glMaterialf(GL_FRONT, GL_SHININESS,   material.shininess);
    glTranslatef(x,y,z);
    glutSolidSphere(2*2, 36, 32);
  glPopMatrix();
}

void VehicleWidget::obstacle(float size,const materialStruct& material1, const materialStruct& material2){

  glPushMatrix();
    glRotatef(-90,1,0,0);

    glPushMatrix();
      glMaterialfv(GL_FRONT, GL_AMBIENT,    material1.ambient);
      glMaterialfv(GL_FRONT, GL_DIFFUSE,    material1.diffuse);
      glMaterialfv(GL_FRONT, GL_SPECULAR,   material1.specular);
      glMaterialf(GL_FRONT, GL_SHININESS,   material1.shininess);
      glutSolidTorus(size/4, size, 16,8);
      glTranslatef(0,0,size);
      // radius, slices, stacks
      glutSolidSphere(size/2, 16,2);
    glPopMatrix();

    glMaterialfv(GL_FRONT, GL_AMBIENT,    material2.ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE,    material2.diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR,   material2.specular);
    glMaterialf(GL_FRONT, GL_SHININESS,   material2.shininess);
    //obj, base(bottom), base(top), length(height), slices, stacks
    gluCylinder(qobj, size, size/2, size, 10, 1);
  glPopMatrix();
}

void VehicleWidget::spawnObstacles(int inN, int outN, float size, const materialStruct& material1, const materialStruct& material2){

  //outter obstacles
  for(int i=0; i<outN; i++){
   glRotatef(360.0/outN,0,1,0);
    glPushMatrix();
    // adding additional 30 because of the vehicle lenght
      glTranslatef(radius+2*vehicleWidth+radius/8, 0, 0);
      obstacle(size, material1, material2);
    glPopMatrix();
  }

  //TODO: uncomment for inner obstacles
  // inner obstacles
  // for(int i=0; i<inN; i++){
  //  glRotatef(360.0/inN,0,1,0);
  //   glPushMatrix();
  //   // sbtracting only 16.28(the width of the vehicle because it's rotation is centered at the front)
  //     glTranslatef(radius-2*vehicleWidth, 0, 0);
  //     obstacle(size, material1, material2);
  //   glPopMatrix();
  // }
}

//Flat plane with a texture
void VehicleWidget::renderPlane(const materialStruct& material){

  glMaterialfv(GL_FRONT, GL_AMBIENT,    material.ambient);
  glMaterialfv(GL_FRONT, GL_DIFFUSE,    material.diffuse);
  glMaterialfv(GL_FRONT, GL_SPECULAR,   material.specular);
  glMaterialf(GL_FRONT, GL_SHININESS,   material.shininess);

  GLfloat normals[][3] = { {0, 1, 0 }};
  glNormal3fv(normals[0]);
  glBegin(GL_POLYGON);
    glTexCoord2f(0.0, 0.0);
    glVertex3f(-100, -100, 0);
    glTexCoord2f(1.0, 0.0);
    glVertex3f(100, -100, 0);
    glTexCoord2f(1.0, 1.0);
    glVertex3f(100, 100, 0);
    glTexCoord2f(0.0, 1.0);
    glVertex3f(-100,  100, 0);
  glEnd();
}

// called every time the widget needs painting
void VehicleWidget::paintGL(){

	// clear the widget
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glEnable(GL_NORMALIZE);

  // glShadeModel(GL_FLAT);
	glMatrixMode(GL_MODELVIEW);
 	glEnable(GL_DEPTH_TEST);

    glRotatef(_y_camera_angle, 1., 0., 0.); //vertical widget
    glRotatef(_x_camera_angle, 0, 1., 0.); //Horizontal widget

    glScalef(_scaler,_scaler,_scaler);//zooming in/out

    //making light responsive to the radius
    glPushMatrix();
      glRotatef(_rotateLight, 0,1,0);
      if(_b_lighting)makeLight(0.6*radius,radius,0,0.2,brassMaterials);
      else{  glDisable(GL_LIGHTING);}
    glPopMatrix();


  /* For an appropriate scaling of a plane and racetrack texture
      using https://www.dcode.fr/function-equation-finder*/
  float raceTrackScaler = 0.0357506 * pow(radius,0.827275) - 0.11963;

    /* The bottom texture(plain black) and only visible when lighting is on
      because if lghting is off and view is from the top nothing else apart plane is visible*/
    if(_b_lighting){
      glTranslatef(0,-4,0);
      glPushMatrix();
        if(radius>65)
          glScalef(raceTrackScaler,raceTrackScaler,raceTrackScaler);
        glTranslatef(0,-0.01,0);
        glRotatef(90, 1, 0, 0);
        glRotatef(180, 0, 0, 1);
        this->renderPlane(blackMaterial);
      glPopMatrix();
    }

//GLOBE texture and RACETRACK texture
  if(_b_textures){
    // The Racetrack texture
    glPushMatrix();
    //since the texture is not fully symetrical circle, i have to translate it and scale it manually
      glTranslatef(0,0,-5);
      if(radius<120)
        glScalef(raceTrackScaler,raceTrackScaler,raceTrackScaler);
      else glScalef(raceTrackScaler,raceTrackScaler,raceTrackScaler+0.1*raceTrackScaler);
      glRotatef(180, 0, 1, 0);
      glRotatef(90, 1, 0, 0);
      glRotatef(180, 0, 0, 1);

      glEnable(GL_TEXTURE_2D);
      glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, _imageRaceTrack.Width(), _imageRaceTrack.Height(), 0, GL_RGB, GL_UNSIGNED_BYTE, _imageRaceTrack.imageField());
      this->renderPlane(whiteShinyMaterials);
      glDisable(GL_TEXTURE_2D);
    glPopMatrix();

    //The Globe
    glPushMatrix();
      glScalef(radius,radius,radius);
      glRotatef(_rotateEarth, 0, 1, 0);
      glRotatef(90, 1,0,0);
      glRotatef(180, 0,1,0);
      this->sphereWithTexture();
    glPopMatrix();
  }

  if(_b_obstacles){
    //number of inner obstacles, number of outer obstacles, height of obstacle
    int inner = radius/6;
    int outter= radius/4;
    spawnObstacles(inner, outter, 2, redShinyMaterials, brassMaterials); //set min max(40)
  }

  	glLoadIdentity();
    //setting camera, target and face
    gluLookAt(50,50,0,  0,0,0,  0,0,1);

    unifyVehicle();

	glFlush();
}

// Dialog opens on double mouse click event
void VehicleWidget::mouseDoubleClickEvent(QMouseEvent* event )
{
  QDialog *widget = new QDialog;
  _ui.setupUi(widget);
  this->LoadDialog();
  widget->exec();
  this->UnloadDialog(_ui);
}

// Loading the dialog
void VehicleWidget::LoadDialog()
{
  _ui.pos1->setText(QString::number(speed));
  _ui.at1->setText(QString::number(radius));
  _ui.up1->setText(QString::number(vehicleWidth));
  _ui.blight->setCheckState(_b_lighting ? Qt::Checked : Qt::Unchecked);
  _ui.btextures->setCheckState(_b_textures ? Qt::Checked : Qt::Unchecked);
  _ui.bobstacles->setCheckState(_b_obstacles ? Qt::Checked : Qt::Unchecked);
}

// Chaning the variables with additional constraints
void VehicleWidget::UnloadDialog(const Ui_Dialog& dialog)
{
  if(dialog.pos1->toPlainText().toFloat()>=0 && dialog.pos1->toPlainText().toFloat()<=40){
    speed = dialog.pos1->toPlainText().toFloat();
  }
  if(dialog.at1->toPlainText().toFloat()>=50 && dialog.at1->toPlainText().toFloat()<=200){
      radius = dialog.at1->toPlainText().toFloat();
  }

  vehicleWidth = dialog.up1->toPlainText().toFloat(); //freedom
  _b_lighting = (_ui.blight->checkState() == Qt::Checked) ? true : false;
  _b_textures = (_ui.btextures->checkState() == Qt::Checked) ? true : false;
  _b_obstacles = (_ui.bobstacles->checkState() == Qt::Checked) ? true : false;
}
