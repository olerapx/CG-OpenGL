#ifndef OPENGLWIDGET_H
#define OPENGLWIDGET_H

#include <QGLWidget>
#include <QMouseEvent>
#include <iostream>

namespace Ui
{
    class OpenGLWidget;
}

class OpenGLWidget : public QGLWidget
{
    Q_OBJECT

public:
    explicit OpenGLWidget(QWidget *parent = 0);
    ~OpenGLWidget();

    inline void setDrawInner(bool draw) {drawInner = draw;}
    inline void setDrawOuter (bool draw) {drawOuter = draw;}

protected:
    bool drawInner = true, drawOuter = true;

    void initializeGL();
    void resizeGL(int width, int height);
    void paintGL();

    void initLight();

    void draw();
    void drawFirst();
    void drawSecond();

    void drawFirstBottomEdge();
    void drawFirstTopEdge();
    void drawFirstSideEdges();

    void drawSecondBottomEdge();
    void drawSecondTopEdge();
    void drawSecondSideEdges();

    QSize minimumSizeHint() const;
    QSize sizeHint() const;

    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);

    void normalizedGlVertex3d (double x, double y, double z);

public slots:
    void setXRotation(int angle);
    void setYRotation(int angle);
    void setZRotation(int angle);

signals:
    void xRotationChanged(int angle);
    void yRotationChanged(int angle);
    void zRotationChanged(int angle);

private:
    int xRot;
    int yRot;
    int zRot;

    double xScale = 3.0, yScale = 3.0, zScale = 2.0;
    double xShift = -1, yShift = -1, zShift = -1;

    QPoint lastPos;

    GLuint textureID;
    QImage texture;
};

#endif // OPENGLWIDGET_H
