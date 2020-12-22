#include <GL/glut.h>
#include <QGLWidget>
#include <QDebug>
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


// constructor
OrthoDemoWidget::OrthoDemoWidget(QWidget *parent)
  : QGLWidget(parent),
    _ortho_par(-350.,350.,-350.,350.,-350.,350),
    _glupar(0.,0.,100.,0.,0.,0.,0.,1.,0.),
    _b_lighting(true),
    _angle(0.0)

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
    //
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

  glEnd();
// glNormal3fv(glm::value_ptr(n));
//   glColor3f(1.0,1.0,1.0);
  glBegin(GL_POLYGON);
    glVertex3f(v1[0], v1[1], v1[2]);
    glVertex3f(v1[0], v1[1], -100);
    glVertex3f(v2[0], v2[1], -100);
    glVertex3f(v2[0], v2[1], v2[2]);
  glEnd();

}

void OrthoDemoWidget::hexo(float inner, float outer, float nsides, float rings, const materialStruct& material){

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

  glutSolidTorus(inner, outer, nsides, rings);

}


void OrthoDemoWidget::updateAngle(){
  _angle -= 1.0; //clockwise
  this->repaint(); //paintGL used every time
}

void OrthoDemoWidget::updateAngleManual(int i){
  _angle = 3*i;
  this->repaint(); //paintGL used every time
}

// void OrthoDemoWidget::updateAngleManualV(int i){
//   _angle = i;
//   this->repaint(); //paintGL used every time
// }


// called every time the widget needs painting
void OrthoDemoWidget::paintGL()
	{ // paintGL()
	// clear the widget
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// You must set the matrix mode to model view directly before enabling the depth test
      	glMatrixMode(GL_MODELVIEW);
       	glEnable(GL_DEPTH_TEST); // comment out depth test to observe the result

	glLoadIdentity();
       	gluLookAt(_glupar._x,
		  _glupar._y,
		  _glupar._z,
		  _glupar._at_x,
		  _glupar._at_y,
		  _glupar._at_z,
		  _glupar._up_x,
		  _glupar._up_y,
		  _glupar._up_z);
  //
  // // glRotatef(45, 0,0,1);
  // glRotatef(_angle, 1,1, 1);
	// this->pyramid(100.,redShinyMaterials);
  // //
  // // glLoadIdentity();
  // //
  // // glTranslatef(250.,250.,0.);
  // // this->pyramid(50.,blueShinyMaterials);
  // // glLoadIdentity();
  // //
  // // glTranslatef(230.,0.,0.);
  // // glRotatef(45, 0, 0 ,1);
  // // this->pyramid(50.,blueShinyMaterials);
  // // glLoadIdentity();
  // // glTranslatef(250.,-250.,0.);
  // // this->pyramid(50.,blueShinyMaterials);
  // glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // Draw a white torus of outer radius 3, inner radius 0.5 with 15 stacks
  // and 30 slices.
  glColor3f(1.0, 1.0, 1.0);

  // glPushMatrix();
  glRotatef(_angle, 1 ,1, 0);
  this->hexo(10, 60, 30, 30, blueShinyMaterials);

  // Draw a red x-axis, a green y-axis, and a blue z-axis.  Each of the
  // axes are ten units long.
  // glColor3f(0.0, 0.0, 1.0);
  // glBegin(GL_LINES);
  //   glColor3f(1, 0, 0); glVertex3f(0, 0, 0); glVertex3f(10, 0, 0);
  //   glColor3f(0, 1, 0); glVertex3f(0, 0, 0); glVertex3f(0, 10, 0);
  //   glColor3f(0, 0, 1); glVertex3f(0, 0, 0); glVertex3f(0, 0, 10);
  // glEnd();
  glLoadIdentity();

  // You must set the matrix mode to model view directly before enabling the depth test

  glMatrixMode(GL_MODELVIEW);
  glTranslatef(-230.,-200.,0.);
  glEnable(GL_DEPTH_TEST); // comment out depth test to observe the result

            gluLookAt(_glupar._x,
          _glupar._y,
          _glupar._z,
          _glupar._at_x,
          _glupar._at_y,
          _glupar._at_z,
          _glupar._up_x,
          _glupar._up_y,
          _glupar._up_z);
  glRotatef(_angle, 1,0, 1);
  this->pyramid(100.,brassMaterials);

  glLoadIdentity();
        gluLookAt(_glupar._x,
      _glupar._y,
      _glupar._z,
      _glupar._at_x,
      _glupar._at_y,
      _glupar._at_z,
      _glupar._up_x,
      _glupar._up_y,
      _glupar._up_z);
  glTranslatef(-230.,100.,0.);
  glRotatef((double)_angle,0.,0.,1.);
  this->pyramid(100.,redShinyMaterials);
  glLoadIdentity();
	// flush to screen
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
