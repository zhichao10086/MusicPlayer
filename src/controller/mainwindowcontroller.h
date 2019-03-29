#ifndef MAINWINDOWCONTROLLER_H
#define MAINWINDOWCONTROLLER_H

#include <mainwindow.h>
#include <mainwindowmodel.h>
#include <musicplayercontroller.h>


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

    MusicPlayerView* getMusicPlayerView();

    MainWindow* _mainWindow;
    MainWindowmodel* _mainWindowModel;





};

#endif // MainWindowController_H
