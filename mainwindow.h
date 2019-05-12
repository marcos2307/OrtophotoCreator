#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsSceneMouseEvent>
#include <QtWidgets>
#include "customscene.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);

    ~MainWindow();

    double determinante(QPointF P1, QPointF P2);
    double getArea(void);
    void refresh(void);
    void escribir(QString);

private slots:
    void agregarPunto(QPointF);
    void dibujar(QPointF);
    void cerrar(void);
    void on_long_btn_toggled(bool checked);
    void on_area_btn_toggled(bool checked);

    void on_rst_btn_pressed();

private:
    Ui::MainWindow *ui;
    CustomScene *scene;
    QPolygonF polygon;
    QLineF last_line;
    double  t = 0;
    bool measuring;
    bool measuringarea;
};

#endif // MAINWINDOW_H
