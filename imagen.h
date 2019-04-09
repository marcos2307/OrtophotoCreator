#ifndef IMAGEN_H
#define IMAGEN_H

#include <QObject>
#include <QWidget>
#include <QGraphicsView>
#include <QMouseEvent>

class Imagen : public QGraphicsView
{
    Q_OBJECT
public:
    explicit Imagen(QWidget *parent = nullptr);
    void mousePressEvent(QMouseEvent *event);

signals:
    void coordinates_clicked(QString);

public slots:
};

#endif // IMAGEN_H
