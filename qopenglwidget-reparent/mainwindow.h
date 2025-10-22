#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class RotatingTriWidget;
class ColorCycleWidget;
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
    RotatingTriWidget *m_widgetA;
    ColorCycleWidget *m_widgetB;
    QTimer *m_swapTimer = nullptr;
};
#endif // MAINWINDOW_H
