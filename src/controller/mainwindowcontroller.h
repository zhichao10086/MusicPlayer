#ifndef MAINWINDOWCONTROLLER_H
#define MAINWINDOWCONTROLLER_H

#include <mainwindow.h>
#include <mainwindowmodel.h>
#include <musicplayercontroller.h>
#include "musicplayercontroller.h"
#include "musicplayerview.h"
#include <iostream>
#include <QApplication>
#include <QRect>

using namespace std;


class MainWindow;
class MainWindowmodel;

class MainWindowController
{
public:
    MainWindowController();

    /*
     * 初始化
    */
    void init();


    /*
     * 显示
     */
    void show();

    /*
     * 关闭主程序
     */
    void closeApp();


    /*
     * 最小化
     */
    void minApp();

    /*
     * 最大化
     */
    void maxApp();





    MusicPlayerView* getMusicPlayerView();

    MainWindow* _mainWindow;
    MainWindowmodel* _mainWindowModel;





    MainWindow *getMainWindow() const;
    void setMainWindow(MainWindow *mainWindow);
};

#endif // MainWindowController_H
