#pragma once

#include <QWidget>

class QGraphicsView;
class QGraphicsScene;

// Graphics canvas for DRAW / turtle graphics output.
// Uses QGraphicsView/QGraphicsScene for 2D rendering.
class GraphicsPanel : public QWidget {
    Q_OBJECT

public:
    explicit GraphicsPanel(QWidget *parent = nullptr);

private:
    QGraphicsScene *scene_;
    QGraphicsView  *view_;
};
