#ifndef ROTATINGTRIRENDERER_H
#define ROTATINGTRIRENDERER_H

#include "baserenderer.h"
#include <QOpenGLFunctions_4_3_Core>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLBuffer>
#include <QMatrix4x4>

class QOpenGLShaderProgram;
class QTimer;

class RotatingTriRenderer : public BaseRenderer, protected QOpenGLFunctions_4_3_Core
{
    Q_OBJECT
public:
    RotatingTriRenderer();
    ~RotatingTriRenderer();

    void initialize() override;
    void paint() override;
    void resize(int w, int h) override;

private:
    void setup();

    QOpenGLShaderProgram *m_program = nullptr;
    QOpenGLVertexArrayObject m_vao;
    QOpenGLBuffer m_buffer;

    QMatrix4x4 m_projection;
    float m_rotation = 0.0f;
    QTimer *m_timer;
};

#endif // ROTATINGTRIRENDERER_H
