#pragma once

#include <QWidget>

class QGraphicsView;
class QGraphicsScene;
class QToolBar;

namespace comal::graphics { class Scene; struct Group; }

// Graphics canvas for DRAW command output.
// Renders the comal::graphics::Scene model into a QGraphicsView.
class GraphicsPanel : public QWidget {
    Q_OBJECT

public:
    explicit GraphicsPanel(QWidget *parent = nullptr);

public slots:
    /// Re-render the entire scene from the graphics model.
    void renderScene(const comal::graphics::Scene& scene);

    /// Clear the canvas to a blank state.
    void clearCanvas();

signals:
    /// Emitted when user requests clearing (button or context menu).
    void clearRequested();

private slots:
    void onSaveAsPng();
    void onSaveAsSvg();

private:
    void renderGroup(const comal::graphics::Group& group,
                     const comal::graphics::Scene& scene,
                     double offsetX, double offsetY);

    QGraphicsScene *scene_;
    QGraphicsView  *view_;
    QToolBar       *toolbar_;
};
