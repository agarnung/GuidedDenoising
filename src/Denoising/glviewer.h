#ifndef GLVIEWER_H
#define GLVIEWER_H

#include <QOpenGLWindow>
#include <QColorDialog>
#include "meshexaminer.h"

class GLViewer : public QOpenGLWindow
{
    Q_OBJECT

public:
    explicit GLViewer(QWindow *parent = nullptr);
    ~GLViewer();

    void updateMesh(const TriMesh &_mesh);
    void resetMesh(const TriMesh &_mesh, bool _needNormalize = false);

    MeshExaminer* getExaminer() {
        return examiner_;
    }

public slots:
    void setDrawPointsStatus(bool _val) {
        examiner_->setDrawPointsStatus(_val);
        this->update();
    }

    void setDrawFacesStatus(bool _val) {
        examiner_->setDrawFacesStatus(_val);
        this->update();
    }

    void setDrawEdgesStatus(bool _val) {
        examiner_->setDrawEdgesStatus(_val);
        this->update();
    }

    void setBackgroundColor() {
        QColor color = QColorDialog::getColor(Qt::black, nullptr, tr("Set Background Color!"));
        if (!color.isValid()) return;
        backgroundColor_ = color;
        this->update();
    }

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void wheelEvent(QWheelEvent *event) override;
    void mouseDoubleClickEvent(QMouseEvent *event) override;

    void initializeGL() override;
    void resizeEvent(QResizeEvent *event) override;
    void paintEvent(QPaintEvent *event) override;

private:
    MeshExaminer *examiner_;
    QColor backgroundColor_;
};

#endif // GLVIEWER_H
