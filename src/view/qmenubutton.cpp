#include "qmenubutton.h"
#include "ui_qmenubutton.h"

QMenuButton::QMenuButton(QWidget *parent) :
    QPushButton(parent),
    ui(new Ui::QMenuButton)
{
    ui->setupUi(this);
    this->initView();

}

QMenuButton::~QMenuButton()
{
    delete ui;
}

QMenu *QMenuButton::getMenu()
{
    return this->__menu;
}

void QMenuButton::initView()
{
    this->__menu = new QMenu();

    actionShunXu   = new QAction("顺序播放");
    actionSuiJi    = new QAction("随机播放");
    actionXunHuan  = new QAction("列表循环");
    actionDanQu    = new QAction("单曲循环");
    this->__menu->addAction(actionShunXu);
    this->__menu->addAction(actionSuiJi);
    this->__menu->addAction(actionXunHuan);
    this->__menu->addAction(actionDanQu);
}

void QMenuButton::popupMenu()
{
    QPoint pos; //获取按键菜单的坐标

   // int x = pos.x();
    pos.setX(0);

    int y = pos.y();
   // pos.setX(x + this->geometry().width()/2);

    pos.setY(y+this->geometry().height());

    //返回菜单下面的action不管有没被选中，可以算一个小事件循环

    //里面参数的意思是在哪个坐标弹出菜单，这里将自定义的pop按键的坐标作参考，并在其下面弹出菜单

    QAction *action =  this->__menu->exec(this->mapToGlobal(pos));
    if(action == actionDanQu){
        emit changePlayBackMode(QMediaPlaylist::PlaybackMode::CurrentItemInLoop);

    }else if(action == actionXunHuan){
        emit changePlayBackMode(QMediaPlaylist::PlaybackMode::Loop);
    }else if(action == actionSuiJi){
        emit changePlayBackMode(QMediaPlaylist::PlaybackMode::Random);
    }else{
        emit changePlayBackMode(QMediaPlaylist::PlaybackMode::Sequential);
    }
}
