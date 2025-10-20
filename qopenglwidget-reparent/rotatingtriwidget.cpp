#include "rotatingtriwidget.h"
#include <QOpenGLShaderProgram>
#include <QTimer>

static const char *vertexShaderSource =
    "#version 430 core\n"
    "layout(location = 0) in vec2 pos;\n"
    "uniform mat4 mvp;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = mvp * vec4(pos.x, pos.y, 0.0, 1.0);\n"
    "}\n";

static const char *fragmentShaderSource =
    "#version 430 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(0.2, 0.5, 0.9, 1.0);\n"
    "}\n";

RotatingTriWidget::RotatingTriWidget(QWidget *parent)
    : m_timer(new QTimer(this))
{
    connect(m_timer, &QTimer::timeout, this, qOverload<>(&QWidget::update));
    m_timer->start(16);
}

RotatingTriWidget::~RotatingTriWidget()
{
    makeCurrent();
    m_buffer.destroy();
    m_vao.destroy();
    delete m_program;
    doneCurrent();
}

void RotatingTriWidget::initializeGL()
{
    // This function is called ONCE per context creation.
    // When reparenting happens, a NEW context is created and this is called again.
    // However, the destructor above might not have been called for the old context,
    // or resource IDs can get mixed up, leading to issues.
    qDebug() << "RotatingTriWidget::initializeGL()";

    initializeOpenGLFunctions();

    m_program = new QOpenGLShaderProgram(this);
    m_program->addShaderFromSourceCode(QOpenGLShader::Vertex, vertexShaderSource);
    m_program->addShaderFromSourceCode(QOpenGLShader::Fragment, fragmentShaderSource);
    m_program->link();

    setup();
}

void RotatingTriWidget::paintGL()
{
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    if (!m_program || !m_program->isLinked()) return;

    m_program->bind();
    QOpenGLVertexArrayObject::Binder vaoBinder(&m_vao);

    QMatrix4x4 model;
    model.rotate(m_rotation, 0, 0, 1);
    m_rotation += 1.0f;

    m_program->setUniformValue("mvp", m_projection * model);

    glDrawArrays(GL_TRIANGLES, 0, 3);

    m_program->release();
}

void RotatingTriWidget::resizeGL(int w, int h)
{
    m_projection.setToIdentity();
    m_projection.ortho(-1.0f, 1.0f, -1.0f, 1.0f, -1.0f, 1.0f);
}

void RotatingTriWidget::setup()
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
