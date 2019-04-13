#ifndef GLOBALVARIABLE_H
#define GLOBALVARIABLE_H

#pragma once

#include "playmusicdetialcontroller.h"
#include <iostream>
#include <QObject>
#include "user.h"
#include <QJsonObject>
#include "filefunccontroller.h"

class PlayMusicDetialController;
class user;


class GlobalVariable{

public:
    //
    static PlayMusicDetialController* global_PlayMusicDetialCtrl;
    //环境变量
    static QJsonObject settingObj;

    //全局的用户变量
    static User global_User;
    //是否登陆
    static bool global_Islogin;

    //用户文件绝对路径
    static QString global_user_absolute_file;


    //判断是否登陆
    static bool IsLogin();
    //获取全局用户
    static User& get_global_User();

    static void saveUserTolocal();

    GlobalVariable();

    ~GlobalVariable();
};


#endif // GLOBALVARIABLE_H
