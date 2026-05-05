#pragma once

#include <QWidget>

class QGraphicsView;
class QGraphicsScene;

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

    /// Save canvas as PNG image
    void saveAsPng();

    /// Save canvas as SVG image
    void saveAsSvg();

signals:
    /// Emitted when user requests clearing (button or context menu).
    void clearRequested();

private:
    void renderGroup(const comal::graphics::Group& group,
                     const comal::graphics::Scene& scene,
                     double offsetX, double offsetY);

    QGraphicsScene *scene_;
    QGraphicsView  *view_;
};
