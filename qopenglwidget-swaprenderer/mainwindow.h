#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <memory>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class GLHostWidget;
class BaseRenderer;
class QTimer;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void swapContent();

private:
    Ui::MainWindow *ui;
    GLHostWidget *m_hostA;
    GLHostWidget *m_hostB;

    // The window now owns the renderers.
    // In a larger app, some other controller object might own them.
    std::unique_ptr<BaseRenderer> m_rendererA;
    std::unique_ptr<BaseRenderer> m_rendererB;
    QTimer *m_swapTimer;
};
#endif // MAINWINDOW_H
