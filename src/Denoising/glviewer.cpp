#include "glviewer.h"
#include <QFileDialog>
#include <QColorDialog>
#include <QOpenGLFunctions>
#include <QResizeEvent>

GLViewer::GLViewer(QWindow *parent)
    : QOpenGLWindow(QOpenGLWindow::NoPartialUpdate, parent), examiner_(nullptr), backgroundColor_(Qt::black)
{
    examiner_ = new MeshExaminer();
}

GLViewer::~GLViewer()
{
    delete examiner_;
}

void GLViewer::mousePressEvent(QMouseEvent *event)
{
    examiner_->mousePressEvent(event);
}

void GLViewer::mouseReleaseEvent(QMouseEvent *event)
{
    examiner_->mouseReleaseEvent(event);
}

void GLViewer::mouseMoveEvent(QMouseEvent *event)
{
    examiner_->mouseMoveEvent(event);
    this->update();
}

void GLViewer::wheelEvent(QWheelEvent *event)
{
    examiner_->wheelEvent(event);
    this->update();
}

void GLViewer::mouseDoubleClickEvent(QMouseEvent*)
{
    // No operation
}

void GLViewer::initializeGL()
{
    QOpenGLFunctions *gl = context()->functions();
    gl->glClearColor(backgroundColor_.redF(), backgroundColor_.greenF(), backgroundColor_.blueF(), 1.0f);
    examiner_->init();
}

void GLViewer::resizeEvent(QResizeEvent *event)
{
    QOpenGLWindow::resizeEvent(event);
    if (examiner_) {
        examiner_->reshape(event->size().width(), event->size().height());
    }
}

void GLViewer::paintEvent(QPaintEvent*)
{
    QOpenGLFunctions *gl = context()->functions();
    gl->glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    if (examiner_) {
        examiner_->draw();
    }
}

void GLViewer::updateMesh(const TriMesh &_mesh)
{
    examiner_->updateMesh(_mesh);
}

void GLViewer::resetMesh(const TriMesh &_mesh, bool _needNormalize)
{
    examiner_->resetMesh(_mesh, _needNormalize);
}
