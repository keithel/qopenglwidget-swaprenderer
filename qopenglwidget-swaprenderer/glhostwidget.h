#ifndef GLHOSTWIDGET_H
#define GLHOSTWIDGET_H

#include <QOpenGLWidget>
#include <memory>

class IRenderer;

// This is a generic container widget. Its only job is to host a renderer
// and pass the OpenGL calls to it. It knows nothing about what is being drawn.
class GLHostWidget : public QOpenGLWidget
{
    Q_OBJECT
public:
    explicit GLHostWidget(QWidget *parent = nullptr);
    ~GLHostWidget();

    void setRenderer(std::unique_ptr<IRenderer> renderer);
    std::unique_ptr<IRenderer> takeRenderer();

protected:
    void initializeGL() override;
    void paintGL() override;
    void resizeGL(int w, int h) override;

private:
    std::unique_ptr<IRenderer> m_renderer;
};

#endif // GLHOSTWIDGET_H
