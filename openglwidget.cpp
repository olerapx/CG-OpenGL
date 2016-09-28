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

void OpenGLWidget::draw()
{
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glColor3d(1, 1, 1);

    glBegin (GL_POLYGON);
      normalizedGlVertex3d(0, 0, 0);
      normalizedGlVertex3d(0.2,0.1,0);
      normalizedGlVertex3d(0.3, 0.1, 0);
      normalizedGlVertex3d(0.5, 0, 0);
      normalizedGlVertex3d(0.4, 0.2, 0);
      normalizedGlVertex3d(0.4, 0.3, 0);
      normalizedGlVertex3d(0.5, 0.5, 0);
      normalizedGlVertex3d(0.3, 0.4, 0);
      normalizedGlVertex3d(0.2, 0.4, 0);
      normalizedGlVertex3d(0, 0.5, 0);
      normalizedGlVertex3d(0.1, 0.3, 0);
      normalizedGlVertex3d(0.1, 0.2, 0);
      normalizedGlVertex3d(0, 0, 0);
     glEnd();

     glBegin (GL_LINES);
        normalizedGlVertex3d(0, 0, 0);
        normalizedGlVertex3d(0, 0, 1);

        normalizedGlVertex3d(0.2,0.1,0);
        normalizedGlVertex3d(0.2,0.1,1);


        normalizedGlVertex3d(0.3, 0.1, 0);
        normalizedGlVertex3d(0.3, 0.1, 1);

        normalizedGlVertex3d(0.5, 0, 0);
        normalizedGlVertex3d(0.5, 0, 1);

        normalizedGlVertex3d(0.4, 0.2, 0);
        normalizedGlVertex3d(0.4, 0.2, 1);

        normalizedGlVertex3d(0.4, 0.3, 0);
        normalizedGlVertex3d(0.4, 0.3, 1);

        normalizedGlVertex3d(0.5, 0.5, 0);
        normalizedGlVertex3d(0.5, 0.5, 1);

        normalizedGlVertex3d(0.3, 0.4, 0);
        normalizedGlVertex3d(0.3, 0.4, 1);

        normalizedGlVertex3d(0.2, 0.4, 0);
        normalizedGlVertex3d(0.2, 0.4, 1);

        normalizedGlVertex3d(0, 0.5, 0);
        normalizedGlVertex3d(0, 0.5, 1);

        normalizedGlVertex3d(0.1, 0.3, 0);
       normalizedGlVertex3d(0.1, 0.3, 1);

        normalizedGlVertex3d(0.1, 0.2, 0);
        normalizedGlVertex3d(0.1, 0.2, 1);

        normalizedGlVertex3d(0, 0, 0);
        normalizedGlVertex3d(0, 0, 1);
     glEnd();

     glBegin (GL_POLYGON);
       normalizedGlVertex3d(0, 0, 1);
       normalizedGlVertex3d(0.2,0.1,1);
       normalizedGlVertex3d(0.3, 0.1, 1);
       normalizedGlVertex3d(0.5, 0, 1);
       normalizedGlVertex3d(0.4, 0.2, 1);
       normalizedGlVertex3d(0.4, 0.3, 1);
       normalizedGlVertex3d(0.5, 0.5, 1);
       normalizedGlVertex3d(0.3, 0.4, 1);
       normalizedGlVertex3d(0.2, 0.4, 1);
       normalizedGlVertex3d(0, 0.5, 1);
       normalizedGlVertex3d(0.1, 0.3, 1);
       normalizedGlVertex3d(0.1, 0.2, 1);
       normalizedGlVertex3d(0, 0, 1);
      glEnd();

      glColor3d(1, 0, 0);
      glBegin (GL_POLYGON);
        normalizedGlVertex3d(0.1, 0.15, 0);
        normalizedGlVertex3d(0.25, 0.2, 0);
        normalizedGlVertex3d(0.4, 0.15, 0);
        normalizedGlVertex3d(0.3, 0.25, 0);
        normalizedGlVertex3d(0.25, 0.38, 0);
        normalizedGlVertex3d(0.2, 0.25, 0);
        normalizedGlVertex3d(0.1, 0.15, 0);
      glEnd();

      glBegin (GL_LINES);
        normalizedGlVertex3d(0.1, 0.15, 0);
        normalizedGlVertex3d(0.1, 0.15, 1);

        normalizedGlVertex3d(0.25, 0.2, 0);
        normalizedGlVertex3d(0.25, 0.2, 1);

        normalizedGlVertex3d(0.4, 0.15, 0);
        normalizedGlVertex3d(0.4, 0.15, 1);

        normalizedGlVertex3d(0.3, 0.25, 0);
        normalizedGlVertex3d(0.3, 0.25, 1);

        normalizedGlVertex3d(0.25, 0.38, 0);
        normalizedGlVertex3d(0.25, 0.38, 1);

        normalizedGlVertex3d(0.2, 0.25, 0);
        normalizedGlVertex3d(0.2, 0.25, 1);

        normalizedGlVertex3d(0.1, 0.15, 0);
        normalizedGlVertex3d(0.1, 0.15, 1);
      glEnd();

      glBegin (GL_POLYGON);
        normalizedGlVertex3d(0.1, 0.15, 1);
        normalizedGlVertex3d(0.25, 0.2, 1);
        normalizedGlVertex3d(0.4, 0.15, 1);
        normalizedGlVertex3d(0.3, 0.25, 1);
        normalizedGlVertex3d(0.25, 0.38, 1);
        normalizedGlVertex3d(0.2, 0.25, 1);
        normalizedGlVertex3d(0.1, 0.15, 1);
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
