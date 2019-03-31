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
    this->init_view();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::init_view()
{

    ui = new Ui::MainWindow;
    ui->setupUi(this);
    QMainWindow::setCentralWidget(this->_mainWindowCtrl->getMusicPlayerView());
    cout<<this->_mainWindowCtrl->getMusicPlayerView()->size().height();
    cout<<this->ui->centralwidget->size().height()<<endl;


}
