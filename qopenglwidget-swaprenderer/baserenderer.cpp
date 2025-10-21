#include "baserenderer.h"
#include <QTimer>
#include <QString>
#include <QDebug>

BaseRenderer::BaseRenderer()
    : QObject()
    , m_printPaintGLTimesTimer(new QTimer(this))
{
    connect(m_printPaintGLTimesTimer, &QTimer::timeout, this, [this](){
        if (m_paintGLElapsedTimes.empty())
            return;

        uint maxVal = 0;
        QString timesList;
        for(int i = 0; i < m_paintGLElapsedTimes.size(); i++) {
            auto time = m_paintGLElapsedTimes.at(i);
            if (time > maxVal)
                maxVal = time;
            timesList.append(QString::number(m_paintGLElapsedTimes.at(i)));
            if (i < m_paintGLElapsedTimes.size()-1)
                timesList.append(", ");
            else
                timesList.append("ms");
        }
        m_paintGLElapsedTimes.clear();
        qDebug() << metaObject()->className() << "init or swap paintGL took max" << maxVal << "ms. Last 1s times:" << timesList;
    });

    m_printPaintGLTimesTimer->start(1000);
}

void BaseRenderer::initialize()
{
    m_paintGLElapsedTimer.start();
}

void BaseRenderer::paint()
{
    m_paintGLElapsedTimes.append(static_cast<uint>(m_paintGLElapsedTimer.restart()));
}
