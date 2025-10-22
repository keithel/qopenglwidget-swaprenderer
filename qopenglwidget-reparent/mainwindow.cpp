#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "rotatingtriwidget.h"
#include "colorcyclewidget.h"
#include "logging.h"
#include <QTimer>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , m_swapTimer(new QTimer(this))
{
    ui->setupUi(this);

    m_widgetA = new RotatingTriWidget();
    m_widgetB = new ColorCycleWidget();

    ui->splitter->addWidget(m_widgetA);
    ui->splitter->addWidget(m_widgetB);
    ui->splitter->setStretchFactor(0, 1);
    ui->splitter->setStretchFactor(1, 1);

    connect(ui->swapButton, &QPushButton::clicked, this, &MainWindow::swapContent);
    connect(m_swapTimer, &QTimer::timeout, this, &MainWindow::swapContent);
    m_swapTimer->start(160);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::swapContent()
{
    // Reparent the widgets
    // This is the anti-pattern. We are physically moving the widgets.
    // In Qt, this often means destroying and recreating the native window handles.
    // Because AA_ShareOpenGLContexts is false, the OpenGL context is tied to that
    // window handle. When the handle is destroyed, the context and all its
    // resources become invalid, leading to corruption.

    QList<int> splitterItemSizes = ui->splitter->sizes();
    bool isA_first = (ui->splitter->widget(0) == m_widgetA);

    // QSplitter doesn't have a simple swap. We have to take the widgets
    // out and put them back in the opposite order. This action is
    // what triggers the reparenting and context destruction.
    if (isA_first) {
        qCDebug(perf) << "RotatingTriWidget is first";
        // Detach widgets from the splitter. This effectively sets their parent to null.
        m_widgetA->setParent(nullptr);
        m_widgetB->setParent(nullptr);
        // Re-insert in the opposite order.
        ui->splitter->insertWidget(0, m_widgetB);
        ui->splitter->insertWidget(1, m_widgetA);
    } else {
        qCDebug(perf) << "ColorCycleWidget is first";
        m_widgetA->setParent(nullptr);
        m_widgetB->setParent(nullptr);
        ui->splitter->insertWidget(0, m_widgetA);
        ui->splitter->insertWidget(1, m_widgetB);
    }
    ui->splitter->setSizes(splitterItemSizes);
}

