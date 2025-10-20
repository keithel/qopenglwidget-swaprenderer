#ifndef COLORCYCLERENDERER_H
#define COLORCYCLERENDERER_H

#include "irenderer.h"
#include <QOpenGLFunctions_4_3_Core>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLBuffer>
#include <QMatrix4x4>
#include <QElapsedTimer>

class QOpenGLShaderProgram;
class QTimer;

class ColorCycleRenderer : public IRenderer, protected QOpenGLFunctions_4_3_Core
{
    Q_OBJECT
public:
    ColorCycleRenderer();
    ~ColorCycleRenderer();

    void initialize() override;
    void paint() override;
    void resize(int w, int h) override;

private:
    void setup();

    QOpenGLShaderProgram *m_program = nullptr;
    QOpenGLVertexArrayObject m_vao;
    QOpenGLBuffer m_buffer;

    QMatrix4x4 m_projection;
    QElapsedTimer m_elapsedTimer;
    QTimer *m_timer;
};

#endif // COLORCYCLERENDERER_H
