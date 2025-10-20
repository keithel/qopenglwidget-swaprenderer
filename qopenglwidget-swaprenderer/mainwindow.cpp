#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "glhostwidget.h"
#include "rotatingtrirenderer.h"
#include "colorcyclerenderer.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // The host widgets are created and placed in the splitter once.
    // They will never move again.
    m_hostA = new GLHostWidget();
    m_hostB = new GLHostWidget();

    ui->splitter->addWidget(m_hostA);
    ui->splitter->addWidget(m_hostB);
    ui->splitter->setStretchFactor(0, 1);
    ui->splitter->setStretchFactor(1, 1);

    // Create the renderer objects.
    m_rendererA = std::make_unique<RotatingTriRenderer>();
    m_rendererB = std::make_unique<ColorCycleRenderer>();

    // Assign the initial renderers to the host widgets.
    m_hostA->setRenderer(std::move(m_rendererA));
    m_hostB->setRenderer(std::move(m_rendererB));

    connect(ui->swapButton, &QPushButton::clicked, this, &MainWindow::swapButtonClicked);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::swapButtonClicked()
{
    // THIS IS THE RECOMMENDED PATTERN.
    // We are not touching the widgets at all. We are only changing which
    // renderer object each widget points to. This is a fast, safe
    // pointer swap. No widgets are reparented, and no GL contexts
    // are destroyed.

    // Take the renderers back from the widgets
    auto rendererFromA = m_hostA->takeRenderer();
    auto rendererFromB = m_hostB->takeRenderer();

    // And give them to the other widget
    m_hostA->setRenderer(std::move(rendererFromB));
    m_hostB->setRenderer(std::move(rendererFromA));
}
