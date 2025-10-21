#ifndef ROTATINGTRIWIDGET_H
#define ROTATINGTRIWIDGET_H

#include "baseglwidget.h"
#include <QOpenGLFunctions_4_3_Core>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLBuffer>
#include <QMatrix4x4>

class QOpenGLShaderProgram;
class QTimer;

class RotatingTriWidget : public BaseGLWidget, protected QOpenGLFunctions_4_3_Core
{
    Q_OBJECT
public:
    explicit RotatingTriWidget(QWidget *parent = nullptr);
    ~RotatingTriWidget();

protected:
    void initializeGL() override;
    void paintGL() override;
    void resizeGL(int w, int h) override;

private:
    void setup();

private:
    QOpenGLShaderProgram *m_program = nullptr;
    QOpenGLVertexArrayObject m_vao;
    QOpenGLBuffer m_buffer;

    QMatrix4x4 m_projection;
    float m_rotation = 0.f;
    QTimer *m_timer;
};

#endif // ROTATINGTRIWIDGET_H
