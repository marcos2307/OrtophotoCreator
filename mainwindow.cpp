#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "imagen.h"
#include <QDebug>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->consola->setReadOnly(true);

    Imagen * im = new Imagen;
    ui->horizontalLayout->addWidget(im);
    connect(im,SIGNAL(coordinates_clicked(QString)), ui->consola, SLOT(appendPlainText(QString)));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::image_clicked(QMouseEvent *event)
{
    QString s;
    s = QString::number(event->pos().x());
    s +=", ";
    s += QString::number(event->pos().y());
    ui->consola->appendPlainText(s);
}

