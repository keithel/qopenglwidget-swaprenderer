# qopenglwidget-swaprenderer
Show a better way of swapping QOpenGLWidget rendered content

This small project shows two different ways of swapping QOpenGLWidget rendered
content on a QMainWindow split with a QSplitter.

The first way is just to reparent the QOpenGLWidgets to the splitter in the
opposite order. This is generally considered the bad approach, as it ends up
destroying and recreating the context, and it can potentially lead to issues
with resource corruption if other OpenGL depends on those resources.
This is located in the `qopenglwidget-reparent` directory.

The second way is to share all QOpenGLContext resources using
`Qt::AA_ShareOpenGLContexts`, have all of the rendering logic that actually does
the OpenGL calls be housed in a separate class from the QOpenGLWidget - a
Renderer class, and then swap instances of those renderers between the
QOpenGLWidgets.
This is located in the `qopenglwidget-swaprenderer` directory.
