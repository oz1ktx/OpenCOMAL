#include "graphics_panel.h"
#include "comal_scene_model.h"

#include <QVBoxLayout>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsEllipseItem>
#include <QGraphicsTextItem>
#include <QToolBar>
#include <QMenu>
#include <QAction>
#include <QFileDialog>
#include <QPen>
#include <QBrush>
#include <QImage>
#include <QPainter>
#include <QSvgGenerator>

using namespace comal::graphics;

static QColor toQt(const Color& c) {
    return QColor(c.r, c.g, c.b, c.a);
}

GraphicsPanel::GraphicsPanel(QWidget *parent)
    : QWidget(parent)
{
    auto *layout = new QVBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);

    // Toolbar with Clear and Save buttons
    toolbar_ = new QToolBar(this);
    toolbar_->setIconSize(QSize(16, 16));
    toolbar_->addAction(tr("Clear"), this, [this]() { emit clearRequested(); });
    toolbar_->addSeparator();
    toolbar_->addAction(tr("Save PNG..."), this, &GraphicsPanel::onSaveAsPng);
    toolbar_->addAction(tr("Save SVG..."), this, &GraphicsPanel::onSaveAsSvg);
    layout->addWidget(toolbar_);

    scene_ = new QGraphicsScene(0, 0, 640, 480, this);
    view_  = new QGraphicsView(scene_, this);
    view_->setRenderHint(QPainter::Antialiasing);
    layout->addWidget(view_);

    // Context menu on the graphics view
    view_->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(view_, &QWidget::customContextMenuRequested, this, [this](const QPoint &pos) {
        QMenu menu(this);
        menu.addAction(tr("Clear"), this, [this]() { emit clearRequested(); });
        menu.addSeparator();
        menu.addAction(tr("Save as PNG..."), this, &GraphicsPanel::onSaveAsPng);
        menu.addAction(tr("Save as SVG..."), this, &GraphicsPanel::onSaveAsSvg);
        menu.exec(view_->mapToGlobal(pos));
    });

    scene_->setBackgroundBrush(QColor(240, 240, 255));

    // Placeholder label
    auto *label = scene_->addText("Graphics Canvas\n(DRAW output goes here)");
    label->setPos(150, 200);
    label->setDefaultTextColor(Qt::gray);
}

void GraphicsPanel::clearCanvas()
{
    scene_->clear();
    scene_->setBackgroundBrush(QColor(240, 240, 255));
}

void GraphicsPanel::onSaveAsPng()
{
    QString path = QFileDialog::getSaveFileName(
        this, tr("Save as PNG"), QString(), tr("PNG Images (*.png)"));
    if (path.isEmpty()) return;

    QRectF sceneRect = scene_->sceneRect();
    QImage image(sceneRect.size().toSize(), QImage::Format_ARGB32_Premultiplied);
    image.fill(Qt::transparent);

    QPainter painter(&image);
    painter.setRenderHint(QPainter::Antialiasing);
    scene_->render(&painter);
    painter.end();

    image.save(path);
}

void GraphicsPanel::onSaveAsSvg()
{
    QString path = QFileDialog::getSaveFileName(
        this, tr("Save as SVG"), QString(), tr("SVG Files (*.svg)"));
    if (path.isEmpty()) return;

    QRectF sceneRect = scene_->sceneRect();
    QSvgGenerator svg;
    svg.setFileName(path);
    svg.setSize(sceneRect.size().toSize());
    svg.setViewBox(QRect(QPoint(0, 0), sceneRect.size().toSize()));
    svg.setTitle(tr("OpenCOMAL Graphics"));

    QPainter painter(&svg);
    painter.setRenderHint(QPainter::Antialiasing);
    scene_->render(&painter);
    painter.end();
}

void GraphicsPanel::renderScene(const comal::graphics::Scene& model)
{
    scene_->clear();
    scene_->setBackgroundBrush(toQt(model.backgroundColor));
    renderGroup(model.root(), model, 0, 0);
}

void GraphicsPanel::renderGroup(const Group& group,
                                const comal::graphics::Scene& model,
                                double offsetX, double offsetY)
{
    double gx = offsetX + group.x;
    double gy = offsetY + group.y;

    for (const auto& shape : group.shapes) {
        QPen pen(Qt::NoPen);
        if (shape.hasStroke) {
            pen = QPen(toQt(shape.strokeColor), shape.lineWidth);
        }

        QBrush brush(Qt::NoBrush);
        if (shape.hasFill) {
            brush = QBrush(toQt(shape.fillColor));
        }

        if (auto* line = std::get_if<LineShape>(&shape.data)) {
            scene_->addLine(gx + line->x1, gy + line->y1,
                           gx + line->x2, gy + line->y2, pen);
        }
        else if (auto* rect = std::get_if<RectShape>(&shape.data)) {
            scene_->addRect(gx + rect->x, gy + rect->y,
                           rect->w, rect->h, pen, brush);
        }
        else if (auto* circ = std::get_if<CircleShape>(&shape.data)) {
            double d = circ->r * 2;
            scene_->addEllipse(gx + circ->cx - circ->r,
                              gy + circ->cy - circ->r,
                              d, d, pen, brush);
        }
        else if (auto* ell = std::get_if<EllipseShape>(&shape.data)) {
            scene_->addEllipse(gx + ell->x, gy + ell->y,
                              ell->w, ell->h, pen, brush);
        }
        else if (auto* px = std::get_if<PixelShape>(&shape.data)) {
            scene_->addRect(gx + px->x, gy + px->y,
                           1.0, 1.0,
                           QPen(Qt::NoPen), QBrush(toQt(px->color)));
        }
        else if (auto* txt = std::get_if<TextShape>(&shape.data)) {
            QFont font;
            font.setPointSizeF(txt->fontSize);
            auto* item = scene_->addText(QString::fromStdString(txt->text), font);
            item->setPos(gx + txt->x, gy + txt->y);
            // Use stroke color as text color; fall back to black if stroke disabled
            QColor textColor = shape.hasStroke
                ? toQt(shape.strokeColor)
                : QColor(0, 0, 0, 255);
            item->setDefaultTextColor(textColor);
        }
    }

    // Recurse into child groups
    for (const auto& child : group.children) {
        renderGroup(*child, model, gx, gy);
    }
}
