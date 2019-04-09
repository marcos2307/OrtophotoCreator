#include "imagen.h"
#include <QDebug>

Imagen::Imagen(QWidget *parent) : QGraphicsView(parent)
{
    QGraphicsScene *scene;
    QPixmap image;
    image.load("/home/rocinante/OrtophotoCreator/odm_orthophoto.tif");
    scene = new QGraphicsScene(this);
    scene->addPixmap(image);
    scene->setSceneRect(image.rect());
    this->setScene(scene);

}


void Imagen::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        QString s;
        s = QString::number(event->pos().x());
        s +=", ";
        s += QString::number(event->pos().y());
        emit coordinates_clicked(s);
    }
    else if (event->button() == Qt::RightButton) {
        emit coordinates_clicked("RButton");
    }
}
