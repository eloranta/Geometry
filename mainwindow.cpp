#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->deleteButton, &QPushButton::clicked, this, &MainWindow::onDeleteClicked);
    connect(ui->deleteAllButton, &QPushButton::clicked, this, &MainWindow::onDeleteAllClicked);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onDeleteClicked() {
    qDebug() << "onDeleteClicked";
}

void MainWindow::onDeleteAllClicked() {
    // canvas_->deleteAll();
    qDebug() << "onDeleteAllClicked";

}
