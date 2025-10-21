#include "glhostwidget.h"
#include "baserenderer.h"
#include <QDebug>
#include <QOpenGLContext>
#include <QOpenGLFunctions>

GLHostWidget::GLHostWidget(QWidget *parent)
    : QOpenGLWidget(parent)
{
}

GLHostWidget::~GLHostWidget()
{
    // Let unique_ptr handle deleting the renderer.
    // Make the context current first so the renderer's
    // OpenGL resources can be cleaned up properly in its destructor.
    if (m_renderer) {
        makeCurrent();
        m_renderer.reset();
        doneCurrent();
    }
}

void GLHostWidget::setRenderer(std::unique_ptr<BaseRenderer> renderer)
{
    if (m_renderer && isValid()) {
        makeCurrent();
        disconnect(m_renderer.get(), &BaseRenderer::needsUpdate, this, qOverload<>(&QWidget::update));
        doneCurrent();
    }

    m_renderer = std::move(renderer);

    if (m_renderer) {
        // Connect the renderer's request for an update to our update() slot.
        connect(m_renderer.get(), &BaseRenderer::needsUpdate, this, qOverload<>(&QWidget::update));
        if (isValid() && !m_renderer->isInitialized()) {
            // qDebug() << "Context is valid, initializing renderer.";
            makeCurrent();
            m_renderer->initialize();
            doneCurrent();
        }
        else {
            qDebug() << "Context not valid yet. Deferring renderer initialization.";
        }
    }
}

std::unique_ptr<BaseRenderer> GLHostWidget::takeRenderer()
{
    if (m_renderer)
        disconnect(m_renderer.get(), &BaseRenderer::needsUpdate, this, qOverload<>(&QWidget::update));
    return std::move(m_renderer);
}


void GLHostWidget::initializeGL()
{
    qDebug() << "GLHostWidget::initializeGL() initializing renderer.";
    if (m_renderer) {
        m_renderer->initialize();
    }
    else {
        // If no renderer set, just paint a background color.
        QOpenGLFunctions *f = QOpenGLContext::currentContext()->functions();
        f->glClearColor(0.2f, 0.2f, 0.25f, 1.0f);
        f->glClear(GL_COLOR_BUFFER_BIT);
    }
}

void GLHostWidget::paintGL()
{
    if (m_renderer)
        m_renderer->paint();
}

void GLHostWidget::resizeGL(int w, int h)
{
    if (m_renderer)
        m_renderer->resize(w, h);
}
