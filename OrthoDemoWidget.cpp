#include <GL/glut.h>
#include <QGLWidget>
#include <QDebug>
#include <cmath>
#include "OrthoDemoWidget.h"
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

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
static const float PI = 3.1415926535;
static const int N        = 100; // This determines the number of faces of the cylinder
static const int n_div   =  100;  // This determines the fineness of the cylinder along its length
GLUquadric* qobj;

// constructor
OrthoDemoWidget::OrthoDemoWidget(QWidget *parent)
  : QGLWidget(parent),
    _ortho_par(-100.,100.,-100.,100.,-200.,200),
    _glupar(0.,0.,100.,0.,0.,0.,0.,1.,0.),
    _b_lighting(true),
    _angle(0.0),
    _time(0),
    _scaler(1.0)
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
    glLoadIdentity();
    gluPerspective(60.0, 4.0/3.0, 1, 40);
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


void OrthoDemoWidget::pyramid(float scale, const materialStruct& material){

  if (_b_lighting)
    glEnable(GL_LIGHTING);
  else
    glDisable(GL_LIGHTING);

  // glRotatef(45, 0, 0, 1);

  glMaterialfv(GL_FRONT, GL_AMBIENT,    material.ambient); //spalvos tsg
  glMaterialfv(GL_FRONT, GL_DIFFUSE,    material.diffuse);
  glMaterialfv(GL_FRONT, GL_SPECULAR,   material.specular);
  glMaterialf(GL_FRONT, GL_SHININESS,   material.shininess);

  glColor3f(0.0,0.0,1.0);   // blue; facing positive x-axis

  float halfscale = 0.5*scale;
  glm::vec3 v1 = { scale, -scale, 0.0};
  glm::vec3 v2 = { scale, scale, 0.0};
  glm::vec3 v3 = { 0., 0., scale }; // middle

  glm::vec3 n  = glm::normalize(glm::cross(v2 - v1, v3 - v2));

  glNormal3fv(glm::value_ptr(n));
  glBegin(GL_POLYGON);
    glVertex3f(v1[0], v1[1], v1[2]);
    glVertex3f(v2[0], v2[1], v2[2]);
    glVertex3f(v3[0], v3[1], v3[2]);
  glEnd();

  v1 = { scale, scale, 0};
  v2 = {-scale, scale, 0};


  n  = glm::normalize(glm::cross(v2 - v1, v3 - v2));

  glColor3f(1.0,0.0,0.0);   // blue; facing positive x-axis

  glNormal3fv(glm::value_ptr(n));
  glBegin(GL_POLYGON);
    glVertex3f(v1[0], v1[1], v1[2]);
    glVertex3f(v2[0], v2[1], v2[2]);
    glVertex3f(v3[0], v3[1], v3[2]);
  glEnd();

  v1 = {-scale, scale, 0};
  v2 = {-scale,-scale, 0};

  n  = glm::normalize(glm::cross(v2 - v1, v3 - v2));

  glColor3f(0.0,1.0,0.0);   // blue; facing positive x-axis

  glNormal3fv(glm::value_ptr(n));
  glBegin(GL_POLYGON);
  glVertex3f(v1[0], v1[1], v1[2]);
  glVertex3f(v2[0], v2[1], v2[2]);
  glVertex3f(v3[0], v3[1], v3[2]);
  glEnd();

  v1 = {-scale, -scale, 0};
  v2 = { scale, -scale, 0};
  // v3[2] = 4;
  n  = glm::normalize(glm::cross(v2 - v1, v3 - v2));

  glColor3f(1.0,1.0,0.0);   // blue; facing positive x-axis

  glNormal3fv(glm::value_ptr(n));
  glBegin(GL_POLYGON);
    glVertex3f(v1[0], v1[1], v1[2]);
    glVertex3f(v2[0], v2[1], v2[2]);
    glVertex3f(v3[0], v3[1], v3[2]);
    // printf("%f, %f, %f \n", v1[0], v1[1], v1[2]);
    // printf("%f, %f, %f \n", v2[0], v2[1], v2[2]);
    // printf("%f, %f, %f \n", v3[0], v3[1], v3[2]);
  glEnd();
// glNormal3fv(glm::value_ptr(n));
//   glColor3f(1.0,1.0,1.0);
  glBegin(GL_POLYGON);
    glVertex3f(v1[0], v1[1], v1[2]);
    glVertex3f(v1[0], v1[1], -100);
    glVertex3f(v2[0], v2[1], -100);
    glVertex3f(v2[0], v2[1], v2[2]);
     // printf("%f, %f, %f.\n", v2[0], v2[1], v2[2]);
  glEnd();

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
  glMaterialfv(GL_FRONT, GL_AMBIENT,    material.ambient); //spalvos tsg
  glMaterialfv(GL_FRONT, GL_DIFFUSE,    material.diffuse);
  glMaterialfv(GL_FRONT, GL_SPECULAR,   material.specular);
  glMaterialf(GL_FRONT, GL_SHININESS,   material.shininess);

  glutSolidTorus(inner, outer, nsides, rings);
}

void OrthoDemoWidget::sidePoly(const materialStruct& material){

}

void OrthoDemoWidget::sphere(const materialStruct& material ){
   //
   glMaterialfv(GL_FRONT, GL_AMBIENT,    material.ambient); //spalvos tsg
   glMaterialfv(GL_FRONT, GL_DIFFUSE,    material.diffuse);
   glMaterialfv(GL_FRONT, GL_SPECULAR,   material.specular);
   glMaterialf(GL_FRONT, GL_SHININESS,   material.shininess);

  constexpr double pi = 3.14159265358979323846;
  float phi_min = 0;
  float phi_max = 2*pi;

  float theta_min = -pi;
  float theta_max = pi;

  int n_theta = 100;
  int n_phi   = 100;

  float delta_phi   = (phi_max - phi_min)/n_phi;
  float delta_theta = (theta_max - theta_min)/n_theta;

  for (int i_phi = 0; i_phi < n_phi; i_phi++)
    for (int i_theta = 0; i_theta < n_theta; i_theta++){

      glBegin(GL_POLYGON);
      float phi   = phi_min + i_phi*delta_phi;
      float theta = theta_min + i_theta*delta_theta;

      float x_0 = cos(phi)*sin(theta);
      float y_0 = sin(phi)*sin(theta);
      float z_0 = cos(theta);
        glNormal3f(x_0,y_0,z_0);
        glVertex3f(x_0,y_0,z_0);
      float x_1 = cos(phi+delta_phi)*sin(theta);
      float y_1 = sin(phi+delta_phi)*sin(theta);
      float z_1 = cos(theta);
        glNormal3f(x_1,y_1,z_1);
        glVertex3f(x_1,y_1,z_1);
      float x_2 = cos(phi+delta_phi)*sin(theta+delta_theta);
      float y_2 = sin(phi+delta_phi)*sin(theta+delta_phi);
      float z_2 = cos(theta + delta_theta);
        glNormal3f(x_2,y_2,z_2);
        glVertex3f(x_2,y_2,z_2);
      float x_3 = cos(phi)*sin(theta);
      float y_3 = sin(phi)*sin(theta);
      float z_3 = cos(theta + delta_theta);
        glNormal3f(x_3,y_3,z_3);
        glVertex3f(x_3,y_3,z_3);
      glEnd();
    }
}
void OrthoDemoWidget::arm(double upper, double lower, double time){
  double angle = upper*sin(0.1*time) + upper;

  glPushMatrix();
    glRotatef(angle,0.,1.,0.);
    glScalef(0.3,0.3,2.); // deform cylinder
    glTranslatef(0.,0.,-1);
    this->cylinderforarm(greenShinyMaterials);
    glTranslatef(0.,0.,-1);
    glScalef(0.6/0.3,0.6/0.3,0.6/2.);
    this->sphere(redShinyMaterials);
    glScalef(1/0.6,1/0.6,1/0.6); // here we have undone all scalings; the origin is at the end of the upper arm  and the z-axis is aligned with that arm

  // glPopMatrix(); //no pop, because we are building up on the next node
  glPushMatrix();
    double lowangle = lower*sin(0.2*time) + lower;
    glRotatef(lowangle,0.,1.,0.);
    glScalef(0.3,0.3,2.); // deform cylinder
    glTranslatef(0.,0.,-1);
    this->cylinderforarm(greenShinyMaterials);
    glTranslatef(0.,0.,-1);
    glScalef(0.6/0.3,0.6/0.3,0.6/2.);
    this->sphere(redShinyMaterials);
  glPopMatrix();
  glPopMatrix();

  glPushMatrix();
    glScalef(0.7,0.7,0.7);
    this->sphere(redShinyMaterials);
  glPopMatrix();

}
void OrthoDemoWidget::cylinderforarm(const materialStruct& material){

  glMaterialfv(GL_FRONT, GL_AMBIENT,    material.ambient); //spalvos tsg
  glMaterialfv(GL_FRONT, GL_DIFFUSE,    material.diffuse);
  glMaterialfv(GL_FRONT, GL_SPECULAR,   material.specular);
  glMaterialf(GL_FRONT, GL_SHININESS,   material.shininess);

  float x0, x1, y0, y1;

  float z_min = -1;
  float z_max =  1;

  float delta_z = (z_max - z_min)/n_div;

  for (int i = 0; i < N; i++){
    for(int i_z = 0; i_z < n_div; i_z++){
      x0 = cos(2*i*PI/N);
      x1 = cos(2*(i+1)*PI/N);
      y0 = sin(2*i*PI/N);
      y1 = sin(2*(i+1)*PI/N);

      float z = z_min + i_z*delta_z;
      glBegin(GL_POLYGON);
        glVertex3f(x0,y0,z);
        glNormal3f(x0,y0,0);
        glVertex3f(x1,y1,z);
        glNormal3f(x1,y1,0);
        glVertex3f(x1,y1,z+delta_z);
        glNormal3f(x1,y1,0);
        glVertex3f(x0,y0,z+delta_z);
        glNormal3f(x0,y0,0);
        // printf("%f, %f, %f, %f , %f \n", x0, y0, z, x1, y1);
      glEnd();
    }
  }
  // gluCylinder(qobj, 0.5, 1, 5, 32, 5);
}

void OrthoDemoWidget::updateAngle(){
  _angle -= 1.0; //clockwise
  _time +=0.25;
  this->repaint(); //paintGL used every time
}
// cia widget.cpp
void OrthoDemoWidget::zoomIn(int d){
  _scaler = 1 + d -pow(d, 0.97);
  printf("%f\n", _scaler);
  this->repaint(); //neveikia
}
void OrthoDemoWidget::updateAngleManual(int i){
  _angle = 3*i;
  this->repaint(); //veikia
}

void OrthoDemoWidget::wheel(){

  glPushMatrix();
    glRotatef(_angle, 1 ,1, 1);
    glTranslatef(0, 0, -14/_scaler);
    glScalef(_scaler, _scaler, _scaler);
    this->hexo(3, 5, 3, 6, blueShinyMaterials);
  glPopMatrix();

  glPushMatrix();
    glRotatef(_angle, 1 ,1, 1);
    glTranslatef(0, 0, -14/_scaler);
    glScalef(_scaler, _scaler, _scaler);
    this->hexo(3, 5, 3, 6, blueShinyMaterials);
  glPopMatrix();

  glPushMatrix();
    glRotatef(_angle, 1 ,1, 1);
    glTranslatef(0, 0, 14/_scaler);
    glScalef(_scaler, _scaler, _scaler);
    this->hexo(3, 5, 3, 6, whiteShinyMaterials);
  glPopMatrix();

  glPushMatrix();
    glRotatef((double)_angle,1.,1.,1);
    glTranslatef(0,0,-14/_scaler);
    glScalef(_scaler, _scaler, _scaler);
    this->cylinder(3, 28, redShinyMaterials);
  glPopMatrix();
}

void OrthoDemoWidget::unify(double time){

  glLoadIdentity();
  glMatrixMode(GL_MODELVIEW);
  gluLookAt(_glupar._x,
  _glupar._y,
  _glupar._z,
  _glupar._at_x,
  _glupar._at_y,
  _glupar._at_z,
  _glupar._up_x,
  _glupar._up_y,
  _glupar._up_z);

  glPushMatrix();
    glTranslatef(-41, 0, 0);
    this->wheel();
  glPopMatrix();

  glPushMatrix();
    glTranslatef(41, 0, 0);
    // glScalef(_scaler, _scaler, _scaler);
    this->wheel();
  glPopMatrix();

  // glPushMatrix();
  // glLoadIdentity();
  // glTranslatef(0,0,-14/_scaler);
  //   glScalef(_scaler, _scaler, _scaler);
  //   this->cylinder(3, 28, redShinyMaterials);
  // glPopMatrix();


  // glLoadIdentity();
  // glMatrixMode(GL_MODELVIEW);
  // glTranslatef(-80.,-80.,0.);
  // glEnable(GL_DEPTH_TEST); // comment out depth test to observe the result
  //           gluLookAt(_glupar._x,
  //         _glupar._y,
  //         _glupar._z,
  //         _glupar._at_x,
  //         _glupar._at_y,
  //         _glupar._at_z,
  //         _glupar._up_x,
  //         _glupar._up_y,
  //         _glupar._up_z);
  // glRotatef(_angle, 1,0, 1);
  // this->pyramid(100.,brassMaterials);
  //
  // glLoadIdentity();
  //       gluLookAt(_glupar._x,
  //     _glupar._y,
  //     _glupar._z,
  //     _glupar._at_x,
  //     _glupar._at_y,
  //     _glupar._at_z,
  //     _glupar._up_x,
  //     _glupar._up_y,
  //     _glupar._up_z);
  // glTranslatef(-230.,100.,0.);
  // glRotatef((double)_angle,0.,0.,1.);
  // this->pyramid(100.,redShinyMaterials);
  // glLoadIdentity();
  // gluLookAt(_glupar._x,
  // _glupar._y,
  // _glupar._z,
  // _glupar._at_x,
  // _glupar._at_y,
  // _glupar._at_z,
  // _glupar._up_x,
  // _glupar._up_y,
  // _glupar._up_z);
  // // glTranslatef(200.,200.,0.);
  // glRotatef((double)_angle,1.,1.,0);
  // glTranslatef(0,-50,0);
  // glScalef(5,5,5);
  // this->arm(20.,89.,time);
  // glLoadIdentity();
  // gluLookAt(_glupar._x,
  // _glupar._y,
  // _glupar._z,
  // _glupar._at_x,
  // _glupar._at_y,
  // _glupar._at_z,
  // _glupar._up_x,
  // _glupar._up_y,
  // _glupar._up_z);
  // // glTranslatef(200.,200.,0.);
  // glRotatef((double)_angle,1.,1.,0);
  // glRotatef(90,1.,1.,0);
  // glTranslatef(0,0,0);
  // glScalef(0.5,0.5,0.5);
  // this->cylinder(30, redShinyMaterials);
}

void OrthoDemoWidget::renderPlane(const materialStruct& material){

  glMaterialfv(GL_FRONT, GL_AMBIENT,    material.ambient);
  glMaterialfv(GL_FRONT, GL_DIFFUSE,    material.diffuse);
  glMaterialfv(GL_FRONT, GL_SPECULAR,   material.specular);
  glMaterialf(GL_FRONT, GL_SHININESS,   material.shininess);

  glBegin(GL_POLYGON);
    glVertex3f(-50, 0, -50);
    glVertex3f(-50, 0, 50);
    glVertex3f(50, 0, 50);
    glVertex3f(50, 0, -50);
  glEnd();
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

        //shoulld render that plane stuff TODO
        this->renderPlane(redShinyMaterials); //not yet working
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
