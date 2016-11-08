#include "openglwidget.h"
#include <iostream>
OpenGLWidget::OpenGLWidget(QWidget *parent) :
    QGLWidget(QGLFormat(QGL::SampleBuffers), parent)

{
    xRot = 0;
    yRot = 0;
    zRot = 0;
}

OpenGLWidget::~OpenGLWidget()
{

}

QSize OpenGLWidget::minimumSizeHint() const
{
    return QSize(50, 50);
}

QSize OpenGLWidget::sizeHint() const
{
    return QSize(400, 400);
}

void OpenGLWidget::initializeGL()
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);
    glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
    glEnable(GL_NORMALIZE);
    glEnable(GL_TEXTURE_2D);

    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);

    QImage temp("texture.jpg");
    texture = QGLWidget::convertToGLFormat(temp);

    glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, texture.width(),  texture.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE,  texture.bits() );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );

    float ambient[4] = {0, 0, 0, 1};
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambient);
    initLight();
}

void OpenGLWidget::resizeGL(int width, int height)
{
    int side = qMin(width, height);
    glViewport((width - side) / 2, (height - side) / 2, side, side);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-2, +2, -2, +2, 1.0, 15.0);

    glMatrixMode(GL_MODELVIEW);
}

void OpenGLWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glLoadIdentity();
    glTranslatef(0.0, 0.0, -10.0);
    glRotatef((double)xRot / 16.0, 1.0, 0.0, 0.0);
    glRotatef((double)yRot / 16.0, 0.0, 1.0, 0.0);
    glRotatef((double)zRot / 16.0, 0.0, 0.0, 1.0);

    draw();
}

void OpenGLWidget::normalizedGlVertex3d(double x, double y, double z)
{
   glVertex3d(x * xScale + xShift, y * yScale + yShift, z * zScale + zShift);
}

void OpenGLWidget::initLight()
{
    float att = 0.3;
    float radius = 7;
    float kQ = att / (3* radius * radius);
    float kL = att / (3 * radius);
    float kC = att / 3;

    glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, kC);
    glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, kL);
    glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, kQ);

    GLfloat light0_position[4] = { 0, 0, 10, 1.0 };
    glLightfv(GL_LIGHT0, GL_POSITION, light0_position);

    GLfloat light0_diffuse[] = {1.0, 0.5, 0.0, 0.0};
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light0_diffuse);

    GLfloat light0_ambient[] = {1.0, 1.0, 1.0, 0.0};
    glLightfv(GL_LIGHT0, GL_AMBIENT, light0_ambient);

    GLfloat light0_specular[] = {1.0, 1.0, 1.0, 0.0};
    glLightfv(GL_LIGHT0, GL_SPECULAR, light0_specular);

    GLfloat light1_position[4] = {1.8f*xScale + xShift, 0.0f*yScale + yShift, -5.0f*zScale + zShift, 1.0 };
    glLightfv(GL_LIGHT1, GL_POSITION, light1_position);

    GLfloat light1_spot[] = {0.0f * xScale + xShift, 0.0f * yScale + yShift, 0.0f * zScale + zShift, 1};
    glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, light1_spot);
    glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 90);

    GLfloat light1_diffuse[] = {0.5, 1.0, 0.5, 0.0};
    glLightfv(GL_LIGHT1, GL_DIFFUSE, light1_diffuse);

    GLfloat light1_ambient[] = {1.0, 1.0, 1.0, 0.0};
    glLightfv(GL_LIGHT1, GL_AMBIENT, light1_ambient);

    GLfloat light1_specular[] = {1.0, 1.0, 1.0, 0.0};
    glLightfv(GL_LIGHT1, GL_SPECULAR, light1_specular);
}

void OpenGLWidget::draw()
{
    GLfloat material_ambient[] = {0.2, 0.2, 0.2, 1.0};
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT,  material_ambient);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS,  120);

    GLfloat material_specular[] = {0, 0.5, 0.5, 1.0};
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR,  material_specular);

    if (drawOuter)
       drawFirst();
   if (drawInner)
        drawSecond();
}

void OpenGLWidget::drawFirst()
{
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    drawFirstBottomEdge();
    drawFirstTopEdge();
    drawFirstSideEdges();
}

void OpenGLWidget::drawSecond()
{
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    drawSecondBottomEdge();
    drawSecondTopEdge();
    drawSecondSideEdges();
}

void OpenGLWidget::drawFirstBottomEdge()
{

    glFrontFace(GL_CW);
    glBegin (GL_POLYGON);
        glTexCoord2f(0, 0);
        normalizedGlVertex3d(0, 0, 0);

        glTexCoord2f(0.2, 0.1);
        normalizedGlVertex3d(0.2,0.1,0);

        glTexCoord2f(0.2, 0.2);
        normalizedGlVertex3d(0.2,0.2,0);

        glTexCoord2f(0.1, 0.2);
        normalizedGlVertex3d(0.1, 0.2, 0);

        normalizedGlVertex3d(0, 0, 0);
    glEnd();

    glBegin (GL_POLYGON);
        glTexCoord2f(0.3, 0.1);
        normalizedGlVertex3d(0.3, 0.1, 0);

        glTexCoord2f(0.5, 0);
        normalizedGlVertex3d(0.5, 0, 0);

        glTexCoord2f(0.4, 0.2);
        normalizedGlVertex3d(0.4, 0.2, 0);

        glTexCoord2f(0.3, 0.2);
        normalizedGlVertex3d(0.3, 0.2, 0);

        normalizedGlVertex3d(0.3, 0.1, 0);
    glEnd();

    glBegin (GL_POLYGON);
        glTexCoord2f(0.4, 0.3);
        normalizedGlVertex3d(0.4, 0.3, 0);

        glTexCoord2f(0.5, 0.5);
        normalizedGlVertex3d(0.5, 0.5, 0);

        glTexCoord2f(0.3, 0.4);
        normalizedGlVertex3d(0.3, 0.4, 0);

        glTexCoord2f(0.3, 0.3);
        normalizedGlVertex3d(0.3, 0.3, 0);

        normalizedGlVertex3d(0.4, 0.3, 0);
    glEnd();

    glBegin (GL_POLYGON);
        glTexCoord2f(0.2, 0.4);
        normalizedGlVertex3d(0.2, 0.4, 0);

        glTexCoord2f(0, 0.5);
        normalizedGlVertex3d(0, 0.5, 0);

        glTexCoord2f(0.1, 0.3);
        normalizedGlVertex3d(0.1, 0.3, 0);

        glTexCoord2f(0.2, 0.3);
        normalizedGlVertex3d(0.2, 0.3, 0);

        normalizedGlVertex3d(0.2, 0.4, 0);
    glEnd();

    glBegin (GL_POLYGON);
        glTexCoord2f(0.1, 0.1);
        normalizedGlVertex3d(0.1, 0.1, 0);

        glTexCoord2f(0.4, 0.1);
        normalizedGlVertex3d(0.4, 0.1, 0);

        glTexCoord2f(0.4, 0.4);
        normalizedGlVertex3d(0.4, 0.4, 0);

        glTexCoord2f(0.1, 0.4);
        normalizedGlVertex3d(0.1, 0.4, 0);

        normalizedGlVertex3d(0.1, 0.1, 0);
    glEnd();
    glFrontFace(GL_CCW);
}

void OpenGLWidget::drawFirstTopEdge()
{
    glBegin (GL_POLYGON);
        glTexCoord2f(0, 0);
        normalizedGlVertex3d(0, 0, 1);

        glTexCoord2f(0.2, 0.1);
        normalizedGlVertex3d(0.2,0.1,1);

        glTexCoord2f(0.2, 0.2);
        normalizedGlVertex3d(0.2,0.2,1);

        glTexCoord2f(0.1, 0.2);
        normalizedGlVertex3d(0.1, 0.2, 1);

        normalizedGlVertex3d(0, 0, 1);
    glEnd();

    glBegin (GL_POLYGON);
        glTexCoord2f(0.3, 0.1);
        normalizedGlVertex3d(0.3, 0.1, 1);

        glTexCoord2f(0.5, 0);
        normalizedGlVertex3d(0.5, 0, 1);

        glTexCoord2f(0.4, 0.2);
        normalizedGlVertex3d(0.4, 0.2, 1);

        glTexCoord2f(0.3, 0.2);
        normalizedGlVertex3d(0.3, 0.2, 1);

        normalizedGlVertex3d(0.3, 0.1, 1);
    glEnd();

    glBegin (GL_POLYGON);
        glTexCoord2f(0.4, 0.3);
        normalizedGlVertex3d(0.4, 0.3, 1);

        glTexCoord2f(0.5, 0.5);
        normalizedGlVertex3d(0.5, 0.5, 1);

        glTexCoord2f(0.3, 0.4);
        normalizedGlVertex3d(0.3, 0.4, 1);

        glTexCoord2f(0.3, 0.3);
        normalizedGlVertex3d(0.3, 0.3, 1);

        normalizedGlVertex3d(0.4, 0.3, 1);
    glEnd();

    glBegin (GL_POLYGON);
        glTexCoord2f(0.2, 0.4);
        normalizedGlVertex3d(0.2, 0.4, 1);

        glTexCoord2f(0, 0.5);
        normalizedGlVertex3d(0, 0.5, 1);

        glTexCoord2f(0.1, 0.3);
        normalizedGlVertex3d(0.1, 0.3, 1);

        glTexCoord2f(0.2, 0.3);
        normalizedGlVertex3d(0.2, 0.3, 1);

        normalizedGlVertex3d(0.2, 0.4, 1);
    glEnd();

    glBegin (GL_POLYGON);
        glTexCoord2f(0.1, 0.1);
        normalizedGlVertex3d(0.1, 0.1, 1);

        glTexCoord2f(0.4, 0.1);
        normalizedGlVertex3d(0.4, 0.1, 1);

        glTexCoord2f(0.4, 0.4);
        normalizedGlVertex3d(0.4, 0.4, 1);

        glTexCoord2f(0.1, 0.4);
        normalizedGlVertex3d(0.1, 0.4, 1);

        normalizedGlVertex3d(0.1, 0.1, 1);
    glEnd();
}

void OpenGLWidget::drawFirstSideEdges()
{
    glFrontFace(GL_CW);
    glBegin (GL_POLYGON);
       glTexCoord2f(0, 0);
       normalizedGlVertex3d(0, 0, 0);

       glTexCoord2f(0, 1);
       normalizedGlVertex3d(0, 0, 1);

       glTexCoord2f(1, 1);
       normalizedGlVertex3d(0.2,0.1,1);

       glTexCoord2f(1, 0);
       normalizedGlVertex3d(0.2,0.1,0);

       normalizedGlVertex3d(0, 0, 0);
     glEnd();

    glFrontFace(GL_CCW);
    glBegin (GL_POLYGON);
        glTexCoord2f(0, 0);
        normalizedGlVertex3d(0.2,0.1,0);

        glTexCoord2f(0, 1);
        normalizedGlVertex3d(0.3, 0.1, 0);

        glTexCoord2f(1, 1);
        normalizedGlVertex3d(0.3, 0.1, 1);

        glTexCoord2f(1, 0);
        normalizedGlVertex3d(0.2,0.1,1);

        normalizedGlVertex3d(0.2,0.1,0);
    glEnd();

    glFrontFace(GL_CW);
    glBegin (GL_POLYGON);
       glTexCoord2f(0, 0);
       normalizedGlVertex3d(0.3, 0.1, 0);

       glTexCoord2f(0, 1);
       normalizedGlVertex3d(0.3, 0.1, 1);

       glTexCoord2f(1, 1);
       normalizedGlVertex3d(0.5, 0, 1);

       glTexCoord2f(1, 0);
       normalizedGlVertex3d(0.5, 0, 0);

       normalizedGlVertex3d(0.3, 0.1, 0);
    glEnd();

    glFrontFace(GL_CCW);
    glBegin (GL_POLYGON);
        glTexCoord2f(0, 0);
        normalizedGlVertex3d(0.5, 0, 0);

        glTexCoord2f(0, 1);
        normalizedGlVertex3d(0.4, 0.2, 0);

        glTexCoord2f(1, 1);
        normalizedGlVertex3d(0.4, 0.2, 1);

        glTexCoord2f(1, 0);
        normalizedGlVertex3d(0.5, 0, 1);

        normalizedGlVertex3d(0.5, 0, 0);
    glEnd();
glFrontFace(GL_CW);
    glBegin (GL_POLYGON);
      glTexCoord2f(0, 0);
      normalizedGlVertex3d(0.4, 0.2, 0);

      glTexCoord2f(0, 1);
      normalizedGlVertex3d(0.4, 0.2, 1);

      glTexCoord2f(1, 1);
      normalizedGlVertex3d(0.4, 0.3, 1);

      glTexCoord2f(1, 0);
      normalizedGlVertex3d(0.4, 0.3, 0);

      normalizedGlVertex3d(0.4, 0.2, 0);
    glEnd();
glFrontFace(GL_CW);
    glBegin (GL_POLYGON);
        glTexCoord2f(0, 0);
        normalizedGlVertex3d(0.5, 0.5, 0);

        glTexCoord2f(0, 1);
        normalizedGlVertex3d(0.4, 0.3, 0);

        glTexCoord2f(1, 1);
        normalizedGlVertex3d(0.4, 0.3, 1);

        glTexCoord2f(1, 0);
        normalizedGlVertex3d(0.5, 0.5, 1);

        normalizedGlVertex3d(0.5, 0.5, 0);
    glEnd();
    glFrontFace(GL_CW);
    glBegin (GL_POLYGON);
       glTexCoord2f(0, 0);
       normalizedGlVertex3d(0.5, 0.5, 0);

       glTexCoord2f(0, 1);
       normalizedGlVertex3d(0.5, 0.5, 1);

       glTexCoord2f(1, 1);
       normalizedGlVertex3d(0.3, 0.4, 1);

       glTexCoord2f(1, 0);
       normalizedGlVertex3d(0.3, 0.4, 0);

       normalizedGlVertex3d(0.5, 0.5, 0);
    glEnd();
    glFrontFace(GL_CCW);
    glBegin (GL_POLYGON);
        glTexCoord2f(0, 0);
        normalizedGlVertex3d(0.3, 0.4, 0);

        glTexCoord2f(0, 1);
        normalizedGlVertex3d(0.2, 0.4, 0);

        glTexCoord2f(1, 1);
        normalizedGlVertex3d(0.2, 0.4, 1);

        glTexCoord2f(1, 0);
        normalizedGlVertex3d(0.3, 0.4, 1);

        normalizedGlVertex3d(0.3, 0.4, 0);
    glEnd();
    glFrontFace(GL_CW);
    glBegin (GL_POLYGON);
       glTexCoord2f(0, 0);
       normalizedGlVertex3d(0.2, 0.4, 0);

       glTexCoord2f(0, 1);
       normalizedGlVertex3d(0.2, 0.4, 1);

       glTexCoord2f(1, 1);
       normalizedGlVertex3d(0, 0.5, 1);

       glTexCoord2f(1, 0);
       normalizedGlVertex3d(0, 0.5, 0);

       normalizedGlVertex3d(0.2, 0.4, 0);
    glEnd();
    glFrontFace(GL_CCW);
    glBegin (GL_POLYGON);
        glTexCoord2f(0, 0);
        normalizedGlVertex3d(0, 0.5, 0);

        glTexCoord2f(0, 1);
        normalizedGlVertex3d(0.1, 0.3, 0);

        glTexCoord2f(1, 1);
        normalizedGlVertex3d(0.1, 0.3, 1);

        glTexCoord2f(1, 0);
        normalizedGlVertex3d(0, 0.5, 1);

        normalizedGlVertex3d(0, 0.5, 0);
    glEnd();
glFrontFace(GL_CW);
    glBegin (GL_POLYGON);
       glTexCoord2f(0, 0);
       normalizedGlVertex3d(0.1, 0.3, 0);

       glTexCoord2f(0, 1);
       normalizedGlVertex3d(0.1, 0.3, 1);

       glTexCoord2f(1, 1);
       normalizedGlVertex3d(0.1, 0.2, 1);

       glTexCoord2f(1, 0);
       normalizedGlVertex3d(0.1, 0.2, 0);

       normalizedGlVertex3d(0.1, 0.3, 0);
    glEnd();
glFrontFace(GL_CCW);
    glBegin (GL_POLYGON);
        glTexCoord2f(0, 0);
        normalizedGlVertex3d(0.1, 0.2, 0);

        glTexCoord2f(0, 1);
        normalizedGlVertex3d(0, 0, 0);

        glTexCoord2f(1, 1);
        normalizedGlVertex3d(0, 0, 1);

        glTexCoord2f(1, 0);
        normalizedGlVertex3d(0.1, 0.2, 1);

        normalizedGlVertex3d(0.1, 0.2, 0);
    glEnd();
}

void OpenGLWidget::drawSecondBottomEdge()
{
   glFrontFace(GL_CW);
   glBegin (GL_POLYGON);
        glTexCoord2f(0.1, 0.15);
        normalizedGlVertex3d(0.1, 0.15, 0.01);

        glTexCoord2f(0.25, 0.2);
        normalizedGlVertex3d(0.25, 0.2, 0.01);

        glTexCoord2f(0.25, 0.25);
        normalizedGlVertex3d(0.25, 0.25, 0.01);

        glTexCoord2f(0.2, 0.25);
        normalizedGlVertex3d(0.2, 0.25, 0.01);

        glTexCoord2f(0.1, 0.15);
        normalizedGlVertex3d(0.1, 0.15, 0.01);
   glEnd();

   glBegin (GL_POLYGON);
        glTexCoord2f(0.2, 0.25);
        normalizedGlVertex3d(0.2, 0.25, 0.01);

        glTexCoord2f(0.3, 0.25);
        normalizedGlVertex3d(0.3, 0.25, 0.01);

        glTexCoord2f(0.25, 0.38);
        normalizedGlVertex3d(0.25, 0.38, 0.01);

        glTexCoord2f(0.2, 0.25);
        normalizedGlVertex3d(0.2, 0.25, 0.01);
   glEnd();

   glBegin (GL_POLYGON);
        glTexCoord2f(0.25, 0.2);
        normalizedGlVertex3d(0.25, 0.2, 0.01);

        glTexCoord2f(0.4, 0.15);
        normalizedGlVertex3d(0.4, 0.15, 0.01);

        glTexCoord2f(0.3, 0.25);
        normalizedGlVertex3d(0.3, 0.25, 0.01);

        glTexCoord2f(0.25, 0.25);
        normalizedGlVertex3d(0.25, 0.25, 0.01);

        glTexCoord2f(0.25, 0.2);
        normalizedGlVertex3d(0.25, 0.2, 0.01);
   glEnd();
   glFrontFace(GL_CCW);
}

void OpenGLWidget::drawSecondTopEdge()
{
    glBegin (GL_POLYGON);
         glTexCoord2f(0.1, 0.15);
         normalizedGlVertex3d(0.1, 0.15, 0.99);

         glTexCoord2f(0.25, 0.2);
         normalizedGlVertex3d(0.25, 0.2, 0.99);

         glTexCoord2f(0.25, 0.25);
         normalizedGlVertex3d(0.25, 0.25, 0.99);

         glTexCoord2f(0.2, 0.25);
         normalizedGlVertex3d(0.2, 0.25, 0.99);

         glTexCoord2f(0.1, 0.15);
         normalizedGlVertex3d(0.1, 0.15, 0.99);
    glEnd();

    glBegin (GL_POLYGON);
         glTexCoord2f(0.2, 0.25);
         normalizedGlVertex3d(0.2, 0.25, 0.99);

         glTexCoord2f(0.3, 0.25);
         normalizedGlVertex3d(0.3, 0.25, 0.99);

         glTexCoord2f(0.25, 0.38);
         normalizedGlVertex3d(0.25, 0.38, 0.99);

         glTexCoord2f(0.2, 0.25);
         normalizedGlVertex3d(0.2, 0.25, 0.99);
    glEnd();

    glBegin (GL_POLYGON);
         glTexCoord2f(0.25, 0.2);
         normalizedGlVertex3d(0.25, 0.2, 0.99);

         glTexCoord2f(0.4, 0.15);
         normalizedGlVertex3d(0.4, 0.15, 0.99);

         glTexCoord2f(0.3, 0.25);
         normalizedGlVertex3d(0.3, 0.25, 0.99);

         glTexCoord2f(0.25, 0.25);
         normalizedGlVertex3d(0.25, 0.25, 0.99);

         glTexCoord2f(0.25, 0.2);
         normalizedGlVertex3d(0.25, 0.2, 0.99);
    glEnd();
}

void OpenGLWidget::drawSecondSideEdges()
{
    glBegin (GL_POLYGON);
        glTexCoord2f(0, 0);
        normalizedGlVertex3d(0.1, 0.15, 0);

        glTexCoord2f(0, 1);
        normalizedGlVertex3d(0.25, 0.2, 0);

        glTexCoord2f(1, 1);
        normalizedGlVertex3d(0.25, 0.2, 1);

        glTexCoord2f(1, 0);
        normalizedGlVertex3d(0.1, 0.15, 1);

        normalizedGlVertex3d(0.1, 0.15, 0);
    glEnd();

    glBegin (GL_POLYGON);
        glTexCoord2f(0, 0);
        normalizedGlVertex3d(0.25, 0.2, 0);

        glTexCoord2f(0, 1);
        normalizedGlVertex3d(0.4, 0.15, 0);

        glTexCoord2f(1, 1);
        normalizedGlVertex3d(0.4, 0.15, 1);

        glTexCoord2f(1, 0);
        normalizedGlVertex3d(0.25, 0.2, 1);

        normalizedGlVertex3d(0.25, 0.2, 0);
    glEnd();
glFrontFace(GL_CW);
    glBegin (GL_POLYGON);
        glTexCoord2f(0, 0);
        normalizedGlVertex3d(0.1, 0.15, 0);

        glTexCoord2f(0, 1);
        normalizedGlVertex3d(0.2, 0.25, 0);

        glTexCoord2f(1, 1);
        normalizedGlVertex3d(0.2, 0.25, 1);

        glTexCoord2f(1, 0);
        normalizedGlVertex3d(0.1, 0.15, 1);

        normalizedGlVertex3d(0.1, 0.15, 0);
    glEnd();

    glBegin (GL_POLYGON);
        glTexCoord2f(0, 0);
        normalizedGlVertex3d(0.2, 0.25, 0);

        glTexCoord2f(0, 1);
        normalizedGlVertex3d(0.25, 0.38, 0);

        glTexCoord2f(1, 1);
        normalizedGlVertex3d(0.25, 0.38, 1);

        glTexCoord2f(1, 0);
        normalizedGlVertex3d(0.2, 0.25, 1);

        normalizedGlVertex3d(0.2, 0.25, 0);
    glEnd();
    glFrontFace(GL_CCW);
    glBegin (GL_POLYGON);
        glTexCoord2f(0, 0);
        normalizedGlVertex3d(0.4, 0.15, 0);

        glTexCoord2f(0, 1);
        normalizedGlVertex3d(0.3, 0.25, 0);

        glTexCoord2f(1, 1);
        normalizedGlVertex3d(0.3, 0.25, 1);

        glTexCoord2f(1, 0);
        normalizedGlVertex3d(0.4, 0.15, 1);

        normalizedGlVertex3d(0.4, 0.15, 0);
    glEnd();

    glBegin (GL_POLYGON);
        glTexCoord2f(0, 0);
        normalizedGlVertex3d(0.3, 0.25, 0);

        glTexCoord2f(0, 1);
        normalizedGlVertex3d(0.25, 0.38, 0);

        glTexCoord2f(1, 1);
        normalizedGlVertex3d(0.25, 0.38, 1);

        glTexCoord2f(1, 0);
        normalizedGlVertex3d(0.3, 0.25, 1);

        normalizedGlVertex3d(0.3, 0.25, 0);
    glEnd();
}

static void normalizeAngle(int &angle)
{
    while (angle < 0)
        angle += 360 * 16;

    while (angle > 360)
        angle -= 360 * 16;
}

void OpenGLWidget::setXRotation(int angle)
{
    normalizeAngle(angle);
    if (angle != xRot)
    {
        xRot = angle;
        updateGL();
    }
}

void OpenGLWidget::setYRotation(int angle)
{
    normalizeAngle(angle);

    if (angle != yRot)
    {
        yRot = angle;
        updateGL();
    }
}

void OpenGLWidget::setZRotation(int angle)
{
    normalizeAngle(angle);
    if (angle != zRot)
    {
        zRot = angle;
        updateGL();
    }
}

void OpenGLWidget::mousePressEvent(QMouseEvent *event)
{
    lastPos = event->pos();
}

void OpenGLWidget::mouseMoveEvent(QMouseEvent *event)
{
    int dx = event->x() - lastPos.x();
    int dy = event->y() - lastPos.y();

    if (event->buttons() & Qt::LeftButton)
    {
        setXRotation(xRot + 8 * dy);
        setYRotation(yRot + 8 * dx);
    }
    else if (event->buttons() & Qt::RightButton)
    {
        setXRotation(xRot + 8 * dy);
        setZRotation(zRot + 8 * dx);
    }
    lastPos = event->pos();
}
