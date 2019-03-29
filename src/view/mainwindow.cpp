#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::MainWindow(MainWindowController *mc)
{
    this->_mainWindowCtrl = mc;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::init_view()
{
    this->setCentralWidget(this->_mainWindowCtrl->getMusicPlayerView());

}
