#include "baseglwidget.h"
#include "logging.h"
#include <QTimer>
#include <QString>
#include <algorithm>

BaseGLWidget::BaseGLWidget(QWidget *parent)
    : QOpenGLWidget(parent)
    , m_printPaintGLTimesTimer(new QTimer(this))
{
    connect(m_printPaintGLTimesTimer, &QTimer::timeout, this, [this](){
        if (m_paintGLElapsedTimes.empty())
            return;

        uint maxVal = *std::max_element(m_paintGLElapsedTimes.constBegin(), m_paintGLElapsedTimes.constEnd());
        qCInfo(perf) << metaObject()->className() << m_initGLCount << "init or swap paintGL took max" << maxVal << "ms over 1s.";

        if (perf().isInfoEnabled()) {
            QString timesList;
            for(int i = 0; i < m_paintGLElapsedTimes.size(); i++) {
                timesList.append(QString::number(m_paintGLElapsedTimes.at(i)));
                if (i < m_paintGLElapsedTimes.size()-1)
                    timesList.append(", ");
                else
                    timesList.append("ms");
            }
            qCDebug(perf) << metaObject()->className() << "  Last 1s times:" << timesList;
        }
        m_paintGLElapsedTimes.clear();
        m_initGLCount = 0;
    });

    m_printPaintGLTimesTimer->start(1000);
}

void BaseGLWidget::initializeGL()
{
    m_paintGLElapsedTimer.start();
    m_initGLCount++;
}

void BaseGLWidget::paintGL()
{
    m_paintGLElapsedTimes.append(static_cast<uint>(m_paintGLElapsedTimer.restart()));
}
