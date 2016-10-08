#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_drawOuter_clicked()
{
    ui->openGLWidget->setDrawOuter(ui->drawOuter->isChecked());
    ui->openGLWidget->updateGL();
}

void MainWindow::on_drawInner_clicked()
{
    ui->openGLWidget->setDrawInner(ui->drawInner->isChecked());
    ui->openGLWidget->updateGL();
}
