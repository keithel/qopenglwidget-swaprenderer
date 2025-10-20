#ifndef COLORCYCLEWIDGET_H
#define COLORCYCLEWIDGET_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions_4_3_Core>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLBuffer>
#include <QMatrix4x4>
#include <QElapsedTimer>

class QOpenGLShaderProgram;
class QTimer;

class ColorCycleWidget : public QOpenGLWidget, QOpenGLFunctions_4_3_Core
{
    Q_OBJECT
public:
    explicit ColorCycleWidget(QWidget *parent = nullptr);
    ~ColorCycleWidget();

protected:
    void initializeGL() override;
    void paintGL() override;
    void resizeGL(int w, int h) override;

private:
    void setup();

    QOpenGLShaderProgram *m_program = nullptr;
    QOpenGLVertexArrayObject m_vao;
    QOpenGLBuffer m_buffer;

    QMatrix4x4 m_projection;
    QElapsedTimer m_elapsedTimer;
    QTimer *m_timer;
};

#endif // COLORCYCLEWIDGET_H
