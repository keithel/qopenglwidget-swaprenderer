#include "colorcyclerenderer.h"
#include <QOpenGLShaderProgram>
#include <QTimer>
#include <QDebug>
#include <cmath>

static const char *cc_vertexShaderSource =
    "#version 430 core\n"
    "layout(location = 0) in vec2 pos;\n"
    "uniform mat4 mvp;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = mvp * vec4(pos.x, pos.y, 0.0, 1.0);\n"
    "}\n";

static const char *cc_fragmentShaderSource =
    "#version 430 core\n"
    "uniform vec3 triColor;\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(triColor, 1.0);\n"
    "}\n";

ColorCycleRenderer::ColorCycleRenderer()
    : m_timer(new QTimer(this))
{
    connect(m_timer, &QTimer::timeout, this, &IRenderer::needsUpdate);
    m_timer->start(16);
    m_elapsedTimer.start();
}

ColorCycleRenderer::~ColorCycleRenderer()
{
    m_buffer.destroy();
    m_vao.destroy();
    delete m_program;
}

void ColorCycleRenderer::initialize()
{
    qDebug() << "ColorCycleRenderer::initialize()";
    initializeOpenGLFunctions();

    m_program = new QOpenGLShaderProgram();
    m_program->addShaderFromSourceCode(QOpenGLShader::Vertex, cc_vertexShaderSource);
    m_program->addShaderFromSourceCode(QOpenGLShader::Fragment, cc_fragmentShaderSource);
    m_program->link();

    setup();
}

void ColorCycleRenderer::paint()
{
    glClearColor(0.15f, 0.15f, 0.15f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    if (!m_program || !m_program->isLinked()) return;

    m_program->bind();
    QOpenGLVertexArrayObject::Binder vaoBinder(&m_vao);

    QMatrix4x4 model; // identity
    m_program->setUniformValue("mvp", m_projection * model);

    float timeVal = m_elapsedTimer.elapsed() / 1000.0f;
    float red = (sin(timeVal) + 1.0f) / 2.0f;
    float green = (sin(timeVal + 2.0f) + 1.0f) / 2.0f;
    float blue = (sin(timeVal + 4.0f) + 1.0f) / 2.0f;
    m_program->setUniformValue("triColor", QVector3D(red, green, blue));

    glDrawArrays(GL_TRIANGLES, 0, 3);

    m_program->release();
}

void ColorCycleRenderer::resize(int w, int h)
{
    m_projection.setToIdentity();
    m_projection.ortho(-1.0f, 1.0f, -1.0f, 1.0f, -1.0f, 1.0f);
}

void ColorCycleRenderer::setup()
{
    static const GLfloat vertices[] = {
        -0.5f, -0.5f,
         0.5f, -0.5f,
         0.0f,  0.5f
    };

    m_vao.create();
    QOpenGLVertexArrayObject::Binder vaoBinder(&m_vao);

    m_buffer.create();
    m_buffer.bind();
    m_buffer.allocate(vertices, sizeof(vertices));

    m_program->enableAttributeArray(0);
    m_program->setAttributeBuffer(0, GL_FLOAT, 0, 2, 0);
    m_buffer.release();
}
