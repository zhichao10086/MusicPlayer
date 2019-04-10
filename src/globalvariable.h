#ifndef GLOBALVARIABLE_H
#define GLOBALVARIABLE_H

#pragma once

#include "playmusicdetialcontroller.h"
#include <iostream>
#include <QObject>

class PlayMusicDetialController;



class GlobalVariable{

public:
    static PlayMusicDetialController* global_PlayMusicDetialCtrl;
    GlobalVariable();

    ~GlobalVariable();
};


#endif // GLOBALVARIABLE_H
