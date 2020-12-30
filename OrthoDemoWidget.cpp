#include <GL/glut.h>
#include <QGLWidget>
#include <QDebug>
#include <iostream>
#include <cmath>
#include "OrthoDemoWidget.h"
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <array>

// TODO list:
/*
==NOT DONE==
lighting (normals and normalise)
wheels to turn by 'radius' angle
wheels to spin acordingly
make a stop and play button
Back with hierarchical
Doors with hierarchical
ZAxis polygons around above the wheels
ZAxis curvature on the roof and sides
lights in front and in the back (light sources)
fix all the inequalities of coordinates

==HALF DONE==
Plane with color
textures
*/

static const GLfloat radius = 50;
static const float speed = 0.8;
static const float PI = 3.1415926535;
static const int N        = 100; // This determines the number of faces of the cylinder
static const int n_div   =  100;  // This determines the fineness of the cylinder along its length
static const int StartingPosition = 80;
GLUquadric* qobj;
static const int rot[3] = {0,1,0}; //for rotating
float TotalDistance = 0;

void OrthoDemoWidget::updateCameraYAngle(int angle){
  _y_camera_angle = angle;
  this->repaint();
}
void OrthoDemoWidget::updateCameraXAngle(int angle){
  _x_camera_angle = angle;
  this->repaint();
}

// For infinite rotation(has to be set)
void OrthoDemoWidget::updateAngle(){
  float Wheelsize = 1;

  _wheelRotate += 1*(360*speed)/(2*PI*Wheelsize); //dk why is it too quick
  TotalDistance += speed;
  _angleWhole = TotalDistance;

  // printf("UpdateAngle %f wh: %f\n", TotalDistance,_wheelRotate);
  this->repaint();
}

void OrthoDemoWidget::doorsOpen(int d){
  _doorsAngle = d;
  printf("dangle: %f d; %i\n", _doorsAngle, d);
  this->repaint();
}

// when zooming in
void OrthoDemoWidget::zoomIn(int d){
  _scaler = 1 + d -pow(d, 0.97);
  printf("ZoomIn %f, %d\n", _scaler, d);
  this->repaint();
}
void OrthoDemoWidget::windowTranslate(int d){
  _windowTranslate = d;
  std::cout<<d<<std::endl;
  this->repaint();
}


float OrthoDemoWidget::wheelRotateAngle(float wheelSize){
  float angle;
  float radDistanceIn = 2*PI*radius;
  float radDistanceOut = 2*PI*(radius+16.28);

  return 360/(2*PI*wheelSize);
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
    _windowTranslate(0),
    _movement(StartingPosition),
    _image("/home/rokas/Documents/Leeds/3Year1Term_Works/GRAPHICSFINALPROJECT/textures/M.ppm"),
    _imageWall("/home/rokas/Documents/Leeds/3Year1Term_Works/GRAPHICSFINALPROJECT/textures/Mercator-projection.ppm")
	{ // constructor

} // constructor


// called when OpenGL context is set up
void OrthoDemoWidget::initializeGL()
	{ // initializeGL()
	// set the widget background colour
	glClearColor(0.3, 0.3, 0.3, 0.0);
    // glColor3f(1.0, 1.0, 1.0);
    //
    // // Set the camera lens to have a 60 degree (vertical) field of view, an
    // // aspect ratio of 4/3, and have everything closer than 1 unit to the
    // // camera and greater than 40 units distant clipped away.
    // glMatrixMode(GL_PROJECTION);
    // glLoadIdentity();
    // gluPerspective(60, 1, 1, 40);
    qobj = gluNewQuadric();
    gluQuadricNormals(qobj, GLU_SMOOTH);
    // // Position camera at (4, 6, 5) looking at (0, 0, 0) with the vector
    // // <0, 1, 0> pointing upward.
    // glMatrixMode(GL_MODELVIEW);
    // glLoadIdentity();

	glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
    glOrtho(-100.,100.,-100.,100.,-200.,200);

} // initializeGL()


// called every time the widget is resized
void OrthoDemoWidget::resizeGL(int w, int h){
  glViewport(0, 0, w, h);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	// // GLfloat light_pos[] = {0,-50,0, 0.5};
  //
	// glEnable(GL_LIGHTING); // enable lighting in general
  // glEnable(GL_LIGHT0);   // each light source must also be enabled
  // // glLightfv(GL_LIGHT0, GL_SPECULAR, light_pos);


	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
}

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


glm::vec3 OrthoDemoWidget::normal3Points(const std::array<double, 9>& params){
  int otherSides = 0;
  int A=params[3]*params[1] + params[6]*params[4] + params[0]*params[7];
  int B=params[0]*params[4] + params[3]*params[7] + params[6]*params[1];
  // Adding one to the vertices on the negative z axis
  otherSides += (params[2]<0)?1:0;
  otherSides += (params[5]<0)?1:0;
  otherSides += (params[8]<0)?1:0;

  if((otherSides<2 && A<=B) || (otherSides>1 && A>=B)){
    glm::vec3 v1 = {params[0], params[1], params[2]};
    glm::vec3 v2 = {params[3], params[4], params[5]};
    glm::vec3 v3 = {params[6], params[7], params[8]};

  return glm::normalize(glm::cross(v2 - v1, v3 - v2));
  }
  else {
    glm::vec3 v2 = {params[0], params[1], params[2]};
    glm::vec3 v1 = {params[3], params[4], params[5]};
    glm::vec3 v3 = {params[6], params[7], params[8]};

  return glm::normalize(glm::cross(v2 - v1, v3 - v2));
  }
}

void OrthoDemoWidget::vehicleStatWindows(float side, const materialStruct& material){
  if (_b_lighting)
    glEnable(GL_LIGHTING);
  else
    glDisable(GL_LIGHTING);

  glMaterialfv(GL_FRONT, GL_AMBIENT,    material.ambient);
  glMaterialfv(GL_FRONT, GL_DIFFUSE,    material.diffuse);
  glMaterialfv(GL_FRONT, GL_SPECULAR,   material.specular);
  glMaterialf(GL_FRONT, GL_SHININESS,   material.shininess);

// FRONT window
  // double params[9] = {6,8,side, 6,8, -side, 19.5, 12, -side};
  glNormal3fv(glm::value_ptr(normal3Points({6,8,8.14,19.5,12.5,8.14,19.5,12.5,-8.14})));
  glEnable(GL_TEXTURE_2D);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, _image.Width(), _image.Height(), 0, GL_RGB, GL_UNSIGNED_BYTE, _image.imageField());
  glBegin(GL_POLYGON);//1
  glTexCoord2f(0,0);
    glVertex3f(6,8,8.14);
    glTexCoord2f(0,1);
    glVertex3f(19.5,12.5,8.14);
    glTexCoord2f(1,1);
    glVertex3f(19.5,12.5,-8.14);
    glTexCoord2f(1,0);
    glVertex3f(6,8,-8.14);
  glEnd();
  glDisable(GL_TEXTURE_2D);
  // params[9] = {35.5,8,side, 20,11.5,side, 20,8,side};
  glNormal3fv(glm::value_ptr(normal3Points({35.5,8,side, 20,11,side, 20,8,side})));
  glBegin(GL_TRIANGLES);//1.2
    glVertex3f(35.5,8,side);
    glVertex3f(20,11,side);
    glVertex3f(20,8,side);
  glEnd();

}

void OrthoDemoWidget::vehicleDynaWindows(float side, const materialStruct& material){
  if (_b_lighting)
    glEnable(GL_LIGHTING);
  else
    glDisable(GL_LIGHTING);

  glMaterialfv(GL_FRONT, GL_AMBIENT,    material.ambient);
  glMaterialfv(GL_FRONT, GL_DIFFUSE,    material.diffuse);
  glMaterialfv(GL_FRONT, GL_SPECULAR,   material.specular);
  glMaterialf(GL_FRONT, GL_SHININESS,   material.shininess);

  //Window area
  glNormal3fv(glm::value_ptr(normal3Points({11,8,side,19,8,side,19,11,side})));
  glBegin(GL_TRIANGLES);//1.1
    glVertex3f(11,8,side);
    glVertex3f(19,8,side);
    glVertex3f(19,11,side);
  glEnd();

}

void OrthoDemoWidget::vehicleBoot(const materialStruct& material){

}

void OrthoDemoWidget::vehicleRoof(float side, const materialStruct& material){
  if (_b_lighting)
    glEnable(GL_LIGHTING);
  else
    glDisable(GL_LIGHTING);

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

// THe real roof
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
    glVertex3f(29,7,side);glVertex3f(47,7,side);glVertex3f(47,7,-side);
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
    glVertex3f(46,3,side);glVertex3f(43,0.5,side);glVertex3f(43,0.5,-side);
    glVertex3f(46,3,-side);
  glEnd();

}

void OrthoDemoWidget::vehicleSideUper(float side, const materialStruct& material){
  if (_b_lighting)
    glEnable(GL_LIGHTING);
  else
    glDisable(GL_LIGHTING);

  glMaterialfv(GL_FRONT, GL_AMBIENT,    material.ambient); //spalvos tsg
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

void OrthoDemoWidget::vehicleDoors(float side, const materialStruct& material){
  if (_b_lighting)
    glEnable(GL_LIGHTING);
  else
    glDisable(GL_LIGHTING);

  glMaterialfv(GL_FRONT, GL_AMBIENT,    material.ambient); //spalvos tsg
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
    // glBegin(GL_TRIANGLES);//8
    //   glVertex3f(19,0,side);
    //   glVertex3f(19,7,side);
    //   glVertex3f(11,7,side);
    // glEnd();

  // mid area between window and bottom
  glNormal3fv(glm::value_ptr(normal3Points({11,7,side,19,7,side,19,8,side})));
    glBegin(GL_POLYGON);//7
      glVertex3f(11,7,side);
      glVertex3f(19,7,side);
      glVertex3f(19,8,side);
      glVertex3f(11,8,side); //taken
    glEnd();
    //
    // glNormal3fv(glm::value_ptr(normal3Points({19,8,side,11,7,side,11,8,side})));
    // glBegin(GL_TRIANGLES);//8
    //   glVertex3f(19,8,side);
    //   glVertex3f(11,7,side);
    //   glVertex3f(11,8,side);
    // glEnd();
}

void OrthoDemoWidget::vehicleSideGround(float side, const materialStruct& material){
  if (_b_lighting)
    glEnable(GL_LIGHTING);
  else
    glDisable(GL_LIGHTING);

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

  glBegin(GL_TRIANGLES);//6.5 (the forgotten)
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
    glVertex3f(35,5.5,side);
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


void OrthoDemoWidget::wheelAxes(float wheelWidth, float whichWheel, float ZaxisPosition, float wheelSize){

  //left axis
  glPushMatrix();
     glTranslatef(whichWheel, 0, -ZaxisPosition);
     // glRotatef(wheelRotateAngle(wheelSize), 0,0,1);
     glRotatef(_wheelRotate, 0,0,1);
    this->hexo(wheelWidth, wheelSize, 3, 6, blueShinyMaterials);
  glPopMatrix();

  glPushMatrix();
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

    glRotatef(_y_camera_angle, 1., 0., 0.); //vertical widget
    glRotatef(_x_camera_angle, 0., 1., 0.); //vertical widget
    glRotatef(_angleWhole, 0., 1., 0.); //(_angle or _angleWhole) Car movement
    glTranslatef(-radius, 0, 0);
    glScalef(_scaler,_scaler,_scaler);

    glRotatef(90, 0,1,0);//Rotate the car itself
    this->wheelAxes(1, 6.5, 8.14, 1.8);
    this->wheelAxes(1, 38.5, 8.14, 1.8);

    //Stationary parts of a Vehicle
    this->vehicleSideGround(-8.14, redShinyMaterials);
    this->vehicleSideGround(8.14, redShinyMaterials);
    this->vehicleSideUper(-8.14, redShinyMaterials);
    this->vehicleSideUper(8.14, redShinyMaterials);
    this->vehicleRoof(8.14, redShinyMaterials);

    // glPushMatrix();
    //   glTranslatef(19,0,0);
    //   glRotatef(_doorsAngle, 0,1,0);
    //   glTranslatef(-19,0,0);
    //   this->vehicleDoors(-8.14, redShinyMaterials);
    // glPopMatrix();

    this->vehicleDoors(-8.14, redShinyMaterials);
    this->vehicleDoors(8.14, redShinyMaterials);

    // Stationary Windows (without translate)
    this->vehicleStatWindows(-8.14, blueShinyMaterials);
    this->vehicleStatWindows(8.14, blueShinyMaterials);
    //
    // Dynamic windws (with glTranslatef)
    glPushMatrix();
      glTranslatef(_windowTranslate*0.1,-1*_windowTranslate*0.25, 0.11*_windowTranslate); //Z coordinate should be added
      this->vehicleDynaWindows(-8.14, greenShinyMaterials);
      glTranslatef(0,0,0);
      glTranslatef(_windowTranslate*0.1,-1*_windowTranslate*0.25, -1*_windowTranslate); //Z coordinate should be added
      this->vehicleDynaWindows(8.14, greenShinyMaterials);
    glPopMatrix();

  glPopMatrix();

}

// called every time the widget needs painting
void OrthoDemoWidget::paintGL(){
	// clear the widget
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glEnable(GL_NORMALIZE);

  // glShadeModel(GL_FLAT);
	glMatrixMode(GL_MODELVIEW);
 	glEnable(GL_DEPTH_TEST);

  //
  // glTranslatef(80, 50, 0);
  // GLfloat light_pos[] = {80,50,0, 0.5};
  // glEnable(GL_LIGHTING); // enable lighting in general
  // glEnable(GL_LIGHT0);   // each light source must also be enabled
  // glLightfv(GL_LIGHT0, GL_SPECULAR, light_pos);
  // glutSolidSphere(2*2, 36, 32);
  //
  // glLoadIdentity();
  //   gluLookAt(0,100,0,  0,0,0,  0,0,1);
  // glTranslatef(-80, -50, 0);
    glScalef(_scaler,_scaler,_scaler);
              	// this->cube();

    glRotatef(_y_camera_angle, 1., 0., 0.); //vertical widget
    glRotatef(_x_camera_angle, 0, 1., 0.); //Horizontal widget


      GLfloat light_pos[] = {50,10,0, 0.5};
      glEnable(GL_LIGHTING); // enable lighting in general
      glEnable(GL_LIGHT0);   // each light source must also be enabled
      glLightfv(GL_LIGHT0, GL_POSITION, light_pos);

      glPushMatrix();
      glTranslatef(50, 10, 0);
      glutSolidSphere(2*2, 36, 32);
      glPopMatrix();

    // TODO make y length of wheel radius

    glTranslatef(0,-5,0);
    glPushMatrix();
      glRotatef(90, 1, 0, 0);
      glRotatef(180, 0, 0, 1);
      glEnable(GL_TEXTURE_2D);
        // glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, _image.Width(), _image.Height(), 0, GL_RGB, GL_UNSIGNED_BYTE, _image.imageField());
      glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, _imageWall.Width(), _imageWall.Height(), 0, GL_RGB, GL_UNSIGNED_BYTE, _imageWall.imageField());
      this->renderPlane(whiteShinyMaterials);
      glDisable(GL_TEXTURE_2D);
    glPopMatrix();

    glPushMatrix();
      glRotatef(0, 0, 0, 1);
      glTranslatef(0,50,-100);
      glScalef(1,0.5,1);
      glEnable(GL_TEXTURE_2D);
      glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, _image.Width(), _image.Height(), 0, GL_RGB, GL_UNSIGNED_BYTE, _image.imageField());
      this->renderPlane(redShinyMaterials);
      glDisable(GL_TEXTURE_2D);
    glPopMatrix();

  	glLoadIdentity();
    gluLookAt(0,1,0,  0,0,0,  0,0,1);

  unify(_time);
	glFlush();
}

void OrthoDemoWidget::renderPlane(const materialStruct& material){

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
