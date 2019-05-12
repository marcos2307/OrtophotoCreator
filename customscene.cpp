#include "customscene.h"
#include <QMessageBox>
#include <QDebug>


CustomScene::CustomScene(QObject *parent) :
    QGraphicsScene(parent)
{

}
void CustomScene::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    if(mouseEvent->button() == Qt::RightButton)
    {
        emit end();
    }
    else
    {
        QPointF p;
        p = mouseEvent->scenePos();

        //QString s;
        //s = "(" + QString::number(p.x()) + ", " +  QString::number(p.y()) + ")";
        //qDebug()<<s;
        emit clicked(p);
    }
}

void CustomScene::mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    QPointF p;
    p = mouseEvent->scenePos();
    emit over(p);
}
