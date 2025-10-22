#ifndef BASERENDERER_H
#define BASERENDERER_H

#include <QObject>
#include <QElapsedTimer>
#include <QList>

class QTimer;

// An interface for any object that can render an OpenGL scene.
// Inheriting QObject allows us to use signals/slots, for example,
// to tell the host widget that it needs to update.
class BaseRenderer : public QObject
{
    Q_OBJECT
public:
    BaseRenderer();
    virtual ~BaseRenderer() = default;

    // Called once when the OpenGL context is ready.
    // This is where shaders, VBOs, etc. are created.
    virtual void initialize();

    // Called every frame to draw the scene.
    virtual void paint();

    // Called when the widget is resized.
    virtual void resize(int w, int h) = 0;

    inline bool isInitialized();

signals:
    // A signal the renderer can emit to tell its host to repaint.
    void needsUpdate();

protected:
    inline void setInitialized(bool initialized);

private:
    bool m_initialized = false;
    QElapsedTimer m_paintGLElapsedTimer;
    QList<uint> m_paintGLElapsedTimes;
    QTimer *m_printPaintGLTimesTimer;
    uint m_initGLCount = 0;
};


bool BaseRenderer::isInitialized() {
    return m_initialized;
}

void BaseRenderer::setInitialized(bool initialized) {
    m_initialized = initialized;
}

#endif // BASERENDERER_H
