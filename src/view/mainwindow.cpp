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
    //this->init_view();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::init_view()
{

    ui = new Ui::MainWindow;
    ui->setupUi(this);
    //无边框
    this->setWindowFlags(windowFlags()|Qt::FramelessWindowHint);
    this->setWindowState(Qt::WindowActive);
    this->ui->statusbar->hide();

    QMainWindow::setCentralWidget(this->_mainWindowCtrl->getMusicPlayerView());
    //cout<<this->_mainWindowCtrl->getMusicPlayerView()->size().height();
    //cout<<this->ui->centralwidget->size().height()<<endl;


}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton){
         _dragPosition = event->globalPos() - frameGeometry().topLeft();
         event->accept();
    }
}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    if (event->buttons() == Qt::LeftButton) //当满足鼠标左键被点击时。
        {
             move(event->globalPos() - _dragPosition);//移动窗口
             event->accept();
        }
}

