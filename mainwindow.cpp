#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "customscene.h"
#include <QGraphicsLineItem>
#include <QDebug>
#include <QPainter>
#include <QColor>
#include <cmath>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->consola->setReadOnly(false);
    ui->graphics_view->setInteractive(true);

    QImage image("/home/rocinante/Desktop/odm_orthophoto.tif");
    QGraphicsPixmapItem* item = new QGraphicsPixmapItem(QPixmap::fromImage(image));

    scene = new CustomScene();
    scene->addItem(item);
    ui->graphics_view->setScene(scene);


    connect(scene, SIGNAL(clicked(QPointF)), SLOT(agregarPunto(QPointF)));
    connect(scene, SIGNAL(over(QPointF)), SLOT(dibujar(QPointF)));
    connect(scene, SIGNAL(end()), SLOT(cerrar()));
    escribir("Presione los botones para realizar las mediciones. Para cerrar el poligono presionar click derecho.\n");

    refresh();

}


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::agregarPunto(QPointF p)
{
    if(measuring)
    {
        QPen blue_pen(Qt::blue);
        blue_pen.setWidth(3);
        polygon.append(p);
        int n = polygon.size();
        if(n>1)
        {
                scene->addLine(polygon[n-1].x(), polygon[n-1].y(), polygon[n-2].x(), polygon[n-2].y(), blue_pen);
                double l = sqrt ( pow(polygon[n-1].x() - polygon[n-2].x() , 2) + pow(polygon[n-1].y() - polygon[n-2].y(), 2) );
                escribir("Nuevo Trazo" + QString::number(n-1) + ": " + QString::number(l) + "\n");
                t += l;
                ui->long_line->setText(QString::number(t));
                escribir("Total: " +  QString::number(t) + "\n");
        }
    }
}

void MainWindow::dibujar(QPointF p)
{


    if(measuring)
    {
        int n = polygon.size();
        if(n>1)
        {
            QPen red_pen(Qt::red);
            red_pen.setWidth(3);
            last_line.setP1(polygon[n-1]);
            last_line.setP2(p);
            ui->graphics_view->update();
        }
    }
}

void MainWindow::cerrar(void)
{
    if(measuring)
    {
        int n = polygon.size();
        if(n>1)
        {
            QPen blue_pen(Qt::blue);
            blue_pen.setWidth(3);
            scene->addLine(polygon[n-1].x(), polygon[n-1].y(), polygon[0].x(), polygon[0].y(), blue_pen);
            double l = sqrt ( pow(polygon[n-1].x() - polygon[0].x() , 2) + pow(polygon[n-1].y() - polygon[0].y(), 2) );
            escribir("Trazo " + QString::number(n) + ": " + QString::number(l) + "\n");
            t += l;
            ui->long_line->setText(QString::number(t));
            escribir("Total: " +  QString::number(t) + "\n");
        }
    }
    if(measuringarea)
    {
        int n = polygon.size();
        if(n>2)
        {
            QPen blue_pen(Qt::blue);
            blue_pen.setWidth(3);
            scene->addLine(polygon[n-1].x(), polygon[n-1].y(), polygon[0].x(), polygon[0].y(), blue_pen);
            double l = sqrt ( pow(polygon[n-1].x() - polygon[0].x() , 2) + pow(polygon[n-1].y() - polygon[0].y(), 2) );
            double Area = getArea();
            escribir("AREA: " + QString::number(Area) + "\n");
            ui->area_line->setText(QString::number(Area));


        }
    }

    ui->long_btn->setChecked(false);
    ui->area_btn->setChecked(false);

}

void MainWindow::refresh()
{
    measuring = false;
    measuringarea = false;
    ui->long_line->setText("");
    ui->area_line->setText("");
    polygon.clear();
    t = 0;
}

void MainWindow::on_long_btn_toggled(bool checked)
{
    measuring = checked;
}

void MainWindow::on_area_btn_toggled(bool checked)
{
    measuring = checked;
    measuringarea = checked;
}


void MainWindow::on_rst_btn_pressed()
{
    refresh();
    ui->long_btn->setChecked(false);
    ui->area_btn->setChecked(false);
}

void MainWindow::escribir(QString s)
{
    ui->consola->insertPlainText(s);
    ui->consola->verticalScrollBar()->setValue(ui->consola->verticalScrollBar()->maximum()-5);
}

double MainWindow::determinante(QPointF P1, QPointF P2)
{
    return (P1.x()*P2.y() - P1.y()*P2.x());
}

double MainWindow::getArea(void)
{
    double Area = 0;
    int n = polygon.size();
    for (int i = 1;i < n; ++i)
    {
        Area += determinante(polygon[i-1],polygon[i]);
    }
    Area += determinante(polygon[n-1],polygon[0]);
    return abs(Area)/2;
}
