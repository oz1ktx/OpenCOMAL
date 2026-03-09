#include "graphics_panel.h"

#include <QVBoxLayout>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsEllipseItem>
#include <QGraphicsTextItem>
#include <QPen>
#include <QBrush>

GraphicsPanel::GraphicsPanel(QWidget *parent)
    : QWidget(parent)
{
    auto *layout = new QVBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);

    scene_ = new QGraphicsScene(0, 0, 640, 480, this);
    view_  = new QGraphicsView(scene_, this);
    view_->setRenderHint(QPainter::Antialiasing);
    layout->addWidget(view_);

    // Draw some placeholder shapes to show the canvas works
    scene_->setBackgroundBrush(QColor(240, 240, 255));

    // A rectangle
    scene_->addRect(40, 40, 200, 120,
                    QPen(Qt::black, 2),
                    QBrush(QColor(0, 128, 255, 128)));

    // A circle
    scene_->addEllipse(300, 60, 100, 100,
                       QPen(Qt::darkGreen, 2),
                       QBrush(QColor(0, 200, 100, 128)));

    // A line
    scene_->addLine(40, 200, 450, 300, QPen(Qt::red, 2));

    // Label
    auto *label = scene_->addText("Graphics Canvas\n(DRAW output goes here)");
    label->setPos(150, 350);
    label->setDefaultTextColor(Qt::gray);
}
