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
    this->__menu->setStyleSheet("QMenu::item {\
                                font-size: 9pt; \
                                background-color:rgb(249, 255, 239);\
                                padding:2px 16px; /*设置菜单项文字上下和左右的内边距，效果就是菜单中的条目左右上下有了间隔*/\
                                margin:2px 2px;/*设置菜单项的外边距*/\
                                 }\
                                QMenu::item:selected { \
                                    background-color:rgb(119,119,119,50);/*选中的样式*/\
                                }\
                                QMenu::item:pressed {/*菜单项按下效果*/\
                                          background-color: rgb(119,119,119,50); \
                                      }");

    actionShunXu   = new QAction("顺序播放");
    actionSuiJi    = new QAction("随机播放");
    actionXunHuan  = new QAction("列表循环");
    actionDanQu    = new QAction("单曲循环");
    //actionShunXu->setIcon(QIcon(":/images/icon/images/列表顺序.png"));
    //actionSuiJi->setIcon(QIcon(":/images/icon/images/随机播放_32.png"));
    //actionXunHuan->setIcon(QIcon(":/images/icon/images/循环播放_32.png"));
    //actionDanQu->setIcon(QIcon(":/images/icon/images/单曲循环_32.png"));
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
        this->setStyleSheet("QPushButton{	\
                                \
                                border-image: url(:/images/icon/images/单曲循环_32.png);\
                            }\
                            QPushButton:hover{\
                                border-image: url(:/images/icon/images/单曲循环_32(1).png);\
                            }");
        emit changePlayBackMode(QMediaPlaylist::PlaybackMode::CurrentItemInLoop);

    }else if(action == actionXunHuan){
        this->setStyleSheet("QPushButton{	\
                            \
                            border-image: url(:/images/icon/images/循环播放_32.png);\
                        }\
                        QPushButton:hover{\
                            border-image: url(:/images/icon/images/循环播放_32(1).png);\
                        }");
        emit changePlayBackMode(QMediaPlaylist::PlaybackMode::Loop);
    }else if(action == actionSuiJi){
        this->setStyleSheet("QPushButton{	\
                            \
                            border-image: url(:/images/icon/images/随机播放_32.png);\
                        }\
                        QPushButton:hover{\
                            border-image: url(:/images/icon/images/随机播放_32(1).png);\
                        }");

        emit changePlayBackMode(QMediaPlaylist::PlaybackMode::Random);
    }else{
        this->setStyleSheet("QPushButton{	\
                        \
                        border-image: url(:/images/icon/images/列表顺序.png);\
                    }\
                    QPushButton:hover{\
                        border-image: url(:/images/icon/images/列表顺序(1).png);\
                    }");


        emit changePlayBackMode(QMediaPlaylist::PlaybackMode::Sequential);
    }
}
