#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QGraphicsScene *scene;
    QPixmap image;
    image.load("/home/rocinante/OrtophotoCreator/odm_orthophoto.tif");
    scene = new QGraphicsScene(this);
    scene->addPixmap(image);
    scene->setSceneRect(image.rect());
    ui->imagen->setScene(scene);
}

MainWindow::~MainWindow()
{
    delete ui;
}
