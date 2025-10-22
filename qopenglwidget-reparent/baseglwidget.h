#ifndef BASEGLWIDGET_H
#define BASEGLWIDGET_H

#include <QOpenGLWidget>
#include <QElapsedTimer>
#include <QList>

class QTimer;

class BaseGLWidget : public QOpenGLWidget
{
public:
    BaseGLWidget(QWidget *parent = nullptr);

    // QOpenGLWidget interface
protected:
    void paintGL() override;
    void initializeGL() override;

private:
    QElapsedTimer m_paintGLElapsedTimer;
    QList<uint> m_paintGLElapsedTimes;
    QTimer *m_printPaintGLTimesTimer;
};

#endif // BASEGLWIDGET_H
