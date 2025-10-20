#ifndef IRENDERER_H
#define IRENDERER_H

#include <QObject>

// An abstract interface for any object that can render an OpenGL scene.
// Inheriting QObject allows us to use signals/slots, for example,
// to tell the host widget that it needs to update.
class IRenderer : public QObject
{
    Q_OBJECT
public:
    virtual ~IRenderer() = default;

    // Called once when the OpenGL context is ready.
    // This is where shaders, VBOs, etc. are created.
    virtual void initialize() = 0;

    // Called every frame to draw the scene.
    virtual void paint() = 0;

    // Called when the widget is resized.
    virtual void resize(int w, int h) = 0;

signals:
    // A signal the renderer can emit to tell its host to repaint.
    void needsUpdate();
};

#endif // IRENDERER_H
