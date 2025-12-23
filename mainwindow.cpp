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
    ui->canvas->onDelete();
}

void MainWindow::onDeleteAllClicked() {
    ui->canvas->onDeleteAll();
}
